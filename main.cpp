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
#include <math.h>
using namespace std;

const int INPUT_SIZE = 256;

/*
    Nearest Neighbor is the simplest upscaling algorithm.
    Creates a 2x2 matrix for every individual pixel in the original image.

    This implementation is O(n), where n is the number of pixels in the 
    original image (INPUT_SIZE^2).

    @param in the input image.
    @param out the output image.
*/
void nearest_neighbor(int in[][INPUT_SIZE], int out[][INPUT_SIZE*2]) {
    for (int i = 0; i < INPUT_SIZE; i++) {
        for (int j = 0; j < INPUT_SIZE; j++) {
            out[i*2][j*2] = in[i][j];
            out[i*2+1][j*2] = in[i][j];
            out[i*2][j*2+1] = in[i][j];
            out[i*2+1][j*2+1] = in[i][j];
        }
    }
}

/*
    Linear and bilinear interpolation functions.
*/

double lerp(double p0, double p1, double k) {
    return p0 + (p1 - p0) * k;
}

double blerp(double p00, double p10, double p01, double p11, double kx, double ky) {
    return lerp (lerp(p00, p10, kx), lerp(p01, p11, kx), ky);
}

/*
    Bilinear upscaling.
    Uses linear interpolation to calculate the output image.

    This implementation is O(n), where n is the number of pixels in the 
    original image (INPUT_SIZE^2).

    @param in the input image.
    @param out the output image.
*/
void bilinear(int in[][INPUT_SIZE], int out[][INPUT_SIZE*2]) {
    for(int y = 0; y < INPUT_SIZE * 2; y++) {
        for (int x = 0; x < INPUT_SIZE * 2; x++) {
            double gx = (x - 0.5) * 0.5;
            double gy = (y - 0.5) * 0.5;
            int gxi[2] = {max((int)gx, 0), min((int)gx + 1, INPUT_SIZE - 1)};
            int gyi[2] = {max((int)gy, 0), min((int)gy + 1, INPUT_SIZE - 1)};

            int c00 = in[gyi[0]][gxi[0]];
            int c10 = in[gyi[0]][gxi[1]];
            int c01 = in[gyi[1]][gxi[0]];
            int c11 = in[gyi[1]][gxi[1]];

            out[y][x] = blerp(c00, c10, c01, c11, gx - (int)gx, gy - (int)gy);
        }
    }
}

/*
    Cubic and bicubic interpolation functions.
*/

double cerp(double p0, double p1, double p2, double p3, double k) {
    double a = -0.5 * p0 + 1.5 * p1 + -1.5 * p2 + 0.5 * p3;
    double b = p0 + -2.5 * p1 + 2 * p2 + -0.5 * p3;
    double c = -0.5 * p0 + 0.5 * p2;
    return a * pow(k, 3) + b * pow(k, 2) + c * k + p1;
}

double bcerp(double p00, double p01, double p02, double p03, 
            double p10, double p11, double p12, double p13, 
            double p20, double p21, double p22, double p23, 
            double p30, double p31, double p32, double p33, 
            double kx, double ky) {
    return cerp ( cerp (p00, p01, p02, p03, ky),
                  cerp (p10, p11, p12, p13, ky),
                  cerp (p20, p21, p22, p23, ky),
                  cerp (p30, p31, p32, p33, ky),
                  kx );
}

/*
    Bicubic upscaling.
    Uses cubic interpolation to calculate the output image.

    This implementation is O(n), where n is the number of pixels in the 
    original image (INPUT_SIZE^2).

    @param in the input image.
    @param out the output image.
*/
void bicubic(int in[][INPUT_SIZE], int out[][INPUT_SIZE*2]) {
    for (int x = 0; x < INPUT_SIZE * 2; x++) {
        for (int y = 0; y < INPUT_SIZE * 2; y++) {
            double gx = (x - 0.5) * 0.5;
            double gy = (y - 0.5) * 0.5;
            int gxi = (int)gx;
            int gyi = (int)gy;

            int c00 = in[max(gyi-1, 0)][max(gxi-1, 0)];
            int c01 = in[gyi][max(gxi-1, 0)];
            int c02 = in[min(gyi+1, INPUT_SIZE - 1)][max(gxi-1, 0)];
            int c03 = in[min(gyi+2, INPUT_SIZE - 1)][max(gxi-1, 0)];
            int c10 = in[max(gyi-1, 0)][gxi];
            int c11 = in[gyi][gxi];
            int c12 = in[min(gyi+1, INPUT_SIZE - 1)][gxi];
            int c13 = in[min(gyi+2, INPUT_SIZE - 1)][gxi];
            int c20 = in[max(gyi-1, 0)][min(gxi+1, INPUT_SIZE - 1)];
            int c21 = in[gyi][min(gxi+1, INPUT_SIZE - 1)];
            int c22 = in[min(gyi+1, INPUT_SIZE - 1)][min(gxi+1, INPUT_SIZE - 1)];
            int c23 = in[min(gyi+2, INPUT_SIZE - 1)][min(gxi+1, INPUT_SIZE - 1)];
            int c30 = in[max(gyi-1, 0)][min(gxi+2, INPUT_SIZE - 1)];
            int c31 = in[gyi][min(gxi+2, INPUT_SIZE - 1)];
            int c32 = in[min(gyi+1, INPUT_SIZE - 1)][min(gxi+2, INPUT_SIZE - 1)];
            int c33 = in[min(gyi+2, INPUT_SIZE - 1)][min(gxi+2, INPUT_SIZE - 1)];

            out[y][x] = bcerp (c00, c01, c02, c03,
                               c10, c11, c12, c13,
                               c20, c21, c22, c23,
                               c30, c31, c32, c33,
                               gx - gxi, gy - gyi);
        }
    }
}

/*
    Reads image information from a byte array from given file.
    The image is expected to be of size INPUT_SIZE^2.

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
    be most performant.
*/
int main(int argc, char** argv) {
    if (argc == 1) {

    } else if (argc == 3) {
        int input[INPUT_SIZE][INPUT_SIZE];
        read_from_file(input, argv[1]);

        int output[INPUT_SIZE*2][INPUT_SIZE*2];
        nearest_neighbor(input, output);
        output_to_file(output, (char*)"out_nn");
        bilinear(input, output);
        output_to_file(output, (char*)"out_bilinear");
        bicubic(input, output);
        output_to_file(output, (char*)"out_bicubic");
    } else {
        cerr << "Wrong number of arguments, expected 0 or 2" << endl;
        return(1);
    }
}