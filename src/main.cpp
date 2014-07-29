#include <iostream>
#include <algorithm> 
#include <string> 

#include "boost/program_options.hpp" 
#include "utils/utils.h"
#include "histogram.h"
#include "statistics.h"


using namespace pstatistics;

int main(int argc, char** argv) 
{ 
    unsigned bins_amount(0);
    std::vector<double> data;

    try 
    { 
        /** Define and parse the program options */ 
        namespace po = boost::program_options; 
        po::options_description desc("Options"); 
        desc.add_options() 
            ("help, h", "Print help messages") 
            ("histogram", "Print Histogram") 
            ("mean", "Print the mean of the data") 
            ("std", "Print the standard deviation of the data")
            ("skew", "Print skewness of the data")
            ("bins", po::value<unsigned>(&bins_amount), "Set the number of bins of the histogram");

        po::variables_map vm; 
        try 
        { 
            po::store(po::parse_command_line(argc, argv, desc),  vm); // can throw 
            if ( vm.count("help")  ) 
            { 
                std::cout << "Basic Command Line Parameter" << std::endl << desc << std::endl; 
                return EXIT_SUCCESS; 
            } 

            po::notify(vm); // throws on error, so do after help in case 
            // there are any problems 
        } 
        catch(po::error& e) 
        { 
            std::cerr << "ERROR: " << e.what() << std::endl << std::endl; 
            std::cerr << desc << std::endl; 
            return EXIT_FAILURE; 
        } 
        auto stdin_data(ReadStdin<double>());
        for(auto i: stdin_data)
            data.push_back(i[0]);

        if (vm.count("histogram")){
            std::cerr << "# lines read: " << data.size() << std::endl;
            if(bins_amount > 0){
                Histogram histogram(bins_amount, 
                        *std::min_element(data.begin(), data.end()), *std::max_element(data.begin(), data.end()));
                for(auto value: data)
                    histogram(value);
                std::cout << histogram << std::endl;
            }else{
                Histogram histogram(sqrt(data.size()),
                        *std::min_element(data.begin(), data.end()), *std::max_element(data.begin(), data.end()));
                for(auto value: data)
                    histogram(value);
                std::cout << histogram << std::endl;
            }
        }
        if(vm.count("mean")) {
            Mean mean(for_each(data.begin(), data.end(), Mean()));
            std::cout << mean << std::endl;
        } else if(vm.count("std")) {
            StandardDeviation std(for_each(data.begin(), data.end(), StandardDeviation()));
            std::cout << std << std::endl;
        } else if(vm.count("skew")) {
            Skewness skewness(for_each(data.begin(), data.end(), Skewness()));
            std::cout << skewness << std::endl;
        }


        // application code here // 
    } 
    catch(std::exception& e) 
    { 
        std::cerr << "Unhandled Exception reached the top of main: " 
            << e.what() << ", application will now exit" << std::endl; 
        return EXIT_FAILURE; 

    } 
    return EXIT_SUCCESS; 
}
