Common_Files_PATH = ../"Common Files"

DJBF_PATH = ../4-djbf
KBF_PATH = ../k-bf
SHIFTBF_PATH = ../shiftbf

CommonFiles = $(Common_Files_PATH)/array_bool.o $(Common_Files_PATH)/rawData.o $(Common_Files_PATH)/BOBHash.o 
BFFiles = $(DJBF_PATH)/djbf.o $(KBF_PATH)/kbf.o $(SHIFTBF_PATH)/shiftbf.o

all: main.exe

main.exe: main.cpp
	g++ main.cpp $(BFFiles) $(CommonFiles) -o $@

clean:
	del main.exe