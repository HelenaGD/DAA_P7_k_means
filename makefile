CXX		  := g++
CXX_FLAGS := -std=c++17 -w -lstdc++fs
TEST_FLAGS := -pthread -lgtest -lpthread

BIN		:= bin
SRC		:= src
INCLUDE	:= include
LIB		:= lib
TEST	:= tests

LIBRARIES	:=
EXECUTABLE	:= simulator
TESTER	:= tester

ARG := instances/prob1.txt

all: $(BIN)/$(EXECUTABLE)

run: clean all	
	./$(BIN)/$(EXECUTABLE) $(ARG)

$(BIN)/$(EXECUTABLE)  $(ARG): $(SRC)/*.cc
	$(CXX) $(CXX_FLAGS) -I$(INCLUDE) -L$(LIB) $^ -o $@ $(LIBRARIES) 

test: clean $(BIN)/$(TESTER)
	./$(BIN)/$(TESTER)

$(BIN)/$(TESTER): $(TEST)/*.cc
	$(CXX) $(CXX_FLAGS) -I$(INCLUDE) -L$(LIB) $^ -o $@ $(LIBRARIES) $(TEST_FLAGS)

exe: all
	./$(BIN)/$(EXECUTABLE) $(ARG)

clean:
	-rm $(BIN)/*

#.PHONY: clean