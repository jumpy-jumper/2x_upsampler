#define UNIT_TEST_CPP
#include "gtest/gtest.h"
#include <vector>
#include "upsample.cpp"
using namespace std;

vector<vector<int>> empty_image(int height, int width) {
    vector<vector<int> > ret;
    ret.resize(height);
    for (int y = 0; y < height; y++) {
        ret[y].resize(width);
    }
    return ret;
}

void randomize_image(vector<vector<int>>& img) {
    for (int y = 0; y < img.size(); y++) {
        for (int x = 0; x < img[0].size(); x++) {
            img[y][x] = rand() % 256;
        }
    }
}

TEST(NearestNeighborTest,RandomImageTest) {
    int height = rand() % 500 + 500;
    int width = rand() % 500 + 500;

    vector<vector<int>> in = empty_image(height, width);
    randomize_image(in);
    vector<vector<int>> out = empty_image(height * 2, width * 2);
    nearest_neighbor(in, out);
}

TEST(BilinearTest,RandomImageTest) {
    int height = rand() % 500 + 500;
    int width = rand() % 500 + 500;

    vector<vector<int>> in = empty_image(height, width);
    randomize_image(in);
    vector<vector<int>> out = empty_image(height * 2, width * 2);
    bilinear(in, out);
}

TEST(BicubicTest,RandomImageTest) {
    int height = rand() % 500 + 500;
    int width = rand() % 500 + 500;

    vector<vector<int>> in = empty_image(height, width);
    randomize_image(in);
    vector<vector<int>> out = empty_image(height * 2, width * 2);
    bicubic(in, out);
}

int main(int argc,char**argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}