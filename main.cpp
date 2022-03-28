#include<iostream>
#include "rk2.hpp"
#include<math.h>
#include"analytical.hpp"
#include "utilities.hpp"
#include"boostimpl.hpp"
#include<boost/numeric/odeint.hpp>
#include"gnuplot-iostream.h"
#include"leapfrog.hpp"
#include <boost/tuple/tuple.hpp>
#include <boost/filesystem.hpp>
#include"writetocsv.hpp"
using namespace boost::numeric::odeint;

typedef std::vector< double > state_type;
std::vector<double> answer[6];
static void my_observer( const state_type &x, const double t )
 {   
      for(int i=0;i<6;i++)
      {
          answer[i].push_back(x[i]);
      }  
      
 }



int main()
{
    // Initial conditions
    double mass =9.10938356*pow(10,-31);
    double c = 3*pow(10,8); //speed of light
    double E[3] ={0,0,0};  //initialize the electric field
    double B[3]={0,0,1};  //initialize the magnetic field
    double y[6]={0,0.9*c,0,0,0,0}; // initial conditions of the particle
    double t0=0; //Initial time
    double tf=50.5*pow(10,-11);//final time
    double tStep=0.25*1.78265*pow(10,-10);  // time step;
    int n =(10.5*pow(10,-9))/tStep;//number of steps in the integration

    Analytical A(B[2],n,t0,tf,y); //initialize the analytic solution with the required fields.
    A.calculate(y);// call the implementing function

    double a[6]={0,0.9*c,0,0,0,0};
    RK2 rk(t0,tf,E,B);  //initialize the RK2 class with the required fields.     
    rk.rk2(a,n);  // call the implementing function
    double radiusofCurvature = CalculateRadius(rk.answery,rk.answerx,rk.tStep); //calculate radius of curvature
    double Timeperiod = CalculateTimePeriod(rk.answery,rk.answerx,rk.tStep); //calculate timeperiod

     double b[6]={0,0.9*c,0,0,0,0};
    LeapFrog lp(t0,tf,E,B); //initialize the LeapFrog class with the required fields.
    lp.leapfrogcall(b,n); // call the implementing function 


    //Ready Made implementations

    //Boost's RKF method
     std::vector<double> Px;
     std::vector<double> Py;
     std::vector<double> Pz;
     std::vector<double> x;
     std::vector<double> k;
     std::vector<double> zf;
     std::vector<double> ti;
     state_type ci(6,0);
     ci[1]=0.9*c*mass;
     
    //initialize the RK2 class with the required fields.
    runge_kutta_fehlberg78<state_type> rk8; //Step-up the stepper function

     for(int ii=0;ii<=n;ii++)  //calculating values with the do_step method
     {
         t0+=tStep;
         rk8.do_step(my_system,ci, t0,tStep);
         Px.push_back(ci[0]);
         Py.push_back(ci[1]);
         Pz.push_back(ci[2]);
         x.push_back(ci[3]);
         k.push_back(ci[4]);
         zf.push_back(ci[5]);
         ti.push_back(t0);
         
     }
     t0=0;

    //Boost's Dopri5 method
     state_type d(6,0);
     d[1]=0.9*c*mass;
    
    runge_kutta_dopri5<state_type> rkdopri5; 
    auto c_stepper = make_controlled(1.E-13, 1.E-8, rkdopri5); //error control
    integrate_adaptive(c_stepper, my_system , d , t0 , tf , tStep,my_observer );  //calculating values with the Integrate_adaptive method
     
     //Storing values in the data.csv file
    writetocsv("data.csv",A.answerPx,rk.answerPx,lp.answerPx);
     

    
      
    //Graphing Utilities
    std::vector<std::pair<double,double>>plot;
    for(int i=0;i<n;i++)
    {
        plot.push_back(std::make_pair(ti[i],Px[i]));    
    }
    /*Gnuplot gp;
    std::vector<boost::tuple<double, double, double, double> > pts_A;*/
    //Don't forget to put "\n" at the end of each line!
	//gp << "set xrange [-2:2]\nset yrange [-2:2]\n";
	// '-' means read from stdin.  The send1d() function sends data to gnuplot's stdin.
	/*gp << "plot '-' using 1:2 with lines'Numerical','-' using 1:2 with lines title 'Analytical'\n";
	gp.send1d(plot1);
    gp.send1d(plot1);*/

	//gp.send1d(yx);

    /*gp << "plot '-' with lines title 'rk2', '-' with lines title 'rkf'\n";
    gp.send1d(ypx);
    gp.send1d(Px);*/

    /*gp << "plot '-' with lines title 'rk2', '-' with lines title 'Dopri5'\n";
    gp.send1d(ypx);
    gp.send1d(answer[0]);*/
  
    //gp.send1d(plot1);
    //Gnuplot gp;
    //gp << "set xrange [-0.25:.25]\nset yrange [-0.25:0.25]\n";
    /*gp << "plot '-' with lines title 'Numerical', '-' with lines title 'Analytical'\n";
    gp.send1d(lp.answerPx);
    gp.send1d(yapx);*/

    //gp << "plot '-' using 1:2 with lines title'LeapFrog'\n";
	//gp.send1d(plot);

   /* gp << "plot'-' with lines title ' rk',   '-' with lines title ' LeapFrog'\n";
    gp.send1d(ypx);
    gp.send1d(ypxlp);*/
#ifdef _WIN32
	// For Windows, prompt for a keystroke before the Gnuplot object goes out of scope so that
	// the gnuplot window doesn't get closed.
	std::cout << "Press enter to exit." << std::endl;
	std::cin.get();
#endif

}