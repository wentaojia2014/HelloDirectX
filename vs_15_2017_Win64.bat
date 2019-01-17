@echo off
mkdir build
cd build
cmake .. -G "Visual Studio 15 2017 Win64" -DCMAKE_TOOLCHAIN_FILE=E:/Tools/vcpkg/scripts/buildsystems/vcpkg.cmake