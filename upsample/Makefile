main: upsample.cpp
	g++ -std=c++11 upsample.cpp -lm -o main
test: unit_test.cpp upsample.cpp
	g++ -std=c++11 unit_test.cpp -lgtest -lgtest_main -lpthread
	./a.out
	rm ./a.out
coverage: unit_test.cpp upsample.cpp
	g++ -o main -fprofile-arcs -ftest-coverage unit_test.cpp -lgtest -lgtest_main -lpthread
	./main
	gcov unit_test.cpp
	lcov --capture --directory . --output-file main_coverage.info
	genhtml main_coverage.info --output-directory out
	rm *gcov
	rm *gcno
	rm *gcda
	rm *info
	rm main
diff:
	./main ../test_cases/sample1_input.dat sample1_output.dat
	../diff/diff ../test_cases/sample1_original.dat out_nn
	../diff/diff ../test_cases/sample1_original.dat out_bilinear
	../diff/diff ../test_cases/sample1_original.dat out_bicubic
	./main ../test_cases/sample2_input.dat sample2_output.dat
	../diff/diff ../test_cases/sample2_original.dat out_nn
	../diff/diff ../test_cases/sample2_original.dat out_bilinear
	../diff/diff ../test_cases/sample2_original.dat out_bicubic
clean:
	rm -f *.dat
	rm -f out_*
	rm -f main
	rm -f *gcov
	rm -f *gcno
	rm -f *gcda
	rm -f *info
	rm -rf out