CommonFiles = "../Common Files"

all: main.exe

djbf.o: djbf.cpp djbf.hpp
	g++ -c djbf.cpp

main.exe: main.cpp djbf.o
	g++ main.cpp djbf.o $(CommonFiles)/rawData.o $(CommonFiles)/array_bool.o $(CommonFiles)/BOBHash.o -o $@

clean:
	del djbf.o
	del main.exe