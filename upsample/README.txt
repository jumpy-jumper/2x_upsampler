Compilation instructions:
    make            creates file "main", which is the upscaling 
                    program
    make test       runs gtest (requires gtest)
    make coverage   creates directory "out" with html file with 
                    coverage report (requires gtest, gcov, lcov)

The program implements the specifications detailed in
the assignment hand-out.

There are no known bugs.

The scaling factor is assumed to be 2x, and the image size
is assumed to be 256x256, as specified in the assignment
specification.

I have liberally used a variety of STL data structures
to attempt to optimize execution time.

Gitlab repository: https://gitlab.com/julio_sarda-perez/cop4531p2
Gtest output: gtest.png
Coverage report: lcov.png