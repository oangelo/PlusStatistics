#ifndef LOGBINNING_H
#define LOGBINNING_H 

#include <cmath>

#include "histogram.h"


namespace pstatistics{

  class LogBinning: public Histogram{
    public:
      LogBinning(const std::vector<double> & values, double _common_ratio = 1.34);
      LogBinning(double min, double max, double _common_ratio = 1.34);
    private:
      double common_ratio;
      void LogaritimicBins();
  };

}

#endif /* LOGBINNING_H */
