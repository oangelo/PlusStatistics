#include "histogram.h"

namespace pstatistics{

  std::ostream& operator<<(std::ostream& os, const Histogram& histogram) {
    os << "#midle_bin_value\tbin_amount/bin_length\tbin_length" <<  std::endl;
    for (size_t i = 0; i < histogram.BinsAmount(); ++i)
    {
      double bin_length =  histogram.BinRange(i).second - histogram.BinRange(i).first; 
      if (histogram[i].second > 0){
        os << histogram[i].first << "\t" << histogram[i].second / bin_length << "\t" << bin_length << std::endl;
      }else{
        os << std::endl;
      }
    }
    return os;
  } 

  std::string Normilize(const Histogram& histogram) {
    std::stringstream ss;
    ss << "#midle_bin_value\tbin_probability\tbin_length\n";

    double area(0);
    for (size_t i = 0; i < histogram.BinsAmount(); ++i) {
      Histogram::bin range(histogram.BinRange(i));
      area += histogram[i].second;
    }

    for (size_t i = 0; i < histogram.BinsAmount(); ++i)
    {
      double bin_length =  histogram.BinRange(i).second - histogram.BinRange(i).first; 
      if (histogram[i].second > 0){
        ss << histogram[i].first << "\t" << (histogram[i].second / bin_length) / area << "\t" << bin_length << std::endl;
      }else{
        ss << std::endl;
      }
    }
    return ss.str();
  }

  //adding a small value to max, so the max value from values can be present at
  //the histogram
  Histogram::Histogram(unsigned bins_amount, const std::vector<double> & values)
    :amount(), center(), range(), max(*std::max_element(values.begin(), values.end()) + 0.00000001), 
    min(*std::min_element(values.begin(), values.end())), samples_amount(0)
  {
    StartHistogram(bins_amount);
    for(auto& item: values){
      operator()(item);
    }

  }

  Histogram::Histogram(unsigned bins_amount, double min, double max)
    :amount(), center(), range(), max(max), min(min), samples_amount(0)
  {
    StartHistogram(bins_amount);
  }

  Histogram::Histogram(double min, double max)
    :amount(), center(), range(), max(max), min(min), samples_amount(0)  {
  }


  void Histogram::StartHistogram(unsigned bins_amount){
    double length = (max - min) / bins_amount;
    for(unsigned i = 0; i < bins_amount; i++) {
      std::pair<double, double> bin(min + i * length, min + (i + 1) * length);
      center.push_back(bin.first + ((bin.second - bin.first) / 2.0));
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
    return std::make_pair(center[index], amount[index]);
  }

  void Histogram::operator()(double value) {
    for (size_t i = 0; i < range.size(); ++i) {
      if( range[i].first <= value and range[i].second > value) {
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
