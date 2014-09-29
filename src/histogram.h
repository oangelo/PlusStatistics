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

    typedef std::pair<double, double> bin;  

    //return the occupation of a bin
    std::pair<double, unsigned> operator[](unsigned index) const;
    //increment a bin acording with the value
    void operator()(double value);

    bin BinRange(unsigned index) const;
    unsigned SamplesAmount() const;
    unsigned BinsAmount() const;
    double Max() const;
    double Min() const;

protected:
    Histogram(double min, double max);

    std::vector<double> amount;
    std::vector<double> center;
    std::vector<bin> range;
    double max, min;
    unsigned samples_amount;
    void StartHistogram(unsigned bins_amount);
};

std::ostream& operator<<(std::ostream& os, const Histogram& histogram); 
std::string Normilize(const Histogram& histogram);

} //namespace

#endif //HISTOGRAM
