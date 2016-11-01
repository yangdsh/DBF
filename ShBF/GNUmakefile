CommonFiles = ../"Common Files"

all: main.exe

shiftbf.o: shiftbf.cpp shiftbf.hpp
	g++ -c shiftbf.cpp

main.exe: main.cpp shiftbf.o
	g++ main.cpp shiftbf.o $(CommonFiles)/rawData.o $(CommonFiles)/array_bool.o $(CommonFiles)/BOBHash.o -o $@

clean:
	del kbf.o
	del main.exe