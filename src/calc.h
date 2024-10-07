#include <iostream>
#include <vector>
#include <eigen3/Eigen/Core>
#include <eigen3/Eigen/Dense>
#include "name.h"

using namespace std;
using namespace Eigen;
using namespace HOGEHOGE;


void calc_LU(VectorXd &x, MatrixXd A, VectorXd R)
{
    // SparseMatrix<double> sparseA = A.sparseView();
    //setNbThreads(num_threads);
    // PardisoLU<SparseMatrix<double>> solver;
    // solver.compute(sparseA);
    PartialPivLU<MatrixXd> solver(A);
    x = solver.solve(R);
}

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
        calc_LU(delta_UVP,LHS,RHS);
        /*20241007ここまで．ｄの収束判定から*/
        
    } while (1 > 0);
}

void convergence_judge()
{
    cout << "convergence" << endl;
}