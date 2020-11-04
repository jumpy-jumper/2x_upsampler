#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

const int INPUT_SIZE = 256;

void read_input(int dest[][INPUT_SIZE], char* in) {
    ifstream inf;
    inf.open(in);

    cout << in << endl;

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

int main(int argc, char** argv) {
    if (argc != 3) {
        cerr << "Wrong number of arguments, expected 2" << endl;
        return(1);
    }

    int input[INPUT_SIZE][INPUT_SIZE];
    read_input(input, argv[1]);

    int output[INPUT_SIZE*2][INPUT_SIZE*2];
}