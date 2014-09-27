# ifndef HISTOGRAM
# define HISTOGRAM 

#include <vector>
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>

namespace pstatistics{

class Histogram{
public:
    Histogram(unsigned bins_amount, const std::vector<double> & values);
    Histogram(unsigned bins_amount, double min, double max);
    virtual ~Histogram(){};

    //return the occupation of a bin
    std::pair<double, unsigned> operator[](unsigned index) const;
    //increment a bin acording with the value
    void operator()(double value);

    std::pair<double, double> Bin(unsigned index) const;
    unsigned SamplesAmount() const;
    unsigned BinsAmount() const;
    double Max() const;
    double Min() const;

protected:
    std::vector<double> amount;
    std::vector<std::pair<double, double>> range;
    double max, min;
    unsigned bins_amount, samples_amount;
    void StartHistogram();
};

std::ostream& operator<<(std::ostream& os, const Histogram& histogram); 
std::string Normilize(const Histogram& histogram);

} //namespace

#endif //HISTOGRAM
