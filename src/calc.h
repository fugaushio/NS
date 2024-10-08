#include <iostream>
#include <vector>
#include <eigen3/Eigen/Core>
#include <eigen3/Eigen/Dense>
#include "namelist.h"
#include "matrix.h"
#include "outputcsv.h"

using namespace std;
using namespace Eigen;


void calc_LU(VectorXd &x, MatrixXd A, VectorXd R)
{
    // SparseMatrix<double> sparseA = A.sparseView();
    // setNbThreads(num_threads);
    // PardisoLU<SparseMatrix<double>> solver;
    // solver.compute(sparseA);
    PartialPivLU<MatrixXd> solver(A);
    x = solver.solve(R);
}

void deltastep()
{
    set_matrix();
    do
    {
        set_PQR();
        set_LHS_RHS();
        calc_LU(delta_UVP, LHS, RHS);
        /*20241007ここまで．ｄの収束判定から*/
        u += delta_UVP.segment(0, node.rows());
        v += delta_UVP.segment(node.rows(), node.rows());
        p += delta_UVP.segment(2 * node.rows(), node.rows());
    } while (delta_UVP.norm() < E_convergence);
}

void convergence_judge()
{
    cout << "convergence" << endl;
}

void timeforward(/*double Time,double DT,vector<double> u, vector<double> v, vector<double> p*/)
{
    outputfile(node,flow,p,element,0);
    for (int timestep = 0; timestep < outputtime; timestep++)
    {
        deltastep();
        convergence_judge();
        flow.col(0) = u;
        flow.col(1) = v;
        outputfile(node, flow, p, element, timestep);
    }
}

