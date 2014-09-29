#include "logbinning.h"

namespace pstatistics{

  LogBinning::LogBinning(const std::vector<double> & values, double _common_ratio)
    :Histogram(*std::min_element(values.begin(), values.end()), *std::max_element(values.begin(), values.end())),
    common_ratio(_common_ratio)
  {
    LogaritimicBins();
    for(auto& item: values){
      operator()(item);
    }

  }

  LogBinning::LogBinning(double min, double max, double _common_ratio)
    :Histogram(min, max),
    common_ratio(_common_ratio)
  {
    LogaritimicBins();
  }

  void LogBinning::LogaritimicBins(){
    range.clear();
    double box_begin(min);
    double box_end(min*common_ratio);
    unsigned count(1);
    while(box_end < max){
      count += 1;
      bin aux(box_begin, box_end);
      range.push_back(aux); 
      amount.push_back(0); 
      center.push_back(pow(common_ratio, (count - 2) + 0.5));
      box_begin = box_end;
      box_end = min * pow(common_ratio, count);
    }
    bin aux(box_begin, box_end);
    range.push_back(aux); 
    amount.push_back(0); 
    center.push_back(pow(common_ratio, (count - 1) + 0.5));

  }

} //namespace
