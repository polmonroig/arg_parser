STD = -std=c++17
WARN = -Wall -Wextra
OPT = -O2
GCC = g++ $(OPT) $(STD) $(WARN)
VERSION = 1.0
FLAGS = -shared -Wl,-soname,
LIB = libaparser.so.$(VERSION)
INSTALL_PATH = /usr/local/lib/
LINK = ln -sf

SRC = src/*.cpp
INCLUDE = include/*.h
FILES = $(SRC) $(INCLUDE) main.cpp
INSTALL_FILES = $(SRC) $(INCLUDE)

install: $(FILES)
	$(GCC) -fPIC -c $(SRC)
	$(GCC) $(FLAGS) -o $(LIB) *.o
	mv $(LIB) $(INSTALL_PATH)
	$(LINK) $(INSTALL_PATH)$(LIB) $(INSTALL_PATH)libaparser.so.1
	$(LINK) $(INSTALL_PATH)$(LIB) $(INSTALL_PATH)libaparser.so
	cp $(INCLUDE) /usr/include

example: $(FILES)
	$(GCC) $(SRC) main.cpp -o main


clean:
	rm -fr include/*.gch src/*.gch *.o
