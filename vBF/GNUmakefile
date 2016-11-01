CommonFiles = ../"Common Files"

all: main.exe

kbf.o: kbf.cpp kbf.hpp
	g++ -c kbf.cpp

main.exe: main.cpp kbf.o
	g++ main.cpp kbf.o $(CommonFiles)/rawData.o $(CommonFiles)/array_bool.o $(CommonFiles)/BOBHash.o -o $@

clean:
	del kbf.o
	del main.exe