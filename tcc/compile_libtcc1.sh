#!/bin/bash

if [ $# = 0 ]; then
  TCC=tcc
else
  TCC=$1
fi

# Get tcc architecture
TCC_VERSION=$(./$TCC -v)
echo $TCC_VERSION
IFS='(' read -ra ADDR <<< "$TCC_VERSION"
IFS=' ' read -ra ADDR <<< "${ADDR[1]}"
TCC_ARCHITECTURE="${ADDR[0]}"
echo "tcc architecture: ${TCC_ARCHITECTURE}"

# Create lib folder if it doesn't exist
if [ ! -d "lib" ]; then
  mkdir lib
fi

set -o xtrace

if [ $TCC_ARCHITECTURE = x86_64 ]; then
  ./$TCC -c lib_libtcc1/libtcc1.c
  ./$TCC -c lib_libtcc1/alloca86_64.S
  ./$TCC -c lib_libtcc1/alloca86_64-bt.S
  ./$TCC -c lib_libtcc1/va_list.c
  ./$TCC -c lib_libtcc1/bcheck.c -Iinclude
  ./$TCC -ar rcs lib/libtcc1-64.a libtcc1.o va_list.o bcheck.o alloca86_64.o alloca86_64-bt.o
elif [ $TCC_ARCHITECTURE = i386 ]
then
  ./$TCC -c lib_libtcc1/libtcc1.c
  ./$TCC -c lib_libtcc1/alloca86.c
  ./$TCC -c lib_libtcc1/alloca86-bt.c
  ./$TCC -c lib_libtcc1/bcheck.c
  ./$TCC -ar rcs lib/libtcc1-64.a libtcc1.o alloca86.o alloca86-bt.o bcheck.o
elif [ $TCC_ARCHITECTURE = arm ]
then
  ./$TCC -c lib_libtcc1/libtcc1.c
  ./$TCC -c lib_libtcc1/armeabi.c
  ./$TCC -c lib_libtcc1/alloca-arm.c
  ./$TCC -c lib_libtcc1/armflush.c
  ./$TCC -ar rcs libtcc1.o armeabi.o alloca-arm.o armflush.o
elif [ $TCC_ARCHITECTURE = arm64 ]
then
  ./$TCC -c lib_libtcc1/lib-arm64.c
  ./$TCC -ar rcs lib/libtcc1-arm64.a lib-arm64.o
else
    echo "Unknown architecture: $TCC_ARCHITECTURE"
fi

rm *.o
