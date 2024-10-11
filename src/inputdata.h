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
    /*rou,myu,DT,T,outputtime,epsilon,bpm,u_max,v_max,p0*/
    rou = parameter(0, 0);
    myu = parameter(0, 1);
    DT = parameter(0, 2);
    T = parameter(0, 3);
    outputtime = static_cast<int>(parameter(0, 4));
    E_convergence = parameter(0, 5);
    bpm = static_cast<int>(parameter(0, 6));
    u_max = parameter(0, 7);
    v_max = parameter(0, 8);
    p0 = parameter(0, 9);
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
    flow_before = flow;

    set_namelists();
}

void get_BCPoint(string file_in, string file_out, string file_wall)
{
    BC_in = readCSV_i(file_in);
    BC_out = readCSV_i(file_out);
    BC_wall = readCSV_i(file_wall);
}

void set_namelists()
{
    M = MatrixXd::Zero(node.rows(), node.rows());
    A = MatrixXd::Zero(node.rows(), node.rows());
    Cx = MatrixXd::Zero(node.rows(), node.rows());
    Cy = MatrixXd::Zero(node.rows(), node.rows());
    D = MatrixXd::Zero(node.rows(), node.rows());
    Gx = MatrixXd::Zero(node.rows(), node.rows());
    Gy = MatrixXd::Zero(node.rows(), node.rows());
    Ms = MatrixXd::Zero(node.rows(), node.rows());
    As = MatrixXd::Zero(node.rows(), node.rows());
    Gs1 = MatrixXd::Zero(node.rows(), node.rows());
    Gs2 = MatrixXd::Zero(node.rows(), node.rows());
    Mp1 = MatrixXd::Zero(node.rows(), node.rows());
    Mp2 = MatrixXd::Zero(node.rows(), node.rows());
    Ap1 = MatrixXd::Zero(node.rows(), node.rows());
    Ap2 = MatrixXd::Zero(node.rows(), node.rows());
    Gp = MatrixXd::Zero(node.rows(), node.rows());

    Me = MatrixXd::Zero(element.cols(), element.cols());
    Ae = MatrixXd::Zero(element.cols(), element.cols());
    Cxe = MatrixXd::Zero(element.cols(), element.cols());
    Cye = MatrixXd::Zero(element.cols(), element.cols());
    De = MatrixXd::Zero(element.cols(), element.cols());
    Gxe = MatrixXd::Zero(element.cols(), element.cols());
    Gye = MatrixXd::Zero(element.cols(), element.cols());
    Mse = MatrixXd::Zero(element.cols(), element.cols());
    Ase = MatrixXd::Zero(element.cols(), element.cols());
    Gs1e = MatrixXd::Zero(element.cols(), element.cols());
    Gs2e = MatrixXd::Zero(element.cols(), element.cols());
    Mp1e = MatrixXd::Zero(element.cols(), element.cols());
    Mp2e = MatrixXd::Zero(element.cols(), element.cols());
    Ap1e = MatrixXd::Zero(element.cols(), element.cols());
    Ap2e = MatrixXd::Zero(element.cols(), element.cols());
    Gpe = MatrixXd::Zero(element.cols(), element.cols());

    dAudu = MatrixXd::Zero(node.rows(), node.rows());
    dAudv = MatrixXd::Zero(node.rows(), node.rows());
    dAvdu = MatrixXd::Zero(node.rows(), node.rows());
    dAvdv = MatrixXd::Zero(node.rows(), node.rows());
    dMsudu = MatrixXd::Zero(node.rows(), node.rows());
    dMsudv = MatrixXd::Zero(node.rows(), node.rows());
    dMsvdu = MatrixXd::Zero(node.rows(), node.rows());
    dMsvdv = MatrixXd::Zero(node.rows(), node.rows());
    dMsu_du = MatrixXd::Zero(node.rows(), node.rows());
    dMsu_dv = MatrixXd::Zero(node.rows(), node.rows());
    dMsv_du = MatrixXd::Zero(node.rows(), node.rows());
    dMsv_dv = MatrixXd::Zero(node.rows(), node.rows());
    dAsudu = MatrixXd::Zero(node.rows(), node.rows());
    dAsudv = MatrixXd::Zero(node.rows(), node.rows());
    dAsvdu = MatrixXd::Zero(node.rows(), node.rows());
    dAsvdv = MatrixXd::Zero(node.rows(), node.rows());
    dGs1pdu = MatrixXd::Zero(node.rows(), node.rows());
    dGs1pdv = MatrixXd::Zero(node.rows(), node.rows());
    dGs2pdu = MatrixXd::Zero(node.rows(), node.rows());
    dGs2pdv = MatrixXd::Zero(node.rows(), node.rows());
    dAp1udu = MatrixXd::Zero(node.rows(), node.rows());
    dAp1udv = MatrixXd::Zero(node.rows(), node.rows());
    dAp1vdu = MatrixXd::Zero(node.rows(), node.rows());
    dAp1vdv = MatrixXd::Zero(node.rows(), node.rows());
    dAp2udu = MatrixXd::Zero(node.rows(), node.rows());
    dAp2udv = MatrixXd::Zero(node.rows(), node.rows());
    dAp2vdu = MatrixXd::Zero(node.rows(), node.rows());
    dAp2vdv = MatrixXd::Zero(node.rows(), node.rows());

    dAudue = MatrixXd::Zero(element.cols(), element.cols());
    dAudve = MatrixXd::Zero(element.cols(), element.cols());
    dAvdue = MatrixXd::Zero(element.cols(), element.cols());
    dAvdve = MatrixXd::Zero(element.cols(), element.cols());
    dMsudue = MatrixXd::Zero(element.cols(), element.cols());
    dMsudve = MatrixXd::Zero(element.cols(), element.cols());
    dMsvdue = MatrixXd::Zero(element.cols(), element.cols());
    dMsvdve = MatrixXd::Zero(element.cols(), element.cols());
    dMsu_due = MatrixXd::Zero(element.cols(), element.cols());
    dMsu_dve = MatrixXd::Zero(element.cols(), element.cols());
    dMsv_due = MatrixXd::Zero(element.cols(), element.cols());
    dMsv_dve = MatrixXd::Zero(element.cols(), element.cols());
    dAsudue = MatrixXd::Zero(element.cols(), element.cols());
    dAsudve = MatrixXd::Zero(element.cols(), element.cols());
    dAsvdue = MatrixXd::Zero(element.cols(), element.cols());
    dAsvdve = MatrixXd::Zero(element.cols(), element.cols());
    dGs1pdue = MatrixXd::Zero(element.cols(), element.cols());
    dGs1pdve = MatrixXd::Zero(element.cols(), element.cols());
    dGs2pdue = MatrixXd::Zero(element.cols(), element.cols());
    dGs2pdve = MatrixXd::Zero(element.cols(), element.cols());
    dAp1udue = MatrixXd::Zero(element.cols(), element.cols());
    dAp1udve = MatrixXd::Zero(element.cols(), element.cols());
    dAp1vdue = MatrixXd::Zero(element.cols(), element.cols());
    dAp1vdve = MatrixXd::Zero(element.cols(), element.cols());
    dAp2udue = MatrixXd::Zero(element.cols(), element.cols());
    dAp2udve = MatrixXd::Zero(element.cols(), element.cols());
    dAp2vdue = MatrixXd::Zero(element.cols(), element.cols());
    dAp2vdve = MatrixXd::Zero(element.cols(), element.cols());

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
    ue_before = VectorXd::Zero(node.rows());
    ve_before = VectorXd::Zero(node.rows());
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