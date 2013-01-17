#ifndef STATISTICS_H
#define STATISTICS_H 

#include <cmath>

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

#endif /* STATISTICS_H */
