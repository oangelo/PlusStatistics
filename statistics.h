#ifndef STATISTICS_H
#define STATISTICS_H 
class Mean{
    public:
        Mean():my_mean(0), counter(0){};
        double operator()(double value){
            my_mean = (value + counter * my_mean) / (counter + 1);
            ++counter;
            return my_mean;
        };
        operator double() const{return my_mean;};
    private:
        double my_mean;
        unsigned counter;
};

class StandardDeviation{
    public:
        StandardDeviation():my_mean(0), deviation(0), counter(0){};
        double operator()(double value){
            my_mean = (value + counter * my_mean) / (counter + 1);
            deviation += (counter * pow(value - my_mean, 2)) / (counter + 1);
            ++counter;
            return sqrt(deviation / counter);
        };
        operator double() const{return sqrt(deviation / counter);};
    private:
        double my_mean, deviation;
        unsigned counter;
};


#endif /* STATISTICS_H */
