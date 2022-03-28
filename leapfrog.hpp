#ifndef LEAP_H
#define LEAP_H
#include <math.h>
#include <iostream>
#include <string>
#include<vector>

class LeapFrog
{
    public:
    LeapFrog( double to, double tF, double e[], double b[])
    {
        t0=to;
        tf=tF;
        for(int i=0;i<3;i++)
        {
            E[i]=e[i];
            B[i]=b[i];
        }       
    }

    void leapfrogcall(double y[],double n)
    {
        tStep=(tf-t0)/n;
        iFinal =n;

        y[0]*=mass;
        y[1]*=mass;
        y[2]*=mass;

        
        
        for(int i=1;i<=iFinal;i++)
        {
            leapfrogimplement(y,i);
           
            answerPx.push_back(w[0]);
            answerPy.push_back(w[1]);
            answerPz.push_back(w[2]);
            answerx.push_back(w[3]);
            answery.push_back(w[4]);
            answerz.push_back(w[5]);
            time.push_back(t0 +i*tStep);
            y=w;
        }


         
    }

    void leapfrogimplement(double y[],int i)
    {
        
        w[0] = y[0] + tStep*model(tStep*i,y[0],y[1],y[2],y[3],y[4],y[5],0);
        w[1] = y[1] + tStep*model(tStep*i,y[0],y[1],y[2],y[3],y[4],y[5],1);
        w[2] = y[2] + tStep*model(tStep*i,y[0],y[1],y[2],y[3],y[4],y[5],2);

        w[3]= y[3] +tStep*model(tStep*i,w[0],w[1],w[2],y[3],y[4],y[5],3);
        w[4]= y[4] +tStep*model(tStep*i,w[0],w[1],w[2],y[3],y[4],y[5],4);
        w[5]= y[5] +tStep*model(tStep*i,w[0],w[1],w[2],y[3],y[4],y[5],5);

        
    }
    double model(double time,  double px , double py, double pz, double x, double y,double z,int state )
    {

    if(state == 0)
    {
        return charge*E[0] + (charge/mass)*(py*B[2] - B[1]*pz);
    }

    else if(state == 1)
    {
        return charge*E[1] + (charge/mass)*(pz*B[0] - B[2]*px);
    }

    else if(state == 2)
    {
        return charge*E[2] + (charge/mass)*(px*B[1] - B[0]*py);
    }

    else if(state == 3)
    {
        return px/mass;
    }

    else if(state == 4)
    {
        return py/mass;
    }

    else 
    {
        return pz/mass;
    }
    }


    public:
    double tStep;
    double t0;
    double tf ;
    int iFinal;
    double E[3];
    double B[3];
    double charge = 1.60217662* pow(10,-19);
    double mass =9.10938356 *pow(10,-31);
    double w[6];
    std::vector<double> answerPx;
    std::vector<double> answerPy;
    std::vector<double> answerPz;
    std::vector<double> answerx;
    std::vector<double> answery;
    std::vector<double> answerz;
    std::vector<double> time;

};

#endif