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
    Mean<double> mean;
    StDeviation<double> std;
    for (size_t i = 0; i < 10000; ++i)
    {
        double value = d(gen);
        mean(value);
        std(value);
    }
    EXPECT_NEAR(mean, 5, 0.1);
    EXPECT_NEAR(std, 2, 0.1);
}

/*
TEST(Histogram, operators){
    Histogram1D hist(0,10,10);
    hist(0);
    hist(1);
    hist(2);
    hist(3);
    hist(4);
    hist(5);
    hist(6);
    hist(7);
    hist(8);
    hist(9);
    for (size_t i = 0; i < 10; ++i)
    {
        std::pair<double,double> range = hist.BinRange(i);
        //std::cout << "["<< range.first << " , " << range.second << ") " << hist[i] << std::endl; 
        EXPECT_EQ(range.first,i);
        EXPECT_EQ(range.second,i+1);
        EXPECT_EQ(hist[i],1);
    }
    EXPECT_ANY_THROW(hist(10));
}

/*
TEST(statistics, max_and_min){
    Histogram1D hist(0,10,10);
    hist(0);
    hist(1);
    hist(2);
    hist(3);
    //hist(4);
    hist(5);
    hist(6);
    hist(7);
    hist(8);
    hist(9);
    hist(9);
    EXPECT_EQ(hist.Min(),4);
    EXPECT_EQ(hist.Max(),9);
}
TEST(statistics, mean){
    Histogram1D hist(0.5,4.5,4);
    hist(1);
    hist(2);
    hist(3);
    hist(4);
    EXPECT_EQ(hist.Mean(),10.0/4.0);
    hist(1);
    hist(1);
    EXPECT_EQ(hist.Mean(),12.0/6.0);
}

TEST(statistics, std){
    Histogram1D hist(0.5,4.5,4);
    hist(4);
    hist(2);
    hist(4);
    hist(2);
    EXPECT_EQ(hist.Std(),1.0);
    Histogram1D hist1(0.5,4.5,4);
    hist1(2);
    hist1(2);
    hist1(2);
    hist1(2);
    EXPECT_EQ(hist1.Std(),0.0);

}
/*Using this in several tests to fill a test histogram
void fill(Histogram &teste, size_t n_bins) {
	for (int i = 0; i < (int) n_bins; i++)
		teste.increment(i);
}
SUITE(Histogram_test)
{

	TEST(Test_Constructor)
	{
		Histogram teste(11, 0, 10);
	}

	TEST(Test_Constructor_wrong)
	{
		CHECK_THROW(Histogram teste(11, 10, 10), Value_error);
	}

	TEST(Test_Constructor_scott)
	{
		Histogram teste(28.87, 100, 0, 100);
		fill(teste, 100);
		CHECK_EQUAL(teste.n_bins(),5);
	}

	TEST(Test_Constructor_scott_wrong)
	{
		CHECK_THROW(Histogram teste(28.87, 100, 100, 100), Value_error);
	}

	TEST(Test_Increment)
	{
		Histogram teste(10, 0, 10);
		for (unsigned int i = 0; i < 10; i++)
			teste.increment(i);
		for (int i = 0; i < 10; i++)
			CHECK_EQUAL(teste[i],0.1);
	}

	TEST(Test_Increment_wrong)
	{
		Histogram teste(10, 0, 10);
		for (int i = 0; i < 10; i++)
			teste.increment(i);
		CHECK_THROW(teste.increment(15), Value_error);
	}

	//Testing boundary conditions for the smallest(2 bins) histogram
	TEST(Test_Increment_smallest)
	{
		Histogram teste(2, 0, 2);
		for (int i = 0; i < 2; i++)
			teste.increment(i);
		CHECK_EQUAL(teste[1],0.5);
		CHECK_EQUAL(teste[0],0.5);
	}

	TEST(Test_Increment_repeat)
	{
		Histogram teste(2, 0, 10);
		double data[10] = { 1, 1, 1, 1, 2, 2, 2, 3, 3, 4 };
		for (int i = 0; i < 10; i++)
			teste.increment(data[i]);
		CHECK_EQUAL(teste[1],0);
		CHECK_CLOSE(teste[0],1.0,EPSILON);
	}

	TEST(Test_mean)
	{
		Histogram teste(10, 0, 10);
		for (int i = 0; i < 10; i++)
			teste.increment(i);
		CHECK_CLOSE(5.0, teste.mean(), 0.01);
	}

	TEST(Test_Operator_accessing_int)
	{
		Histogram teste(10, 0, 10);
		for (int i = 0; i < 10; i++)
			teste.increment(i);

		for (int i = 0; i < 10; i++)
			CHECK_CLOSE(0.1, teste[i], 0.01);
	}

	TEST(Test_Operator_accessing_double)
	{
		Histogram teste(10, 0, 10);
		for (int i = 0; i < 10; i++)
			teste.increment(9.9);
		CHECK_CLOSE(1, teste[9.9], 0.01);
		CHECK_CLOSE(0.0, teste[0], 0.01);
	}

	TEST(Test_Operator_accessing_double_wrong)
	{
		Histogram teste(10, 0, 10);
		for (int i = 0; i < 10; i++)
			teste.increment(9.9);
		CHECK_THROW(teste[11.1], Value_error);
	}

	TEST(Test_Operator_accessing_int_wrong)
	{
		Histogram teste(10, 0, 10);
		for (int i = 0; i < 10; i++)
			teste.increment(i);
		CHECK_THROW(teste[12], Index_error);
	}

	TEST(Test_Operator_call_double)
	{
		Histogram teste(10, 0, 10);
		for (int i = 0; i < 10; i++)
			teste.increment(i);

		CHECK_EQUAL(9, teste(9.9));
	}

	TEST(Test_Operator_call_double_wrong)
	{
		Histogram teste(10, 0, 10);
		for (int i = 0; i < 10; i++)
			teste.increment(i);
		CHECK_THROW(teste(11.1), Value_error);
	}

	TEST(Test_n_bins)
	{
		Histogram teste(10, 0, 10);
		for (int i = 0; i < 10; i++)
			teste.increment(i);
		CHECK_EQUAL(teste.n_bins(), 10);
	}

	TEST(Test_range_max)
	{
		Histogram teste(10, 0, 10);
		for (int i = 0; i < 10; i++)
			teste.increment(i);
		CHECK_EQUAL(teste.range_max(), 10);
	}

	TEST(Test_reset)
	{
		Histogram teste(10, 0, 10);
		fill(teste, 10);
		teste.reset();
		for (int i = 0; i < 10; i++)
			CHECK_EQUAL(teste[i], 0.0);
	}

	TEST(Test_sum)
	{
		Histogram teste(10, 0, 10);
		fill(teste, 10);
		CHECK_EQUAL(teste.sum(), 10.0);
	}

	TEST(Test_sigma)
	{
		Histogram teste(10, 0, 10);
		fill(teste, 10);
		CHECK_CLOSE(2.87, teste.sigma(), 0.01); // succeeds 2.87
	}

	TEST(Test_max_val)
	{
		Histogram teste(10, 0, 10);
		fill(teste, 10);
		teste.increment(0.2);
		CHECK_EQUAL(teste.max_val(), 2.0);
	}

	TEST(Test_min_val)
	{
		Histogram teste(10, 0, 10);
		fill(teste, 9);
		fill(teste, 10);
		CHECK_EQUAL(teste.min_val(), 1.0);
	}

	TEST(Test_max_bin)
	{
		Histogram teste(10, 0, 10);
		fill(teste, 10);
		teste.increment(0.2);
		CHECK_EQUAL(teste.max_bin(), 0);
	}

	TEST(Test_min_bin)
	{
		Histogram teste(10, 0, 10);
		fill(teste, 10);
		fill(teste, 9);
		CHECK_EQUAL(teste.min_bin(), 9);
	}

	TEST(Test_Copy_Constructor)
	{
		Histogram teste(10, 1, 10);

		//Colocando valores dentro dos bins para teste
		teste.increment(3.2);
		teste.increment(4.2);
		teste.increment(3.5);
		teste.increment(7);
		teste.increment(7.1);
		teste.increment(7.2);
		teste.increment(7.2);

		Histogram teste2 = teste;

	}

}
*/
