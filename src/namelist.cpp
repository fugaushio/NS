#include <eigen3/Eigen/Core>
#include "namelist.h"

Eigen::MatrixXd node;
Eigen::MatrixXi element;
Eigen::MatrixXd flow;
Eigen::MatrixXd flow_before;

Eigen::MatrixXi BC_in;
Eigen::MatrixXi BC_out;
Eigen::MatrixXi BC_wall;

Eigen::MatrixXd M;
Eigen::MatrixXd A;
Eigen::MatrixXd Cx;
Eigen::MatrixXd Cy;
Eigen::MatrixXd D;
Eigen::MatrixXd Gx;
Eigen::MatrixXd Gy;
Eigen::MatrixXd Ms;
Eigen::MatrixXd As;
Eigen::MatrixXd Gs1;
Eigen::MatrixXd Gs2;
Eigen::MatrixXd Mp1;
Eigen::MatrixXd Mp2;
Eigen::MatrixXd Ap1;
Eigen::MatrixXd Ap2;
Eigen::MatrixXd Gp;

Eigen::MatrixXd Me;
Eigen::MatrixXd Ae;
Eigen::MatrixXd Cxe;
Eigen::MatrixXd Cye;
Eigen::MatrixXd De;
Eigen::MatrixXd Gxe;
Eigen::MatrixXd Gye;
Eigen::MatrixXd Mse;
Eigen::MatrixXd Ase;
Eigen::MatrixXd Gs1e;
Eigen::MatrixXd Gs2e;
Eigen::MatrixXd Mp1e;
Eigen::MatrixXd Mp2e;
Eigen::MatrixXd Ap1e;
Eigen::MatrixXd Ap2e;
Eigen::MatrixXd Gpe;

Eigen::MatrixXd dAudu;
Eigen::MatrixXd dAudv;
Eigen::MatrixXd dAvdu;
Eigen::MatrixXd dAvdv;
Eigen::MatrixXd dMsudu;
Eigen::MatrixXd dMsudv;
Eigen::MatrixXd dMsvdu;
Eigen::MatrixXd dMsvdv;
Eigen::MatrixXd dMsu_du;
Eigen::MatrixXd dMsu_dv;
Eigen::MatrixXd dMsv_du;
Eigen::MatrixXd dMsv_dv;
Eigen::MatrixXd dAsudu;
Eigen::MatrixXd dAsudv;
Eigen::MatrixXd dAsvdu;
Eigen::MatrixXd dAsvdv;
Eigen::MatrixXd dGs1pdu;
Eigen::MatrixXd dGs1pdv;
Eigen::MatrixXd dGs2pdu;
Eigen::MatrixXd dGs2pdv;
Eigen::MatrixXd dAp1udu;
Eigen::MatrixXd dAp1udv;
Eigen::MatrixXd dAp1vdu;
Eigen::MatrixXd dAp1vdv;
Eigen::MatrixXd dAp2udu;
Eigen::MatrixXd dAp2udv;
Eigen::MatrixXd dAp2vdu;
Eigen::MatrixXd dAp2vdv;

Eigen::MatrixXd dAudue;
Eigen::MatrixXd dAudve;
Eigen::MatrixXd dAvdue;
Eigen::MatrixXd dAvdve;
Eigen::MatrixXd dMsudue;
Eigen::MatrixXd dMsudve;
Eigen::MatrixXd dMsvdue;
Eigen::MatrixXd dMsvdve;
Eigen::MatrixXd dMsu_due;
Eigen::MatrixXd dMsu_dve;
Eigen::MatrixXd dMsv_due;
Eigen::MatrixXd dMsv_dve;
Eigen::MatrixXd dAsudue;
Eigen::MatrixXd dAsudve;
Eigen::MatrixXd dAsvdue;
Eigen::MatrixXd dAsvdve;
Eigen::MatrixXd dGs1pdue;
Eigen::MatrixXd dGs1pdve;
Eigen::MatrixXd dGs2pdue;
Eigen::MatrixXd dGs2pdve;
Eigen::MatrixXd dAp1udue;
Eigen::MatrixXd dAp1udve;
Eigen::MatrixXd dAp1vdue;
Eigen::MatrixXd dAp1vdve;
Eigen::MatrixXd dAp2udue;
Eigen::MatrixXd dAp2udve;
Eigen::MatrixXd dAp2vdue;
Eigen::MatrixXd dAp2vdve;

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
Eigen::VectorXd ue_before;
Eigen::VectorXd ve_before;
// Eigen::VectorXd b;
// Eigen::VectorXd c;
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
double taus;
double taup;

// parameter
double rou;
double myu;
double DT;
double T;
int outputtime;

double E_convergence;

int bpm;
double u_max;
double v_max;
double p0;
