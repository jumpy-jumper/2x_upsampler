main: main.cpp diff.cpp
	g++ main.cpp -lm -o main -std=c++98
	g++ diff.cpp -o diff