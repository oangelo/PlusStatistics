#ifndef STATISTICS_H
#define STATISTICS_H 

#include <cmath>
#include <random>
#include "histogram.h"  

namespace pstatistics{

class Mean{
    public:
        Mean();
        double operator()(double value);
        operator double() const;
    private:
        double my_mean;
        unsigned counter;
};

class StandardDeviation{
    public:
        StandardDeviation();
        double operator()(double value);
        operator double() const;
    private:
        double my_mean, deviation;
        unsigned counter;
};

/*http://en.wikipedia.org/wiki/Skewness*/
class Skewness{
    public:
        Skewness();
        double operator()(double value);
        operator double() const;
    private:
        std::vector<double> data;
        Mean mean;
        double g1;
};

size_t RandomGenerator(Histogram histogram);
}

#endif /* STATISTICS_H */
