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
clean:
	rm -f *.dat
	rm -f out_*
	rm -f main
	rm -f *gcov
	rm -f *gcno
	rm -f *gcda
	rm -f *info
	rm -rf out