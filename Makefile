# - headers/
#     - *.h
# - source/
#     - *.c
#     - *.cpp
# - obj/
#     - *.o
# - main

TARGET := program.exe
SOURCES := $(wildcard source/*.c source/*.cpp)
OBJECTS := $(patsubst source%,obj%, $(patsubst %.c,%.o, $(patsubst %.cpp,%.o,$(SOURCES))))

INCLUDE := -I.
LIBPATH :=
LIBS :=

FLAGS := -Wall
CCFLAGS := $(FLAGS) -std=c99
CXXFLAGS := $(FLAGS)

CC := gcc
CXX := g++

all: $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(INCLUDE) $(OBJECTS) -o $(TARGET) $(LIBPATH) $(LIBS)

%.o: ../source/%.c
	@ mdkir -p obj
	$(CC) $(CCFLAGS) $(INCLUDE) -c $< -o $@

%.o: ../source/%.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -o $@

clean:
	rm -rf obj/*
	rm -f $(TARGET)

run:
	./$(TARGET)