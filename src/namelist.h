#ifndef NAMELIST_H
#define NAMELIST_H

extern Eigen::MatrixXd node;
extern Eigen::MatrixXi element;
extern Eigen::MatrixXd flow;

extern Eigen::MatrixXd M;
extern Eigen::MatrixXd Axu;
extern Eigen::MatrixXd Ayv;
extern Eigen::MatrixXd Cx;
extern Eigen::MatrixXd Cy;
extern Eigen::MatrixXd D;
extern Eigen::MatrixXd Gx;
extern Eigen::MatrixXd Gy;

extern Eigen::MatrixXd Me;
extern Eigen::MatrixXd Axue;
extern Eigen::MatrixXd Ayve;
extern Eigen::MatrixXd Cxe;
extern Eigen::MatrixXd Cye;
extern Eigen::MatrixXd De;
extern Eigen::MatrixXd Gxe;
extern Eigen::MatrixXd Gye;

extern Eigen::VectorXd P;
extern Eigen::VectorXd Q;
extern Eigen::VectorXd R;
extern Eigen::MatrixXd dPdu;
extern Eigen::MatrixXd dPdv;
extern Eigen::MatrixXd dPdp;
extern Eigen::MatrixXd dQdu;
extern Eigen::MatrixXd dQdv;
extern Eigen::MatrixXd dQdp;
extern Eigen::MatrixXd dRdu;
extern Eigen::MatrixXd dRdv;
extern Eigen::MatrixXd dRdp;

extern Eigen::MatrixXd LHS;

extern Eigen::VectorXd u;
extern Eigen::VectorXd v;
extern Eigen::VectorXd u_before;
extern Eigen::VectorXd v_before;
extern Eigen::VectorXd p;
extern Eigen::VectorXd ue;
extern Eigen::VectorXd ve;
extern Eigen::VectorXd pe;
//extern Eigen::VectorXd b;
//extern Eigen::VectorXd c;
extern Eigen::VectorXd be;
extern Eigen::VectorXd ce;

extern Eigen::VectorXd Ax;
extern Eigen::VectorXd Ay;
extern Eigen::VectorXd Axe;
extern Eigen::VectorXd Aye;

extern Eigen::VectorXd RHS;

extern Eigen::VectorXd delta_UVP;

extern int num_elem;
extern double Se;

// parameter
extern double rou;
extern double myu;
extern double DT;
extern double T;
extern int outputtime;

extern double E_convergence;

#endif