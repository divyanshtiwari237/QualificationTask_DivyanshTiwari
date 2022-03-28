#include<vector>
#include<math.h>
typedef std::vector< double > state_type;

double E[3]={0,0,0};
double B[3]= {0,0,1};
double charge = 1.60217662*pow(10,-19);
double mass =9.10938356*pow(10,-31);

static void my_system( const state_type &x , state_type &dxdt , const double t )
 {      
    dxdt[0] = charge*E[0] + (charge/mass)*(x[1]*B[2] - B[1]*x[2]);
    dxdt[1] = charge*E[1] + (charge/mass)*(x[2]*B[0] - B[2]*x[0]);
    dxdt[2] = charge*E[2] + (charge/mass)*(x[0]*B[1] - B[0]*x[1]);
    dxdt[3] = x[0]/mass;
    dxdt[4] = x[1]/mass;
    dxdt[5] = x[2]/mass;  
 
 }
