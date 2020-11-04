#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

const int INPUT_SIZE = 256;

void nearest_neighbor(int in[][INPUT_SIZE], int out[][INPUT_SIZE*2]) {
    for (int i = 0; i < INPUT_SIZE * 2; i++) {
        for (int j = 0; j < INPUT_SIZE * 2; j++) {
            out[i][j] = in[i/2][j/2];
        }
    }
}

void read_from_file(int dest[][INPUT_SIZE], char* file) {
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
}

void output_to_file(int out[][INPUT_SIZE*2], char* file) {
    ofstream outf;
    outf.open(file);

    for (int i = 0; i < INPUT_SIZE * 2; i++) {
        for (int j = 0; j < INPUT_SIZE * 2; j++) {
            outf << (j == 0 ? "" : ",") << out[i][j];
        }
        outf << '\n';
    }

    outf.close();
}

int main(int argc, char** argv) {
    if (argc == 1) {

    } else if (argc == 3) {
        int input[INPUT_SIZE][INPUT_SIZE];
        read_from_file(input, argv[1]);

        int output[INPUT_SIZE*2][INPUT_SIZE*2];
        nearest_neighbor(input, output);
        output_to_file(output, argv[2]);
    } else {
        cerr << "Wrong number of arguments, expected 0 or 2" << endl;
        return(1);
    }
}