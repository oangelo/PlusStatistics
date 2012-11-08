 
#include "histogram.h"

histogram::histogram(unsigned bins,const std::vector<double> & values){
  __epslon=0.0000000001;
  __n_bins=bins;
  __values=values;
  __max=__values[0];
  __min=__values[0];
  for(unsigned i=1;i<__values.size();i++){
    if(__min>__values[i])
      __min=__values[i];
    if(__max<__values[i])
      __max=__values[i];
  }
  __max+=__epslon;
  fill_histogram();
}
histogram::histogram(unsigned bins,double min,double max,const std::vector<double> & values){
  __epslon=0.0000000001;
  __n_bins=bins;
  __values=values;
  __max=max;
  __min=min;
  fill_histogram();
}


void histogram::fill_histogram(){
  std::vector<double> aux(3);
  
  //preparing de __histogram
  double length;
  length = __max-__min;
  for(unsigned i=0;i<__n_bins;i++){
    aux[0]=__min+i*(length/__n_bins);
    aux[1]=__min+(i+1)*(length/__n_bins);
    aux[2]=0;
    __histogram.push_back(aux); 
  }
  
  //feeding
  unsigned position;
  for(unsigned i=0;i<__values.size();i++){
    position = (__values[i]-__min)*(((double)__n_bins)/length);
    //std::cout << position << std::endl; 
    __histogram[position][2]++;
  } 
}

unsigned histogram::n_occupied_bins(){
  unsigned cont=0;
  for(unsigned i=0;i<__histogram.size();i++){
    if(__histogram[i][2]>0){
      cont++;
    }
  }
  return(cont);
}

void histogram::print(){
  for(unsigned i=0;i<__n_bins;i++)
    std::cout << __histogram[i][0] <<"\t"<<__histogram[i][1] <<"\t"<<__histogram[i][2]<< std::endl;
}

void histogram::print(std::string file_name){
  std::ofstream data;
  data.open(file_name.c_str());
  double length;
  length = __max-__min;
  for(unsigned i=0;i<__n_bins;i++)
    data << (__histogram[i][1]+__histogram[i][0])/2  <<"\t"<<__histogram[i][2]/__values.size()<<"\t"<<(length/__n_bins)<< std::endl;
  data.close();
}

void histogram::print(std::string file_name,std::string folder){
struct stat st;   
  if(!(stat(folder.c_str(),&st) == 0)){
    std::stringstream ss; 
    ss << "mkdir " << folder;
    system(std::string(ss.str()).c_str());
  }
  std::stringstream ss; 
  ss << folder << "/" << file_name;
  std::ofstream data;
  data.open(std::string(ss.str()).c_str());
  double length = __max-__min;
  for(unsigned i=0;i<__n_bins;i++)
    data << (__histogram[i][1]+__histogram[i][0])/2  <<"\t"<<__histogram[i][2]/__values.size()<<"\t"<<(length/__n_bins)<< std::endl;  
  data.close();
  
 
  
}

double histogram::operator[](unsigned index) const{
    return (double(__histogram[index][2]) / __values.size());
}

unsigned histogram::Size() const{
    return __histogram.size();
}
