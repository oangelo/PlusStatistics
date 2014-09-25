#include "utils.h"


std::vector< std::vector<double> >  ReadFile(std::string file_name, std::string delim){
  std::vector< std::vector<double> > data;
  std::string line;
  std::ifstream myfile(file_name.c_str());
  if(myfile.is_open())
  {
    while (myfile.good())
    {
      std::vector<double> values;
      getline(myfile, line);
      if((line.front() != '#') && !line.empty() ){
        std::stringstream line_stream(line);
        std::string value;
        while(std::getline(line_stream, value, delim.c_str()[0]))
          values.push_back(std::stod(value));
        data.push_back(values);
      }

    }

    myfile.close();
  }
  else std::cout << "Unable to open file" << std::endl; 
  return data;
}

std::vector< std::vector<double> >  ReadStdin(std::string delim){
  std::vector< std::vector<double> > data;
  std::string line;
  while (std::cin)
  {
    std::vector<double> values;
    getline(std::cin, line);
    if((line.front() != '#') && !line.empty() ){
      std::stringstream line_stream(line);
      std::string value;
      while(std::getline(line_stream, value, delim.c_str()[0]))
        values.push_back(std::stod(value));
      data.push_back(values);
    }
  }
  return data;
}
