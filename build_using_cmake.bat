call "%VS90COMNTOOLS%/vsvars32.bat"
call "%VS100COMNTOOLS%/vsvars32.bat"
call "%VS110COMNTOOLS%/vsvars32.bat"
call "%VS120COMNTOOLS%/vsvars32.bat"
call "%VS140COMNTOOLS%/vsvars32.bat"

set BUILD_DIR=build
set BIN_DIR=bin

mkdir %BUILD_DIR%
cd %BUILD_DIR%
cmake -G "NMake Makefiles" ../
nmake
cd ..

