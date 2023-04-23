# !/bin/bash

cd build

make -j48

echo "read parameters from config file"
source ../config.conf

outputFileName="output_nOE${numberofevents}"

./sim -v -df > "${outputFileName}.txt" &
