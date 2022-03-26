#include<iostream>
#include <fstream>
#include "rk2.hpp"
#include"plot.cpp"
#include<math.h>
#include"analytical.hpp"
#include "utilities.hpp"
#include"boostimpl.hpp"
#include<boost/numeric/odeint.hpp>
#include"matplotlibcpp.cpp"
namespace plt =matplotlibcpp;
typedef std::vector< double > state_type;
 using namespace boost::numeric::odeint;

int main()
{
    // Initial conditions
    double mass =9.10938356*pow(10,-31);
    double c = 3*pow(10,8); //speed of light
    double E[3] ={0,0,0};  //initialize the electric field
    double B[3]={0,0,11};  //initialize the magnetic field
    double y[6]={0,0.9*c,0,0,0,0}; // initial conditions of the particle
    int n =1000;
    double tStep=pow(10,-6);      // time step;
    
    
    
    
    
    Analytical A(B[2],n,0,4.5*pow(10,-10),y);
    A.calculate(y);
    auto yapx =A.answerPx;
    auto yapy =A.answerPy;
    auto yax =A.answerx;
    auto yay =A.answery;
    auto ta = A.timearray;
    
    //Setting up the solver and calling function   
    RK2 rk(0,4.5*pow(10,-10),E,B);       // Initialize the method with fields and time intervals;
    rk.rk2(y,n);       // call the solver method with the initial condition and time step;
    auto ypx =rk.answerPx;
    auto ypy =rk.answerPy;
    auto ypz =rk.answerPz;

    auto yx =rk.answerx;
    auto yy =rk.answery;
    auto yz =rk.answerz;
    auto t = rk.time;

    
    
    //Plotting results
    /*simplePlotter(ypx,t,yapx,ta,"Momentum-xplot.png");         // Plotting utility to visually see the results;
    simplePlotter(ypy,t,yapy,ta,"Momentum-yplot.png");         // Plotting utility to visually see the resul
    
    simplePlotter(yx,t,yax,ta,"xplot.png");         // Plotting utility to visually see the results;
    simplePlotter(yy,t,yay,ta,"yplot.png");         // Plotting utility to visually see the results;
    //simplePlotter(yy,yx,t,t,"yvst.png","time","Anlytical vs Numerical -Px");*/

    double radiusofCurvature = CalculateRadius(yy,yx,rk.tStep);
    double Timeperiod = CalculateTimePeriod(yy,yx,rk.tStep);
    std::cout<<"Radius= "<<radiusofCurvature<<" "<<"TimePeriod= "<<Timeperiod<<std::endl;



    //Ready Made implementations

    //Boost's method

    state_type z(6);
    state_type ans(6);
    state_type ans1(6);
    z[0]=0;
    z[1]=0.9*c*mass;
    z[2]=0;
    z[3]=0;
    z[4]=0;
    z[5]=0;

     
     double t0=0;
     double tf=4.5*pow(10,-10);
     double dt =(tf-t0)/n;
     std::vector<double> Px;
     std::vector<double> Py;
     std::vector<double> Pz;
     std::vector<double> x;
     std::vector<double> k;
     std::vector<double> zf;
     std::vector<double> ti;

     	
    	
    runge_kutta_fehlberg78<state_type> rk8; 

     for(int ii=0;ii<=n;ii++)
     {
         t0+=dt;
         rk8.do_step(my_system,z, t0,dt);
         Px.push_back(z[0]);
         Py.push_back(z[1]);
         Pz.push_back(z[2]);
         x.push_back(z[3]);
         k.push_back(z[4]);
         zf.push_back(z[5]);
         ti.push_back(t0);
         std::cout<<z[0]<<z[1]<<z[2]<<std::endl;
     }
     

     simplePlotter(Px,ti,ypx,t,"pxplot.png");
     simplePlotter(Py,ti,ypy,t,"pyplot.png");
     simplePlotter(Pz,ti,ypz,t,"pzplot.png");
     simplePlotter(x,ti,yx,t,"xplot.png");
     simplePlotter(k,ti,yy,t,"yplot.png");
     simplePlotter(zf,ti,yz,t,"zplot.png");
     simplePlotter(k,x,yy,yx,"x-y.png");





}