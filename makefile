CC=g++ -std=c++0x
CFLAGS=-c -Wall
LDFLAGS=
SOURCES=ImageProcessing.cpp Image.cpp Iterator.cpp
DEPS=Image.h 
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=imageops

all: $(SOURCES) $(EXECUTABLE)
    
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@
clean:
	@rm -f *.o 


