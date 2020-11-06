main: main.cpp diff.cpp
	g++ main.cpp -lm -o main -std=c++98
	g++ diff.cpp -o diff
test:
	make
	./main sample1_input.dat sample1_output.dat
	./diff sample1_original.dat out_nn
	./diff sample1_original.dat out_bilinear
	./diff sample1_original.dat out_bicubic
	./main sample2_input.dat sample2_output.dat
	./diff sample2_original.dat out_nn
	./diff sample2_original.dat out_bilinear
	./diff sample2_original.dat out_bicubic
