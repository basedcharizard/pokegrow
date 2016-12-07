CC=g++
CFLAGS=-Wall -c
LIBS=-lncurses 
TARGET=build/pb
SOURCES=$(wildcard src/*.cpp)
OBJECTS=$(patsubst %.cpp, %.o, $(SOURCES))

all: $(TARGET)

$(TARGET): $(OBJECTS)
	@mkdir -p build
	$(CC) $(LIBS) -o $@ $(OBJECTS)
$(OBJECTS): $(SOURCES)

.PHONY: clean

clean: 
	rm -rf $(OBJECTS) $(TARGET)
