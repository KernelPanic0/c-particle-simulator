#!/bin/bash
# set -euo pipefail

if [ -z "$1" ]
  then
    echo "no file to build as command line argument"
    exit 1
fi

BUILD_SRC=$*
WORKING_DIR=`pwd`
OUT_DIR=$WORKING_DIR/out
RAYLIB=/opt/pop/raylib
RAYGUI=/opt/pop/raygui
EMSDK=/opt/pop/emsdk

if [ ! -d "$OUT_DIR" ]; then
  mkdir "$OUT_DIR"
  echo "Directory '$OUT_DIR' created"
else
  echo "Directory '$OUT_DIR' already exists"
fi

# Get EMSDK on the PATH
cd $EMSDK
source emsdk_env.sh

# Get into the /src folder
cd $WORKING_DIR

# Build to Web Assembly
emcc -o $OUT_DIR/index.html \
    $BUILD_SRC $(find src -name "*.c" ! -name "main.c") -Os -Wall $RAYLIB/src/libraylib.a \
    -I. -I $RAYLIB/src/ \
    -I $RAYGUI/src/ -I $RAYGUI/ \
    -I ./include \
    -L. -L $RAYLIB/src/ \
    -s USE_GLFW=3 \
    -s ASYNCIFY \
    -s ALLOW_MEMORY_GROWTH \
    --shell-file $WORKING_DIR/shell.html \
    --preload-file resources \
    -s TOTAL_STACK=64MB \
    -s INITIAL_MEMORY=128MB \
    -s ASSERTIONS \
    -DPLATFORM_WEB

# Run the game
