@echo on
mkdir build
cd build
cmake .. -G "Visual Studio 15 2017 Win64" -DCMAKE_TOOLCHAIN_FILE="%VCPKG_PATH%scripts\buildsystems\vcpkg.cmake"