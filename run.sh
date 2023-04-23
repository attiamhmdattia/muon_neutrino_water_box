# !/bin/bash

cd build

make -j48

echo "read parameters from config file"
source ../config.conf

outputFileName="output_nOE${numberofevents}"

for i in {1..40};
do
    (
        mkdir neutrino_water${i}
        cd neutrino_water${i}
        cmake ../..
        make -j48
        ./sim -v -f ../../config.conf
        mv "${outputFileName}.root" "${outputFileName}_run_${i}.root"
        echo "${outputFileName}_run_${i}.root is created"
        cd ..
    ) > "${outputFileName}_run_${i}.txt" &

    sleep 10
done

jobs