#!/bin/bash

build_path=build

if [ -d "$build_path" ]; 
then
    cd $build_path && rm -rf * && cd ..
else
    mkdir $build_path
    echo "Generating build path $build_path"
fi

echo "joining build path $build_path"

export QT_SELECT=qt5
echo "Executing qmake and building"
cd $build_path && qmake ../symkit.pro -o Makefile -spec linux-g++ && make
