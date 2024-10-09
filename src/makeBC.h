#include <iostream>
#include <vector>
#include <eigen3/Eigen/Core>
#include <eigen3/Eigen/Dense>
#include "namelist.h"

using namespace std;
using namespace Eigen;

double CSFflow(double t, int bpm)
{
    double x = 1.67 * t * bpm / 60;
    // double y = 5.5957 - 0.36930 * x + 2.8397e-3 * pow(x, 2) - 8.6368e-6 * pow(x, 3) + 1.1811e-8 * pow(x, 4) - 5.9872e-12 * pow(x, 5);
    double y = -2.9744e2 * x + 2.8974e3 * pow(x, 2) - 7.1637e3 * pow(x, 3) + 7.1994e3 * pow(x, 4) - 3.1752e3 * pow(x, 5) + 5.0834e2 * pow(x, 6);
    y /= 40.;
    return y;
}

void set_BC(double t)
{
    for (int i = 0; i < BC_in.rows(); i++)
    {
        u(BC_in(i, 0)) = u_max * CSFflow(t, bpm);
        v(BC_in(i, 0)) = v_max * CSFflow(t, bpm);
    }

    for (int i = 0; i < BC_out.rows(); i++)
    {
        p(BC_out(i, 0)) = p0;
    }

    for (int i = 0; i < BC_wall.rows(); i++)
    {
        u(BC_wall(i, 0)) = 0;
        v(BC_wall(i, 0)) = 0;
    }
}

void fix_LHS_RHS()
{

    for (int i = 0; i < BC_in.rows(); i++)
    {
        for (int j = 0; j < LHS.rows(); j++)
        {

            LHS(BC_in(i, 0), j) = 0.;
            LHS(BC_in(i, 0) + node.rows(), j) = 0.;
        }
        LHS(BC_in(i, 0), BC_in(i, 0)) = 1.;
        LHS(BC_in(i, 0) + node.rows(), BC_in(i, 0) + node.rows()) = 1.;
        RHS(BC_in(i, 0)) = 0.;
        RHS(BC_in(i, 0) + node.rows()) = 0.;
    }

    for (int i = 0; i < BC_out.rows(); i++)
    {
        for (int j = 0; j < 3 * node.rows(); j++)
        {
            LHS(BC_out(i, 0) + 2 * node.rows(), j) = 0.;
        }
        LHS(BC_out(i, 0) + 2 * node.rows(), BC_out(i, 0) + 2 * node.rows()) = 1.;
        RHS(BC_out(i, 0) + 2 * node.rows()) = 0.;
    }

    for (int i = 0; i < BC_wall.rows(); i++)
    {
        for (int j = 0; j < 3 * node.rows(); j++)
        {
            LHS(BC_wall(i, 0), j) = 0.;
            LHS(BC_wall(i, 0) + node.rows(), j) = 0.;
        }
        LHS(BC_wall(i, 0), BC_wall(i, 0)) = 1.;
        LHS(BC_wall(i, 0) + node.rows(), BC_wall(i, 0) + node.rows()) = 1.;
        RHS(BC_wall(i, 0)) = 0.;
        RHS(BC_wall(i, 0) + node.rows()) = 0.;
    }
}