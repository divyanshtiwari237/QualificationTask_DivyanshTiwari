#ifndef RK45_H
#define RK45_H
#include <math.h>
#include <iostream>
#include <fstream>
#include <string>
#include<vector>


class RK2 
{
    public:
    
    RK2( double to, double tF, double e[], double b[])
    {
        t0=to;
        tf=tF;
        for(int i=0;i<3;i++)
        {
            E[i]=e[i];
            B[i]=b[i];
        }       
    }

    void rk2(double y[],double n)
    {
        tStep=(tf-t0)/n;
        iFinal =n;

        y[0]*=mass;
        y[1]*=mass;
        y[2]*=mass;

        std::ofstream file;
        file.open("data.csv", std::ios_base::app);
        
        file<<"Column Px"<<","<<"Column Py"<<","<<"Column Pz"<<","<<"Column x"<<","<<"Column y"<<","<<"Column z"<<std::endl;
        
        for(int i=1;i<=iFinal;i++)
        {
           rk2implement(y,i);
           
            answerPx.push_back(w[0]);
            answerPy.push_back(w[1]);
            answerPz.push_back(w[2]);
            answerx.push_back(w[3]);
            answery.push_back(w[4]);
            answerz.push_back(w[5]);
            time.push_back(t0 +i*tStep);
           
            file<<w[0]<<","<<w[1]<<","<<w[2]<<","<<w[3]<<","<<w[4]<<","<<w[5]<<std::endl;
            
            y=w;
        }

         file.close();
    }

    

    void rk2implement(double y[],int i)
    {
        double k1[6];
        double k2[6];

        for(int j=0;j<6;j++)
        {  
            k1[j] =tStep*model(t0+i*tStep,y[0],y[1],y[2],y[3],y[4],y[5],j);       
        }

        for (int j=0;j<6;j++)
        {
            k2[j] =tStep*model(t0+i*tStep+tStep/2,y[0]+k1[0]/2,y[1]+k1[1]/2,y[2]+k1[2]/2,y[3]+k1[3]/2,y[4]+k1[4]/2,y[5]+k1[5]/2,j); 
        }

        for(int j=0; j<6;j++)
        {
            w[j]=y[j]+k2[j];
        }
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