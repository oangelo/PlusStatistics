#include <random>
#include "../statistics.h" 

TEST(statistics, Mean_and_std){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<> d(5, 2);
    Mean<double> mean;
    StDeviation<double> std;
    std::cout << mean << std::endl;
    std::cout << std << std::endl;
    EXPECT_NEAR(mean, 5, 0.01);
    EXPECT_NEAR(std, 2, 0.01);
}
