# neste template de Makefile so muda a lista
# dos SOURCES e o nome do EXECUTABLE.

CC=g++
CFLAGS=-c -Wall -Weffc++ -pedantic -std=c++0x  
LDFLAGS= -lgtest -lgsl -lgslcblas -lm -lpthread -lpstatistics -lboost_program_options

SOURCES=   main.cpp 
 
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=tests


all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC)  $(OBJECTS) -o $@ $(LDFLAGS)

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

 
