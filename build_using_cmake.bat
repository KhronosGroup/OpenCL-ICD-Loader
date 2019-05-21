@set WDK=C:\Program Files (x86)\Windows Kits\10\include\10.0.17763.0
@if EXIST "%WDK%\km\d3dkmthk.h" goto found_WDK
  @echo Windows WDK not found at "%WDK%".
  @echo Download it from https://docs.microsoft.com/en-us/windows-hardware/drivers/download-the-wdk
  @echo Then, fix build_using_cmake.bat
  @goto :eof
:found_WDK

call "%VS90COMNTOOLS%/vsvars32.bat"

set BUILD_DIR=build
set BIN_DIR=bin

mkdir %BUILD_DIR%
cd %BUILD_DIR%
cmake -G "NMake Makefiles" ../
nmake
cd ..

