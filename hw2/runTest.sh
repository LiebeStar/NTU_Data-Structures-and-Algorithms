#!/bin/bash
make
if [ ! -e output ]
then
	mkdir output
fi

./a.out public_data.txt <1in.txt >output/1out.txt
./a.out public_data.txt <2in.txt >output/2out.txt
./a.out public_data.txt <3in.txt >output/3out.txt
./a.out public_data.txt <4in.txt >output/4out.txt

diff 1out.txt output/1out.txt
diff 2out.txt output/2out.txt
diff 3out.txt output/3out.txt
diff 4out.txt output/4out.txt