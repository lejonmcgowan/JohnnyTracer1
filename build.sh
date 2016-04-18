#!/bin/bash

if [ $1 = "clean" ]; then 
	rm -rf build
else
	rootpath=$(pwd)
	rootpath="$rootpath/"
	finalpath="$rootpath$3"

	echo "FINAL PATH: $finalpath"

	if [ ! -d "build" ]; then
		mkdir build
		cd build
		cmake -DCMAKE_BUILD_TYPE=Debug ..
	else
		cd build
	fi
		make RayTracer473 -j4
		cd bin
	./RayTracer473 $1 $2 $finalpath $4
fi






