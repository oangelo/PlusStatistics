#ifndef UTILS_H_
#define UTILS_H_

#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <iostream> 

std::vector< std::vector<double> >  ReadFile(std::string file_name, std::string delim = " ");
std::vector< std::vector<double> >  ReadStdin(std::string delim = " ");

#endif /* UTILS_H_ */
