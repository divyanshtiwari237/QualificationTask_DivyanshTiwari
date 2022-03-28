#include<math.h>
#include<vector>
#include<iostream>
#define PI 3.14159265

class Analytical
{
    public:
    Analytical(double B,int n,double to, double tF,double y[])
    {
        Timeperiod= 2*PI*mass/(charge*B);
        radius=mass*y[1]/(charge*B);
        
        N=n;
        t0=to;
        tf=tF;
        tStep =(tf-t0)/N;


    }

    void calculate(double y[])
    {
        for (int i=1;i<N;i++)
        {
            double time =i*tStep;
            answerPx.push_back(mass*y[1]*sin(2*PI*time/Timeperiod));
            answerPy.push_back(mass*y[1]*cos(2*PI*time/Timeperiod));
            answerx.push_back(radius*(1-cos(2*PI*time/Timeperiod)));
            answery.push_back(radius*sin(2*PI*time/Timeperiod));
            timearray.push_back(i*tStep);
           

        }
    }


    public:
    std::vector<double> answerPx;
    std::vector<double> answerPy;
    std::vector<double> answerx;
    std::vector<double> answery;
    std::vector<double> timearray;
    double Timeperiod;
    double radius;
    double charge = 1.60217662* pow(10,-19);
    double mass =9.10938356 *pow(10,-31);
    int N;
    double tStep;
    double t0;
    double tf;

};