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
    cout << "calc" << endl;
}

void deltastep()
{
    int j = 0;
    do
    {
        set_PQR();
        set_LHS_RHS();
        calc_LU(delta_UVP, LHS, RHS);
        /*20241007ここまで．ｄの収束判定から*/
        u += delta_UVP.segment(0, node.rows());
        v += delta_UVP.segment(node.rows(), node.rows());
        p += delta_UVP.segment(2 * node.rows(), node.rows());
        j++;
    } while (/*delta_UVP.norm() < E_convergence*/ j < 2);
}

void convergence_judge()
{
    cout << "convergence" << endl;
}

bool hasNaN(MatrixXd mat, double threshold = 1.e15)
{
    // 行列の各要素をチェックしてNaNが含まれているかを判定
    for (int i = 0; i < mat.rows(); ++i)
    {
        for (int j = 0; j < mat.cols(); ++j)
        {
            if (!isfinite(mat(i, j)) || abs(mat(i, j)) > threshold)
            {
                return true; // NaNが見つかった場合
            }
        }
    }
    return false; // NaNが見つからなかった場合
}

void timeforward(/*double Time,double DT,vector<double> u, vector<double> v, vector<double> p*/)
{
    outputfile(node, flow, p, element, 0);
    set_matrix();
    u = flow.col(0);
    v = flow.col(1);
    u_before = u;
    v_before = v;
    for (int timestep = 0; timestep < T / DT; timestep++)
    {

        deltastep();
        convergence_judge();
        flow.col(0) = u;
        flow.col(1) = v;
        u_before = u;
        v_before = v;
        if (hasNaN(flow))
        {
            cout << "generate NaN values. error" << endl;
            break;
        }

        if (timestep % static_cast<int>(T / DT / outputtime) == 0)
        {
            outputfile(node, flow, p, element, timestep);
            // cout <<"timestep:"<<timestep<<endl<<flow<<endl;
        }
        cout << "finish timestep:" << timestep << endl;
    }
}
