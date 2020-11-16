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

bool identical_images(vector<vector<int>>& img1, vector<vector<int>>& img2) {
    if (img1.size() != img2.size()) {
        return false;
    } else if (img1[0].size() != img2[0].size()) {
        return false;
    } else {
        for (int y = 0; y < img1.size(); y++) {
            for (int x = 0; x < img1[0].size(); x++) {
                if (img1[y][x] != img2[y][x]) {
                    return false;
                }
            }
        }
    }

    return true;
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

TEST(FileIOTest,RandomImageTest) {
    int height = rand() % 500 + 500;
    int width = rand() % 500 + 500;
    vector<vector<int>> img = empty_image(height, width);
    randomize_image(img);

    output_to_file(img, (char*)"test.dat");
    vector<vector<int>> img2;
    read_from_file(img2, (char*)"test.dat");
    remove("test.dat");

    EXPECT_TRUE(identical_images(img, img2));
}

int main(int argc,char**argv) {
    srand(time(NULL));
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}