cd bin
cmake .. --fresh
cmake --build .
cd Debug
test.exe
cd ..
cd ..