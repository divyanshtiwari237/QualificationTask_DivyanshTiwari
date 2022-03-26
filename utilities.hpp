#include<vector>

static double CalculateRadius(std::vector<double> y, std::vector<double> x, double tStep)
{
    int i=0;
    while(y[i]>0)
    {
        i++;
    }
    return x[i]/2;

}

static double CalculateTimePeriod(std::vector<double> y, std::vector<double> x, double tStep)
{
    int i=0;
    while(y[i]>0)
    {
        i++;
    }
    return i*tStep;

}