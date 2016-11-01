#!/bin/sh

WORKP=$PWD
g++ Gen_data.cpp -O2 -o Gen_data.exe
./Gen_data.exe

cd ..
BFP=$PWD
COMMONFILESP=$PWD/Common\ Files
DJBFP=$BFP/DBF
SBFP=$BFP/ShBF
KBFP=$BFP/vBF

BOBHASH="$COMMONFILESP/BOBHash.o"
RAWDATA="$COMMONFILESP/rawData.o"
ARRAYBOOL="$COMMONFILESP/array_bool.o"
DJBF=$DJBFP/djbf.o
SBF=$SBFP/shiftbf.o
KBF=$KBFP/kbf.o

cd "$COMMONFILESP"
g++ -c array_bool.cpp -O2
g++ -c rawData.cpp -O2
g++ -c BOBHash.cpp -O2
cd ..

cd $DJBFP
g++ -c djbf.cpp -O2
cd ..

cd $KBFP
g++ -c kbf.cpp -O2
cd ..

cd $SBFP
g++ -c shiftbf.cpp -O2
cd ..

cd $WORKP
g++ main.cpp $DJBF $SBF $KBF "$BOBHASH" "$RAWDATA" "$ARRAYBOOL" -O2 -o main

echo begin running...
./main

