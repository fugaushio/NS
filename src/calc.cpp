#include <iostream>
#include <vector>
#include "calc.h"

using namespace std;

void timeforward(/*double Time,double DT,vector<double> u, vector<double> v, vector<double> p*/)
{
    int i = 0;
    for (int timestep = 0; timestep < 100; timestep++)
    {
        deltastep();
        convergence_judge();
    }
}

void deltastep()
{
    do
    {
        
    } while (1 > 0);
}

void convergence_judge()
{
    cout << "convergence" << endl;
}