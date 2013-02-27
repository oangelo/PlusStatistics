#include "statistics.h"

Mean::Mean():my_mean(0), counter(0){}

double Mean::operator()(double value){
    my_mean = (value + counter * my_mean) / (counter + 1);
    ++counter;
    return my_mean;
}

Mean::operator double() const{return my_mean;}

StandardDeviation::StandardDeviation():my_mean(0), deviation(0), counter(0) {}

double StandardDeviation::operator()(double value) {
    my_mean = (value + counter * my_mean) / (counter + 1);
    deviation += (counter * pow(value - my_mean, 2)) / (counter + 1);
    ++counter;
    return sqrt(deviation / counter);
}

StandardDeviation::operator double() const {
    return sqrt(deviation / counter);
}

std::random_device rd;
std::mt19937 gen(rd());

size_t RandomGenerator(Histogram histogram){
    double histogram_sum = histogram.SumBins();
    std::uniform_real_distribution<> dist(0, histogram_sum);
    double random_number = dist(gen);
    double sum = 0;
    unsigned counter = 0;
    sum = histogram[0];
    while(counter < histogram.get_bins_amount() && random_number > sum) {
        ++counter;
        sum += histogram[counter];
    }
    return counter;
}
