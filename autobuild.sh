#!/bin/bash

set -e

if [ ! -d `pwd`/build ]; then
    mkdir `pwd`/build
fi

if [ ! -d `pwd`/include ]; then
    mkdir `pwd`/include
fi

for header in `ls *.h`
do
    cp $header `pwd`/include
done

rm -rf `pwd`/build/*

cd `pwd`/build &&
    cmake .. &&
    make

cd ..
