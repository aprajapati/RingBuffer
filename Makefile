%.o=%.cpp

$CC=g++
CFLAGS=-c -Wall -std=c++11
LDFLAGS=-lstdc++
SOURCES=RingBuffer.cpp
OBJECTS=$(SOURCES:.cpp=.o)
	EXECUTABLE=RingBuffer

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf *.o

