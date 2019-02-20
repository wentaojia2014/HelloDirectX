@echo off
mkdir build-ms
cd build-ms
call "C:\Program Files (x86)\Microsoft Visual Studio\2017\Enterprise\VC\Auxiliary\Build\vcvars64.bat"
cmake .. -G "NMake Makefiles" -DCMAKE_TOOLCHAIN_FILE="%VCPKG_PATH%scripts\buildsystems\vcpkg.cmake"
pause