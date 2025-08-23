# Contributing to the OpenCL ICD Loader project.

Contributions to the OpenCL ICD Loader are welcomed and encouraged.
Please follow the instructions below for submitting your patches.

## Preparing and submitting changes

Please propose changes to the ICD loader using GitHub pull requests. 
You will be prompted with a one-time "click-through" CLA dialog as part of submitting your pull request or other contribution to GitHub.

## Windows DLL versioning

The ICD Loader version is maintained in `loader/windows/OpenCL.rc` in the form `x.y.z.0` in three fields:
FILEVERSION, PRODUCTVERSION and FileVersion.

The `z` component of the version must be incremented by one for each pull request that modifies anything in the `loader` directory.
The fields must match each other after the increment.

## Linux shared library versioning

The ICD loader library version on Linux is 1.2 with SONAME set to libOpenCL.so.1 using the SOVERSION property in CMakeLists.txt.
MAJOR version does not change when new API functions are added to the ICD loader because the loader maintains backwards compatibility.
MINOR version remains 2.
Note that the version number is independent of the OpenCL specification revision number.
ICD loader library version should take the form MAJOR.MINOR.RELEASE instead of currently used MAJOR.MINOR format (e.g. current version 1.2 should become 1.2.0).
RELEASE field should be incremented by one for each pull request that modifies anything in the loader directory.

