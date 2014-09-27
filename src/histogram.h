# ifndef HISTOGRAM
# define HISTOGRAM 

#include <vector>
#include <cmath>
#include <iostream>
#include <fstream>
#include <string>
#include <sys/stat.h>
#include <stdlib.h>
#include <sstream>
#include <map>
#include <algorithm>

namespace pstatistics{

class Histogram{
public:
    Histogram(unsigned bins_amount, const std::vector<double> & values);
    Histogram(unsigned bins_amount, double min, double max);

    //return the occupation of a bin
    unsigned operator[](unsigned index) const;
    //increment a bin acording with the value
    void operator()(double value);

    unsigned SamplesAmount() const;
    std::pair<double, double> Bin() const;

    unsigned BinsAmount() const;
    double Max() const;
    double Min() const;

    friend std::ostream& operator<<(std::ostream& os, const Histogram& histogram); 
    friend std::string Normilize(const Histogram& histogram);
    
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
