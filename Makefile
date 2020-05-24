STD = -std=c++17
WARN = -Wall -Wextra
OPT = -O2
GCC = g++ $(OPT) $(STD) $(WARN)
VERSION = 1.0
FLAGS = -shared -Wl,-soname,
LIB = libaparser.so$(VERSION)

SRC = src/*.cpp
INCLUDE = include/*.h
FILES = $(SRC) $(INCLUDE) main.cpp
INSTALL_FILES = $(SRC) $(INCLUDE)

install: $(FILES)
	$(GCC) -fPIC -c $(INSTALL_FILES)
	$(GCC) $(FLAGS) $(LIB) -o $(LIB) *.o

example: $(FILES)
	$(GCC) $(SRC) -o main


clean:
	rm -fr include/*.gch src/*.gch *.o 
