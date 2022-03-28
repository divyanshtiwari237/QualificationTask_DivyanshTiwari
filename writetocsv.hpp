#include<fstream>
#include<vector>
#include<string>
static void writetocsv(std::string filename,std::vector<double> a,std::vector<double> b,std::vector<double> c)
{
    std::ofstream file;
    file.open(filename, std::ios_base::app);
    file<<"Analytical"<<","<<"RK2"<<","<<"LeapFrog"<<std::endl;

    for(int i=0;i<a.size();i++)
    {
        file<<a[i]<<","<<b[i]<<","<<c[i]<<std::endl;
    }
}