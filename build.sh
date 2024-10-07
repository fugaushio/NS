mkdir build
cd build
cmake -D compiler=g++ \
      -D enable_GLOG=ON \
      ..

cmake --build .