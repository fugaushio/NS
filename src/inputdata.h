#include <iostream>
#include <vector>
#include <eigen3/Eigen/Core>
#include <eigen3/Eigen/Dense>
#include "namelist.h"
#include "inputcsv.h"

using namespace std;
using namespace Eigen;


void get_parameter()
{
    MatrixXd parameter = readCSV_d("parameter.csv");
    /*rou,myu,DT,T,outputtime,epsilon,bpm,ux_max,uy_max,vx_max,vy_max,p0*/
    rou = parameter(0, 0);
    myu = parameter(0, 1);
    DT = parameter(0, 3);
    T = parameter(0, 4);
    outputtime = static_cast<int>(parameter(0, 5));
    E_convergence = parameter(0, 5);
}

void get_geometry()
{
    node = readCSV_d("node.csv");
    element = readCSV_i("element");
}

void set_0condition()
{
    flow = MatrixXd::Zero(node.rows(), 2);
    p = VectorXd::Zero(node.rows());
}