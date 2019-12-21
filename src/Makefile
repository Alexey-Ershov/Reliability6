HEADER = smart-ptr.hpp
MAIN = main.cpp
OUTPUT = smart-ptr
CFLAGS = -O2 -std=c++17 -Wall
COMPILER = g++-9

.PHONY: all clean

all: main

main.o: $(HEADER) $(MAIN)
	$(COMPILER) $(CFLAGS) \
	            -c \
	            -o main.o \
	            $(MAIN)

main: main.o
	$(COMPILER) -o $(OUTPUT) main.o

clean:
	rm -rf $(OUTPUT) *.o
