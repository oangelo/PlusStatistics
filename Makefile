cc = g++ 
CFLAGS=  -std=c++0x  -frounding-math -c -Wall -O3 -march=native #-pg -g
LDFLAGS=-lCGAL -lCGAL_Core -lgmp -lboost_system -lboost_thread -lstdc++ -lm
SOURCES = src/histogram.cpp src/statistics.cpp src/main.cpp  src/utils/utils.cpp

OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE=pstatistics 


all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC)  $(OBJECTS) -o $@ $(LDFLAGS) #-pg 

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@  

install:
	cp $(EXECUTABLE) /usr/local/bin
