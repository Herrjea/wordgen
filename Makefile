
SRC = src
INC = include
OBJ = obj
BIN = bin
LIB = lib

CXX = g++
CPPFLAGS = -Wall -g -c -std=c++11 -I$(INC)

all: $(BIN)/main

$(BIN)/main: $(OBJ)/main.o $(OBJ)/wordgen.o
	$(CXX) $^ -o $@

$(OBJ)/%.o: $(SRC)/%.cpp $(LIB)/wordgen.h
	$(CXX) $(CPPFLAGS) $< -o $@

#$(OBJ)/main.o: $(SRC)/main.cpp $(LIB)/wordgen.h
#	$(CXX) $(CPPFLAGS) $< -o $@

#$(OBJ)/wordgen.o: $(SRC)/wordgen.cpp $(LIB)/wordgen.h
#	$(CXX) $(CPPFLAGS) $< -o $@

clean:
	rm bin/* obj/*
