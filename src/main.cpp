#include <iostream>
#include <algorithm> 
#include <string> 

#include "boost/program_options.hpp" 
#include "utils.h"
#include "histogram.h"
#include "statistics.h"


using namespace pstatistics;

int main(int argc, char** argv) 
{ 
  unsigned column, bins_amount(0);
  std::string file_name;
  std::vector<std::vector<double>> file_data;
  std::vector<double> data;
  std::string delimiter;

  try 
  { 
    /** Define and parse the program options */ 
    namespace po = boost::program_options; 
    po::options_description basic("Main"); 
    basic.add_options() 
      ("help,h", "Print help messages") 
      ("file,f", po::value<std::string>(&file_name),"Read data from file")
      ("stdin","Read data from the standard input ")
      ("column,c", po::value<unsigned>(&column)->default_value(0),"Use the given column")
      ("delimiter,d", po::value<std::string>(&delimiter)->default_value(std::string(" ")),"File delimiter");

    po::options_description opt("Options"); 
    opt.add_options() 
      ("hist", "Print Histogram") 
      ("mean", "Print the mean of the data") 
      ("std", "Print the standard deviation of the data")
      ("skew", "Print skewness of the data")
      ("bins", po::value<unsigned>(&bins_amount), "Set the number of bins of the histogram");

    po::options_description all_options;
    all_options.add(basic).add(opt);

    po::variables_map vm; 
    try 
    { 
      po::store(po::command_line_parser(argc, argv).options(all_options).
      style( po::command_line_style::unix_style | po::command_line_style::allow_long_disguise).run(),
      vm); // can throw 
      if (vm.count("help") or argc == 1) 
      { 
        std::cout << "Basic Command Line Parameter" << std::endl;
        std::cout << basic << std::endl; 
        std::cout << opt << std::endl; 
        return EXIT_SUCCESS; 
      } 
      po::notify(vm); // throws on error, so do after help in case 
      // there are any problems 
    } 
    catch(po::error& e) 
    { 
      std::cerr << "ERROR: " << e.what() << std::endl << std::endl; 
      std::cerr << basic<< std::endl; 
      std::cerr << opt << std::endl; 
      return EXIT_FAILURE; 
    } 

    if (vm.count("stdin")){
      file_data = ReadStdin(delimiter);
      std::cerr << "Lines: " << file_data.size() << ", Columns: " << file_data[0].size()  << std::endl;
    } else if (vm.count("file")){
      std::cerr << "Reading file: " << file_name  << std::endl;
      file_data =  ReadFile(file_name, delimiter);
      std::cerr << "Lines: " << file_data.size() << ", Columns: " << file_data[0].size()  << std::endl;
    } else{
      throw std::invalid_argument("No input specified!");
    }

    for(auto& i: file_data){
      data.push_back(i[column]);
    }

    if (vm.count("hist")){
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
