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

    unsigned SumBins();

    unsigned get_bins_amount() const;
    double get_max() const;
    double get_min() const;

    friend std::ostream& operator<<(std::ostream& os, const Histogram& histogram); 
    
protected:
    std::vector<double> amount;
    std::vector<std::pair<double, double>> range;
    double max, min;
    unsigned bins_amount;
    void StartHistogram();
};

std::ostream& operator<<(std::ostream& os, const Histogram& histogram); 

} //namespace

#endif //HISTOGRAM
