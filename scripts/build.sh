#! /usr/bin/env bash

# define folder locations
HOME_DIR=~/Documents/dev-projects/personal/cpp-sandbox
BUILD_DIR=$HOME_DIR/build
PROJECT_DIR=$HOME_DIR/src

# check if there is a build directory
if [ ! -d "$BUILD_DIR" ]; then
    mkdir $BUILD_DIR
fi

g++ -o $BUILD_DIR/$@.out $PROJECT_DIR/$@/main.cpp
