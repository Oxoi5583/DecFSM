@echo off

cd build
cmake .. --fresh
cmake --build .
cd ..
cd bin/Debug
test.exe