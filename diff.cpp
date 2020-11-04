#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cmath>
using namespace std;

const int INPUT_SIZE = 512;

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

int diff(int first[][INPUT_SIZE], int second[][INPUT_SIZE]) {
    int sum = 0;
    for (int i = 0; i < INPUT_SIZE; i++) {
        for (int j = 0; j < INPUT_SIZE; j++) {
            sum += abs(first[i][j] - second[i][j]);
        }
    }
    return sum;
}

int main(int argc, char** argv) {
    if (argc == 3) {
        int in1[INPUT_SIZE][INPUT_SIZE];
        read_from_file(in1, argv[1]);

        int in2[INPUT_SIZE][INPUT_SIZE];
        read_from_file(in2, argv[2]);

        cout << "Diff: " << diff(in1, in2) << endl;
    } else {
        cerr << "Wrong number of arguments, expected 2" << endl;
        return(1);
    }
}