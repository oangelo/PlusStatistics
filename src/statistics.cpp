#include "statistics.h"

namespace pstatistics{

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

Skewness::Skewness() :data(), mean(), g1(0) {} 

double Skewness::operator()(double value) {
    mean(value);
    data.push_back(value);
    double numerator(0); 
    for(auto& element: data)
        numerator += pow(element - mean, 3);
    numerator /= data.size();
    double denominator(0); 
    for(auto& element: data)
        denominator += pow(element - mean, 2);
    denominator /= data.size();
    denominator = pow(denominator, 3.0/2.0);
    g1 = (numerator / denominator);
    return g1;
} 

Skewness::operator double() const{
    return g1;
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

size_t RandomGenerator(std::vector<frequency> data_frequency){
    std::vector<double> data;
    for(frequency element: data_frequency){
        for (size_t i = 0; i < element.second; ++i) {
            data.push_back(element.first);
        }
    }
    std::uniform_real_distribution<> dist(0, data.size());
    double random_number = dist(gen);
    return data[random_number];
}

}
