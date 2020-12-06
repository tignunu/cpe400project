#makefile for CPE 400 Project 2020
#Dynamic Routing Mechanism Design in Faulty Network

#Mari Trombley, Skylar Glock, Henry Strum

TARGET = Network #target program
LIBS = #list of external libraries required to link against
HEADERS = node.h #list of all header files
SRCS = main.cpp  #list of all source files
OBJECTS := $(patsubst %.cpp,%.o,$(SRCS)) #makes all source files objects
CXX = g++ #compiler command to be used
CXX_FLAGS = -Wall -std=c++11 #compilation flags to be used 

#Rule for cleaning
.PHONY: default all clean

#Rule that defers make all to the TARGET
all: $(TARGET)

#Rule to compile single object file
%.o: %.cpp $(HEADERS)
	$(CXX) $(CXX_FLAGS) -c $< -o $@

#Rule that makes all object files in the OBJECTS list, then links thenm all to produce TARGET executable
$(TARGET): $(OBJECTS)
	$(CXX) $(CXX_FLAGS) $(OBJECTS) $(LIBS) -o $@

#Rule to clean up the build
clean:
	-rm -f *.o
	-rm -f $(TARGET)