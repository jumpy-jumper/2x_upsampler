/*
    ====================================================================
    Code by Julio Sarda-Perez for COP4531 at Florida State University.
    Professor: Piyush Kumar.

    This file implements various upscaling algorithms.
    ====================================================================
*/

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

const int INPUT_SIZE = 256;

/*
    Nearest Neighbor is the simplest and worst upscaling algorithm.
    Creates a 2x2 matrix for every individual pixel in the original image.

    This implementation is O(n), where n is the number of pixels in the 
    original image.

    @param in the input image.
    @param out the output image.
*/
void nearest_neighbor(int in[][INPUT_SIZE], int out[][INPUT_SIZE*2]) {
    for (int i = 0; i < INPUT_SIZE * 2; i++) {
        for (int j = 0; j < INPUT_SIZE * 2; j++) {
            out[i][j] = in[i/2][j/2];
        }
    }
}

/*
    Bilinear interpolation.
    Uses linear interpolation to fill in missing pixels in
    output image.

        a b  ->   a _ _ b
        c d       _ _ _ _
                  _ _ _ _
                  c _ _ d

    Every 2x2 matrix in the original image is turned into a
    4x4 matrix on the output image.

    @param in the input image.
    @param out the output image.
*/
void bilinear(int in[][INPUT_SIZE], int out[][INPUT_SIZE*2]) {
    for (int i = 0; i < INPUT_SIZE / 2; i++) {
        for (int j = 0; j < INPUT_SIZE / 2; j++) {
            // fill in known pixels a, b, c, d

            out[i*4][j*4] = in[i*2][j*2]; // a
            out[i*4+3][j*4] = in[i*2+1][j*2]; // b
            out[i*4][j*4+3] = in[i*2][j*2+1]; // c
            out[i*4+3][j*4+3] = in[i*2+1][j*2+1]; // d

            // horizontal interpolation to calculate pixels between a-b and c-d
            out[i*4+1][j*4] = in[i*2][j*2] + (in[i*2+1][j*2] - in[i*2][j*2]) / 3;
            out[i*4+2][j*4] = in[i*2][j*2] + (in[i*2+1][j*2] - in[i*2][j*2]) / 3 * 2;
            out[i*4+1][j*4+3] = in[i*2][j*2+1] + (in[i*2+1][j*2+1] - in[i*2][j*2+1]) / 3;
            out[i*4+2][j*4+3] = in[i*2][j*2+1] + (in[i*2+1][j*2+1] - in[i*2][j*2+1]) / 3 * 2;

            // vertical interpolation to calculate pixels between a-c and b-d
            out[i*4][j*4+1] = in[i*2][j*2] + (in[i*2][j*2+1] - in[i*2][j*2]) / 3;
            out[i*4][j*4+2] = in[i*2][j*2] + (in[i*2][j*2+1] - in[i*2][j*2]) / 3 * 2;
            out[i*4+3][j*4+1] = in[i*2+1][j*2] + (in[i*2+1][j*2+1] - in[i*2+1][j*2]) / 3;
            out[i*4+3][j*4+2] = in[i*2+1][j*2] + (in[i*2+1][j*2+1] - in[i*2+1][j*2]) / 3 * 2;

            // horizontal interpolation to calculate remaining pixels
            out[i*4+1][j*4+1] = out[i*4][j*4+1] + (out[i*4+3][j*4+1] - out[i*4][j*4+1]) / 3;
            out[i*4+2][j*4+1] = out[i*4][j*4+1] + (out[i*4+3][j*4+1] - out[i*4][j*4+1]) / 3 * 2;
            out[i*4+1][j*4+2] = out[i*4][j*4+2] + (out[i*4+3][j*4+2] - out[i*4][j*4+2]) / 3;
            out[i*4+2][j*4+2] = out[i*4][j*4+2] + (out[i*4+3][j*4+2] - out[i*4][j*4+2]) / 3 * 2;
        }
    }
}

/*
    Reads image information from a byte array from given file.
    The image is expected to be of size INPUT_SIZE x INPUT_SIZE.

    Returns true if image was successfully read, and false otherwise.

    @param dest 2D int array to copy image to.
    @param file path to file.
*/
bool read_from_file(int dest[][INPUT_SIZE], char* file) {
    ifstream inf;
    inf.open(file);

    string line;
    for (int i = 0; getline(inf, line); i++) {
        istringstream iss(line);
        string item;
        for (int j = 0; getline(iss, item, ','); j++) {
            istringstream(item) >> dest[i][j];
        }
    }

    inf.close();

    return true;
}

/*
    Outputs image information to given file.

    Returns true if file was successfully written to, and false otherwise.

    @param out 2D int array containing image to output.
    @param file path to file.
*/
bool output_to_file(int out[][INPUT_SIZE*2], char* file) {
    ofstream outf;
    outf.open(file);

    for (int i = 0; i < INPUT_SIZE * 2; i++) {
        for (int j = 0; j < INPUT_SIZE * 2; j++) {
            outf << (j == 0 ? "" : ",") << out[i][j];
        }
        outf << '\n';
    }

    outf.close();

    return true;
}

/*
    If the program is executed with no arguments, run unit tests.

    Otherwise if the program is executed with two arguments, read in
    image information from argument one and output an upscaled image
    to argument two, using the upscaling algorithm that is expected to
    be most performant.
*/
int main(int argc, char** argv) {
    if (argc == 1) {

    } else if (argc == 3) {
        int input[INPUT_SIZE][INPUT_SIZE];
        read_from_file(input, argv[1]);

        int output[INPUT_SIZE*2][INPUT_SIZE*2];
        bilinear(input, output); // expected to produce best results
        output_to_file(output, argv[2]);
    } else {
        cerr << "Wrong number of arguments, expected 0 or 2" << endl;
        return(1);
    }
}