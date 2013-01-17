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

