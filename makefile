FLAGS = -Wall -Werror -ansi -pedantic
bin/rshell: all
	g++ main.o programCall.o programQueue.o filename.o $(FLAGS) -o bin/rshell
all: src/main.cpp src/programCall.cpp src/programQueue.cpp
	if [ ! -d "bin" ]; then mkdir bin; fi
	g++ -c src/main.cpp src/programCall.cpp src/programQueue.cpp src/filename.cpp $(FLAGS)
