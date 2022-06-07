/*
 * Copyright (c) 2017-2019 The Khronos Group Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * OpenCL is a trademark of Apple Inc. used under license by Khronos.
 */

#include "icd.h"
#include "icd_windows.h"

#ifdef OPENCL_ICD_LOADER_DISABLE_OPENCLON12

extern "C" bool khrIcdOsVendorsEnumerateAppPackage()
{
    KHR_ICD_TRACE("OpenCLOn12 is disabled\n");
    return false;
}

#else

#include "icd_windows_apppackage.h"

#include <windows.management.deployment.h>
#include <wrl/client.h>
#include <wrl/wrappers/corewrappers.h>

#include <locale>
#include <codecvt>

template <typename F>
struct ScopeExit {
    ScopeExit(F&& f) : f(std::forward<F>(f)) {}
    ~ScopeExit() { f(); }
    F f;
};

template <typename F>
inline ScopeExit<F> MakeScopeExit(F&& f) {
    return ScopeExit<F>(std::forward<F>(f));
};

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;

extern "C" bool khrIcdOsVendorsEnumerateAppPackage()
{
    HRESULT hrInit = Windows::Foundation::Initialize(RO_INIT_MULTITHREADED);
    if (hrInit == RPC_E_CHANGED_MODE)
    {
        hrInit = Windows::Foundation::Initialize(RO_INIT_SINGLETHREADED);
    }
    if (FAILED(hrInit))
    {
        KHR_ICD_TRACE("Failed to init WinRT\n");
        return false;
    }
    auto Cleanup = MakeScopeExit([]()
        {
            Windows::Foundation::Uninitialize();
        });

    using ABI::Windows::Management::Deployment::IPackageManager;
    ComPtr<IPackageManager> packageManager;
    if (FAILED(Windows::Foundation::ActivateInstance(
        HStringReference(RuntimeClass_Windows_Management_Deployment_PackageManager).Get(),
        &packageManager)))
    {
        KHR_ICD_TRACE("Failed to get package manager\n");
        return false;
    }

    using IPackageCollection = ABI::Windows::Foundation::Collections::__FIIterable_1_Windows__CApplicationModel__CPackage_t;
    ComPtr<IPackageCollection> collection;
    if (FAILED(packageManager->FindPackagesByUserSecurityIdPackageFamilyName(
        HStringReference(L"").Get(),
        HStringReference(L"Microsoft.D3DMappingLayers_8wekyb3d8bbwe").Get(),
        &collection)))
    {
        KHR_ICD_TRACE("Failed to find mapping layers package\n");
        return false;
    }

    using IPackageIterator = ABI::Windows::Foundation::Collections::IIterator<
        ABI::Windows::ApplicationModel::Package*>;
    ComPtr<IPackageIterator> iter;
    if (FAILED(collection->First(&iter)))
    {
        KHR_ICD_TRACE("Failed to get package collection iterator\n");
        return false;
    }

    while ([&iter]()
        {
            boolean hasCurrent = false;
            return SUCCEEDED(iter->get_HasCurrent(&hasCurrent)) && hasCurrent;
        }())
    {
        using ABI::Windows::ApplicationModel::IPackage;
        ComPtr<IPackage> package;
        if (FAILED(iter->get_Current(&package)))
        {
            KHR_ICD_TRACE("Failed to get package\n");
            boolean hasCurrent = false;
            (void)iter->MoveNext(&hasCurrent);
            continue;
        }

        boolean hasCurrent = false;
        (void)iter->MoveNext(&hasCurrent);

        using ABI::Windows::Storage::IStorageFolder;
        ComPtr<IStorageFolder> folder;
        if (FAILED(package->get_InstalledLocation(&folder)))
        {
            KHR_ICD_TRACE("Failed to get package install folder\n");
            continue;
        }

        using ABI::Windows::Storage::IStorageItem;
        ComPtr<IStorageItem> item;
        if (FAILED(folder.As(&item)))
        {
            KHR_ICD_TRACE("Failed to convert folder to storage item\n");
            continue;
        }

        HString path;
        if (FAILED(item->get_Path(path.GetAddressOf())))
        {
            KHR_ICD_TRACE("Failed to get path\n");
            continue;
        }

        UINT pathSize = 0;
        auto rawPath = path.GetRawBuffer(&pathSize);
        if (pathSize == 0 || rawPath == nullptr)
        {
            KHR_ICD_TRACE("Failed to get path\n");
            continue;
        }
        
#if defined(_M_AMD64)
#define PLATFORM_PATH L"x64"
#elif defined(_M_ARM)
#define PLATFORM_PATH L"arm"
#elif defined(_M_ARM64)
#define PLATFORM_PATH L"arm64"
#elif defined(_M_IX86)
#define PLATFORM_PATH L"x86"
#endif

        wchar_t dllPath[MAX_PATH];
        wcscpy_s(dllPath, rawPath);
        wcscat_s(dllPath, L"\\" PLATFORM_PATH L"\\OpenCLOn12.dll");

        std::wstring_convert<std::codecvt_utf8<wchar_t>> convert;
        std::string narrowDllPath = convert.to_bytes(dllPath);

        adapterAdd(narrowDllPath.c_str(), {});
        return true;
    }
    return false;
}

#endif
