#!/bin/bash

HERE="`dirname "$0"`"
HERE_REAL="`(cd -L "$HERE"; pwd)`"

mkdir -p jni

cd "$HERE"
test -L jni/Sources && rm jni/Sources
ln -s "$HERE_REAL"/.. jni/Sources
