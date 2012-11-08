# ifndef __HISTOGRAM__
# define __HISTOGRAM__ 

#include <vector>
#include <math.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sys/stat.h>
#include <stdlib.h>
#include <sstream>

class histogram{
public:
    histogram(unsigned bins,const std::vector<double> & values);
    histogram(unsigned bins,double min,double max,const std::vector<double> & values);
    void print();
    void print(std::string file_name);
    void print(std::string file_name,std::string folder);
    unsigned n_occupied_bins();

    unsigned Size() const;
    double operator[](unsigned index) const;
    
protected:
    std::vector<double> __values;
    std::vector< std::vector<double> > __histogram;
    unsigned __n_bins;
    double __max,__min,__epslon;
    void fill_histogram();
    
};

#endif //__HISTOGRAM__
