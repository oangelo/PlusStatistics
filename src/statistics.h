#ifndef STATISTICS_H
#define STATISTICS_H 

#include <functional>
#include <random>
#include <cmath>
#include <map>

#include "histogram.h"  


namespace pstatistics{

    class Mean : public std::binary_function<double, double, double>{
        public:
            Mean();
            double operator()(double value);
            operator double() const;
        private:
            double my_mean;
            unsigned counter;
    };

    class StandardDeviation : public std::binary_function<double, double, double>{
        public:
            StandardDeviation();
            double operator()(double value);
            operator double() const;
        private:
            double my_mean, deviation;
            unsigned counter;
    };

    /*http://en.wikipedia.org/wiki/Skewness*/
    class Skewness : public std::binary_function<double, double, double>{
        public:
            Skewness();
            double operator()(double value);
            operator double() const;
        private:
            std::vector<double> data;
            Mean mean;
            double g1;
    };
}

#endif /* STATISTICS_H */
