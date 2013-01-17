#include "histogram.h"


std::ostream& operator<<(std::ostream& os, const Histogram& histogram) {
    os << "# bin_value \t bin_min \t bin_max" <<  std::endl;
    for (size_t i = 0; i < histogram.range.size(); ++i)
    {
        os << histogram.amount[i] << "\t" << histogram.range[i].first << "\t" << histogram.range[i].second <<  std::endl;
    }
    return os;
} 

//adding a small value to max, so the max value from values can be present at
//the histogram
Histogram::Histogram(unsigned bins_amount, const std::vector<double> & values)
:amount(), range(), max(*std::max_element(values.begin(), values.end()) + 0.00000001), 
    min(*std::min_element(values.begin(), values.end())), bins_amount(bins_amount)
{
    StartHistogram();
    for(auto& item: values){
        operator()(item);
    }

}

Histogram::Histogram(unsigned bins_amount, double min, double max)
:amount(), range(), max(max), min(min), bins_amount(bins_amount)
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

unsigned Histogram::get_bins_amount() const {
    return range.size();
}

double Histogram::get_max() const {
    return max;
}

double Histogram::get_min() const {
    return min;
}

unsigned Histogram::SumBins() {
    return std::accumulate(amount.begin(), amount.end(), 0);
}

unsigned Histogram::operator[](unsigned index) const {
    return amount[index];
}

void Histogram::operator()(double value) {
    for (size_t i = 0; i < range.size(); ++i) {
        if( range[i].first <= value && range[i].second > value) {
            ++amount[i];
            return;
        }
    }
}
