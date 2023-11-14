#!/bin/bash

if [ $1 == clean ]; then
  rm -rf build/

elif [ $1 == build ]; then
  if [ ! -d "build" ]; then
    mkdir build
  fi
  
  cd build
  cmake ..
  make
else
  echo "please input right compile parameter!"
fi
