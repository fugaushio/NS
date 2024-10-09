#include <iostream>
#include <vector>
#include <eigen3/Eigen/Core>
#include <eigen3/Eigen/Dense>
#include "namelist.h"
#include "inputcsv.h"

using namespace std;
using namespace Eigen;
void set_namelists();

void get_parameter(string filename)
{
    MatrixXd parameter = readCSV_d(filename);
    /*rou,myu,DT,T,outputtime,epsilon,bpm,ux_max,uy_max,vx_max,vy_max,p0*/
    rou = parameter(0, 0);
    myu = parameter(0, 1);
    DT = parameter(0, 2);
    T = parameter(0, 3);
    outputtime = static_cast<int>(parameter(0, 4));
    E_convergence = parameter(0, 5);
}

void get_geometry(string file_node, string file_element)
{
    node = readCSV_d(file_node);
    element = readCSV_i(file_element);
}

void set_0condition()
{
    flow = MatrixXd::Zero(node.rows(), 3);
    p = VectorXd::Zero(node.rows());
    flow(0,0)=1.;

    set_namelists();
}

void set_namelists()
{
    M = MatrixXd::Zero(node.rows(), node.rows());
    Axu = MatrixXd::Zero(node.rows(), node.rows());
    Ayv = MatrixXd::Zero(node.rows(), node.rows());
    Cx = MatrixXd::Zero(node.rows(), node.rows());
    Cy = MatrixXd::Zero(node.rows(), node.rows());
    D = MatrixXd::Zero(node.rows(), node.rows());
    Gx = MatrixXd::Zero(node.rows(), node.rows());
    Gy = MatrixXd::Zero(node.rows(), node.rows());

    Me = MatrixXd::Zero(element.cols(), element.cols());
    Axue = MatrixXd::Zero(element.cols(), element.cols());
    Ayve = MatrixXd::Zero(element.cols(), element.cols());
    Cxe = MatrixXd::Zero(element.cols(), element.cols());
    Cye = MatrixXd::Zero(element.cols(), element.cols());
    De = MatrixXd::Zero(element.cols(), element.cols());
    Gxe = MatrixXd::Zero(element.cols(), element.cols());
    Gye = MatrixXd::Zero(element.cols(), element.cols());

    P = VectorXd::Zero(node.rows());
    Q = VectorXd::Zero(node.rows());
    R = VectorXd::Zero(node.rows());
    dPdu = MatrixXd::Zero(node.rows(), node.rows());
    dPdv = MatrixXd::Zero(node.rows(), node.rows());
    dPdp = MatrixXd::Zero(node.rows(), node.rows());
    dQdu = MatrixXd::Zero(node.rows(), node.rows());
    dQdv = MatrixXd::Zero(node.rows(), node.rows());
    dQdp = MatrixXd::Zero(node.rows(), node.rows());
    dRdu = MatrixXd::Zero(node.rows(), node.rows());
    dRdv = MatrixXd::Zero(node.rows(), node.rows());
    dRdp = MatrixXd::Zero(node.rows(), node.rows());

    u = VectorXd::Zero(node.rows());
    v = VectorXd::Zero(node.rows());
    u_before = VectorXd::Zero(node.rows());
    v_before = VectorXd::Zero(node.rows());
    p = VectorXd::Zero(node.rows());
    ue = VectorXd::Zero(3);
    ve = VectorXd::Zero(3);
    pe = VectorXd::Zero(3);
    // b;
    // c;
    be = VectorXd::Zero(3);
    ce = VectorXd::Zero(3);

    Ax = VectorXd::Zero(node.rows());
    Ay = VectorXd::Zero(node.rows());
    Axe = VectorXd::Zero(node.rows());
    Aye = VectorXd::Zero(node.rows());

    LHS = MatrixXd::Zero(3 * node.rows(), 3 * node.rows());
    RHS = VectorXd::Zero(3 * node.rows());

    delta_UVP = VectorXd::Zero(3 * node.rows());
}