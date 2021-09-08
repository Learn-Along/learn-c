rm -r build
mkdir build
cd build
cmake ..
cmake --build .
make test
