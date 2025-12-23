CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17

SRC = src/main.cpp src/shell.cpp
INC = -Iinclude

OUT = mini-shell

all:
	$(CXX) $(CXXFLAGS) $(SRC) $(INC) -o $(OUT)

clean:
	rm -f $(OUT)
