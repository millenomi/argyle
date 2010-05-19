#!/bin/bash

cd "`dirname "$0"`"
for i in *.cpp *.h; do
	if [ -L "$i" ]; then
		echo " - (cleaning symlinks) - " rm "$i"
		rm "$i"
	fi
done
