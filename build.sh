#!/bin/bash

if [ ! -d "build" ]; then
  mkdir build
fi

if [[ $1 == "clean" ]]; then
  rm -rf build/
elif [[ $1 == "release" ]]; then
  cd build
  cmake ..
  make -j 4
elif [[ $1 == "test" ]]; then 
  cd build
  cmake .. -DTCS_WITH_TEST=1
  make -j 4 
else
  echo "please input right compile parameter!"
fi
