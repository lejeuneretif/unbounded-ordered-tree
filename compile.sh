#!/bin/bash

COMMAND="compile"

if [ $# -ge 1 ]; then
  COMMAND=$1
fi

TEST_FLAGS="TEST_TRACE"

if [ $COMMAND = "debug" ]; then
  TEST_FLAGS="$TEST_FLAGS,LEVEL_DEBUG"
  # Then compile
  COMMAND="compile"
fi

if [ $COMMAND = "clean" ]; then
  rm -rf build bin
  exit
elif [ $COMMAND = "test" ]; then
  bin/unit-test.run
  exit
elif [ $COMMAND = "compile" ]; then
  BUILD_PATH=build/$(echo -n $TEST_FLAGS | md5sum | cut -c 1-8)
  echo "BUILD_PATH *$BUILD_PATH*"
  ORIGINAL_PATH=$(pwd)
  mkdir -p $BUILD_PATH bin
  cp -ru src/* tst/* $BUILD_PATH
  cd $BUILD_PATH
  autoreconf --install
  ./configure
  make "TEST_FLAGS=\"-D$TEST_FLAGS\""
  cd $ORIGINAL_PATH
  cp $BUILD_PATH/unit-test bin/unit-test.run
else
  echo "Unknown target $COMMAND"
  exit
fi
