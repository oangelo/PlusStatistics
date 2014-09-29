#include "histogram.h"

namespace pstatistics{

  std::ostream& operator<<(std::ostream& os, const Histogram& histogram) {
    os << "#midle_bin_value \t bin_amount \t bin_length" <<  std::endl;
    for (size_t i = 0; i < histogram.BinsAmount(); ++i)
    {
      double bin_length =  histogram.BinRange(i).second - histogram.BinRange(i).first; 
      os << histogram[i].first << "\t" << histogram[i].second << "\t" << bin_length << std::endl;
    }
    return os;
  } 

  std::string Normilize(const Histogram& histogram) {
    std::stringstream ss;
    ss << "#midle_bin_value \t bin_amount \t bin_length\n";
    for (size_t i = 0; i < histogram.BinsAmount(); ++i)
    {
      double bin_length =  histogram.BinRange(i).second - histogram.BinRange(i).first; 
      ss << histogram[i].first << "\t" << static_cast<double>(histogram[i].second) / histogram.SamplesAmount() 
      << "\t" << bin_length << std::endl;
    }
    return ss.str();
  }

  //adding a small value to max, so the max value from values can be present at
  //the histogram
  Histogram::Histogram(unsigned bins_amount, const std::vector<double> & values)
    :amount(), range(), max(*std::max_element(values.begin(), values.end()) + 0.00000001), 
    min(*std::min_element(values.begin(), values.end())), bins_amount(bins_amount), samples_amount(0)
  {
    StartHistogram();
    for(auto& item: values){
      operator()(item);
    }

  }

  Histogram::Histogram(unsigned bins_amount, double min, double max)
    :amount(), range(), max(max), min(min), bins_amount(bins_amount), samples_amount(0)
  {
    StartHistogram();
  }

  void Histogram::StartHistogram(){
    double length = (max - min) / bins_amount;
    for(unsigned i = 0; i < bins_amount; i++) {
      std::pair<double, double> bin(min + i * length, min + (i + 1) * length);
      range.push_back(bin); 
      amount.push_back(0); 
    }
  }

  unsigned Histogram::BinsAmount() const {
    return range.size();
  }

  double Histogram::Max() const {
    return max;
  }

  double Histogram::Min() const {
    return min;
  }

  unsigned Histogram::SamplesAmount() const {
    return std::accumulate(amount.begin(), amount.end(), 0);
  }

  std::pair<double, unsigned> Histogram::operator[](unsigned index) const {
    double center(range[index].first + (range[index].second - range[index].second) / 2.0);
    return std::make_pair(center, amount[index]);
  }

  void Histogram::operator()(double value) {
    for (size_t i = 0; i < range.size(); ++i) {
      if( range[i].first <= value && range[i].second > value) {
        ++amount[i];
        ++samples_amount;
        return;
      }
    }
  }

  Histogram::bin Histogram::BinRange(unsigned index) const{
    return range[index]; 
  }

}
