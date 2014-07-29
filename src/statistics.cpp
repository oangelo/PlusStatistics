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

} //namespace
