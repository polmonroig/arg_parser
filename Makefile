STD = -std=c++17
FLAGS = -Wall -Wextra
OPT = -O2
GCC = g++ $(OPT) $(STD) $(FLAGS)



SRC = src/*.cpp main.cpp
INCLUDE = include/*.h
FILES = $(SRC) $(INCLUDE)


all: main


main: $(FILES)
	$(GCC) $(SRC) -o main
