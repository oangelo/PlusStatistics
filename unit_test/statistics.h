#include "../histogram.h"
#include "../statistics.h"

TEST(histogram, constructor_values){
    std::vector<double> values;
    values.push_back(1);
    values.push_back(4);
    Histogram histogram(5, values);
    EXPECT_NEAR(histogram.get_max(), 4, 0.000001);
    EXPECT_EQ(histogram.get_min(), 1);
    EXPECT_EQ(histogram.get_bins_amount(), 5);
    EXPECT_EQ(histogram[0], 1);
    EXPECT_EQ(histogram[4], 1);
}

TEST(histogram, constructor_single){
    double min = 0.5, max = 4.6;
    Histogram histogram(5, min, max);
    EXPECT_EQ(histogram.get_max(), 4.6);
    EXPECT_EQ(histogram.get_min(), 0.5);
    EXPECT_EQ(histogram.get_bins_amount(), 5);
}

TEST(histogram, values){
    std::vector<double> values;
    values.push_back(1);
    values.push_back(2);
    values.push_back(3);
    values.push_back(4);
    Histogram histogram(4, values);
    for (size_t i = 0; i < values.size(); ++i)
    {
        EXPECT_EQ(histogram[i], 1);
    }
    EXPECT_EQ(histogram.get_bins_amount(), 4);
}

TEST(histogram, operator_insert){
    double min = 0.00001, max = 4.00001;
    Histogram histogram(4, min, max);
    histogram(3.2);
    histogram(2.2);
    histogram(1.2);
    histogram(0.2);

    for (size_t i = 0; i < 4; ++i)
    {
        EXPECT_EQ(histogram[i], 1);
    }
}

TEST(histogram, ostream_operator){
    double min = 0.50000, max = 4.50000;
    Histogram histogram(4, min, max);
    std::cout << histogram << std::endl;  
}

TEST(histogram, sum){
    std::vector<double> values;
    values.push_back(1);
    values.push_back(2);
    values.push_back(3);
    values.push_back(4);
    Histogram histogram(4, values);
    EXPECT_EQ(histogram.SumBins(), 4);
}

TEST(statistics, Mean_and_std){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<> d(5, 2);
    Mean mean;
    StandardDeviation std;
    for (size_t i = 0; i < 10000; ++i)
    {
        double value = d(gen);
        mean(value);
        std(value);
    }
    EXPECT_NEAR(mean, 5, 0.1);
    EXPECT_NEAR(std, 2, 0.1);
}

TEST(histogram, random){
    std::vector<double> values;
    Histogram probs(2, 0, 2);
    probs(0.5);
    probs(0.5);
    probs(0.5);
    probs(1.5);
    probs(1.5);
    Histogram histogram(2, 0, 1.2);
    for (size_t i = 0; i < 10000; ++i)
    {
        size_t value = RandomGenerator(probs);
    //    std::cout << value << std::endl;
        histogram(value);
    }
    EXPECT_NEAR(histogram[0] / 10000.0, probs[0] / static_cast<double>(probs.SumBins()), 0.02);
    EXPECT_NEAR(histogram[1] / 10000.0, probs[1] / static_cast<double>(probs.SumBins()), 0.02);
}
