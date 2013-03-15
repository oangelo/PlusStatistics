#include <iostream>
#include <algorithm> 

#include <cstring>
#include <cstdlib> 
#include <cmath> 

#include "utils/utils.h"
#include "histogram.h"
#include "statistics.h"

void help(std::string name) {
    std::cout << "usage:" << std::endl;
    std::cout << name << " [options]... [file name]" << std::endl;
    std::cout << std::endl;
    std::cout << "functions:" << std::endl;
    std::cout << "  --hist                 print a histogram" << std::endl;
    std::cout << "  --mean                 print the mean" << std::endl;
    std::cout << "  --std                  print the standard deviation" << std::endl;
    std::cout << std::endl;
    std::cout << "options:" << std::endl;
    std::cout << "  -                             reads data from stdin" << std::endl;
    std::cout << "  -bins_amount <integer>        set the amount of bins on the histogram" << std::endl;
}

int main(int argc, char** argv) {

    unsigned bins_amount = 0;
    std::vector<double> data;

    if(argc > 1) { 
        if( strcmp(argv[1], "-h") == 0) {
            help(std::string(argv[0]));
            return 0;
        }
    }else{
        help(argv[0]);
        return 0;
    }


    for (int i = 1; i < argc; ++i)
    {
        if( strcmp(argv[i], "-bins_amount") == 0) {
            bins_amount = atoi(argv[i + 1]);
            std::cerr << "# bins_amount: " << bins_amount << std::endl;
        }
        if( strcmp(argv[i], "-") == 0) {
            auto stdin_data(ReadStdin<double>());
            for(auto i: stdin_data)
                data.push_back(i[0]);
            std::cerr << "# lines read: " << data.size() << std::endl;
        }

    }

    if(data.size() == 0) {
        auto stdin_data(ReadFile<double>(std::string(argv[argc - 1])));
        for(auto i: stdin_data)
            data.push_back(i[0]);
    }

    for (int i = 1; i < argc; ++i)
    {
        if( strcmp(argv[i], "--hist") == 0) {
            if(data.size() > 0){
                if(bins_amount > 0){
                    Histogram histogram(bins_amount, data);
                    std::cout << histogram << std::endl;
                }else{
                    Histogram histogram(sqrt(data.size()), data);
                    std::cout << histogram << std::endl;
                }
            }
        }
        if( strcmp(argv[i], "--mean") == 0) {
            Mean mean;
            mean = for_each(data.begin(), data.end(), mean);
            std::cout << mean << std::endl;
        }
        if( strcmp(argv[i], "--std") == 0) {
            StandardDeviation std;
            std = for_each(data.begin(), data.end(), std);
            std::cout << std << std::endl;
        }
    }
    return 0;
}
