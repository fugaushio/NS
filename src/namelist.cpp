#include <eigen3/Eigen/Core>
#include "namelist.h"

Eigen::MatrixXd node;
Eigen::MatrixXi element;
Eigen::MatrixXd flow;

Eigen::MatrixXd M;
Eigen::MatrixXd Axu;
Eigen::MatrixXd Ayv;
Eigen::MatrixXd Cx;
Eigen::MatrixXd Cy;
Eigen::MatrixXd D;
Eigen::MatrixXd Gx;
Eigen::MatrixXd Gy;

Eigen::MatrixXd Me;
Eigen::MatrixXd Axue;
Eigen::MatrixXd Ayve;
Eigen::MatrixXd Cxe;
Eigen::MatrixXd Cye;
Eigen::MatrixXd De;
Eigen::MatrixXd Gxe;
Eigen::MatrixXd Gye;

Eigen::VectorXd P;
Eigen::VectorXd Q;
Eigen::VectorXd R;
Eigen::MatrixXd dPdu;
Eigen::MatrixXd dPdv;
Eigen::MatrixXd dPdp;
Eigen::MatrixXd dQdu;
Eigen::MatrixXd dQdv;
Eigen::MatrixXd dQdp;
Eigen::MatrixXd dRdu;
Eigen::MatrixXd dRdv;
Eigen::MatrixXd dRdp;

Eigen::MatrixXd LHS;

Eigen::VectorXd u;
Eigen::VectorXd v;
Eigen::VectorXd u_before;
Eigen::VectorXd v_before;
Eigen::VectorXd p;
Eigen::VectorXd ue;
Eigen::VectorXd ve;
Eigen::VectorXd pe;
//Eigen::VectorXd b;
//Eigen::VectorXd c;
Eigen::VectorXd be;
Eigen::VectorXd ce;

Eigen::VectorXd Ax;
Eigen::VectorXd Ay;
Eigen::VectorXd Axe;
Eigen::VectorXd Aye;

Eigen::VectorXd RHS;

Eigen::VectorXd delta_UVP;

int num_elem;
double Se;

// parameter
double rou;
double myu;
double DT;
double T;
int outputtime;

double E_convergence;
