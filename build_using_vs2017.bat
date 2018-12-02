REM @echo off

Echo LIB Windows Build

REM # Build Vars #
set _SCRIPT_DRIVE=%~d0
set _SCRIPT_FOLDER=%~dp0
set INITDIR=%_SCRIPT_FOLDER%
set SRC=%INITDIR%
set BUILDTREE=%SRC%\build\
set INCS=%SRC%\inc\
SET tbs_arch=x86
SET vcvar_arg=x86
SET cmake_platform="Visual Studio 15 2017"

REM # VC Vars #
SET VCVAR="%programfiles(x86)%\Microsoft Visual Studio\2017\Professional\VC\Auxiliary\Build\vcvarsall.bat"
if exist %VCVAR% call %VCVAR% %vcvar_arg%
SET VCVAR="%programfiles(x86)%\Microsoft Visual Studio\2017\Community\VC\Auxiliary\Build\vcvarsall.bat"
if exist %VCVAR% call %VCVAR% %vcvar_arg%

@echo on

REM # Clean Build Tree #
rd /s /q %BUILDTREE%
mkdir %BUILDTREE%
set BINDIR=%BUILDTREE%\bin\
mkdir %BINDIR%

REM # TODO: install required includes to %INCS%
REM # https://github.com/KhronosGroup/EGL-Registry/tree/master/api/EGL #
REM # https://github.com/KhronosGroup/EGL-Registry/tree/master/api/KHR #
REM # https://github.com/KhronosGroup/OpenCL-Headers/tree/master/CL #

%_SCRIPT_DRIVE%
cd %BUILDTREE%
cmake -G %cmake_platform% ^
-DCMAKE_INSTALL_PREFIX=%BINDIR% ^
%SRC%
cmake --build %BUILDTREE%


cd %INITDIR%

