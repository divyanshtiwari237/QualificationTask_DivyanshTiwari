#include<fstream>
#include<vector>
#include<string>
static void writetocsv(std::string filename,std::vector<double> a,std::vector<double> b,std::vector<double> c,std::vector<double> d,std::vector<double> e)
{
    std::ofstream file;
    file.open(filename, std::ios_base::app);
    file<<"Analytical"<<","<<"RK2"<<","<<"LeapFrog"<<","<<"Boost-RKF"<<","<<"BOOST-Dopri5"<<std::endl;

    for(int i=0;i<a.size();i++)
    {
        file<<a[i]<<","<<b[i]<<","<<c[i]<<","<<d[i]<<","<<e[i]<<std::endl;
    }
}