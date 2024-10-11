#ifndef NAMELIST_H
#define NAMELIST_H

extern Eigen::MatrixXd node;
extern Eigen::MatrixXi element;
extern Eigen::MatrixXd flow;
extern Eigen::MatrixXd flow_before;

extern Eigen::MatrixXi BC_in;
extern Eigen::MatrixXi BC_out;
extern Eigen::MatrixXi BC_wall;

extern Eigen::MatrixXd M;
extern Eigen::MatrixXd A;
extern Eigen::MatrixXd Cx;
extern Eigen::MatrixXd Cy;
extern Eigen::MatrixXd D;
extern Eigen::MatrixXd Gx;
extern Eigen::MatrixXd Gy;
extern Eigen::MatrixXd Ms;
extern Eigen::MatrixXd As;
extern Eigen::MatrixXd Gs1;
extern Eigen::MatrixXd Gs2;
extern Eigen::MatrixXd Mp1;
extern Eigen::MatrixXd Mp2;
extern Eigen::MatrixXd Ap1;
extern Eigen::MatrixXd Ap2;
extern Eigen::MatrixXd Gp;

extern Eigen::MatrixXd Me;
extern Eigen::MatrixXd Ae;
extern Eigen::MatrixXd Cxe;
extern Eigen::MatrixXd Cye;
extern Eigen::MatrixXd De;
extern Eigen::MatrixXd Gxe;
extern Eigen::MatrixXd Gye;
extern Eigen::MatrixXd Mse;
extern Eigen::MatrixXd Ase;
extern Eigen::MatrixXd Gs1e;
extern Eigen::MatrixXd Gs2e;
extern Eigen::MatrixXd Mp1e;
extern Eigen::MatrixXd Mp2e;
extern Eigen::MatrixXd Ap1e;
extern Eigen::MatrixXd Ap2e;
extern Eigen::MatrixXd Gpe;

extern Eigen::MatrixXd dAudu;
extern Eigen::MatrixXd dAudv;
extern Eigen::MatrixXd dAvdu;
extern Eigen::MatrixXd dAvdv;
extern Eigen::MatrixXd dMsudu;
extern Eigen::MatrixXd dMsudv;
extern Eigen::MatrixXd dMsvdu;
extern Eigen::MatrixXd dMsvdv;
extern Eigen::MatrixXd dMsu_du;
extern Eigen::MatrixXd dMsu_dv;
extern Eigen::MatrixXd dMsv_du;
extern Eigen::MatrixXd dMsv_dv;
extern Eigen::MatrixXd dAsudu;
extern Eigen::MatrixXd dAsudv;
extern Eigen::MatrixXd dAsvdu;
extern Eigen::MatrixXd dAsvdv;
extern Eigen::MatrixXd dGs1pdu;
extern Eigen::MatrixXd dGs1pdv;
extern Eigen::MatrixXd dGs2pdu;
extern Eigen::MatrixXd dGs2pdv;
extern Eigen::MatrixXd dAp1udu;
extern Eigen::MatrixXd dAp1udv;
extern Eigen::MatrixXd dAp1vdu;
extern Eigen::MatrixXd dAp1vdv;
extern Eigen::MatrixXd dAp2udu;
extern Eigen::MatrixXd dAp2udv;
extern Eigen::MatrixXd dAp2vdu;
extern Eigen::MatrixXd dAp2vdv;

extern Eigen::MatrixXd dAudue;
extern Eigen::MatrixXd dAudve;
extern Eigen::MatrixXd dAvdue;
extern Eigen::MatrixXd dAvdve;
extern Eigen::MatrixXd dMsudue;
extern Eigen::MatrixXd dMsudve;
extern Eigen::MatrixXd dMsvdue;
extern Eigen::MatrixXd dMsvdve;
extern Eigen::MatrixXd dMsu_due;
extern Eigen::MatrixXd dMsu_dve;
extern Eigen::MatrixXd dMsv_due;
extern Eigen::MatrixXd dMsv_dve;
extern Eigen::MatrixXd dAsudue;
extern Eigen::MatrixXd dAsudve;
extern Eigen::MatrixXd dAsvdue;
extern Eigen::MatrixXd dAsvdve;
extern Eigen::MatrixXd dGs1pdue;
extern Eigen::MatrixXd dGs1pdve;
extern Eigen::MatrixXd dGs2pdue;
extern Eigen::MatrixXd dGs2pdve;
extern Eigen::MatrixXd dAp1udue;
extern Eigen::MatrixXd dAp1udve;
extern Eigen::MatrixXd dAp1vdue;
extern Eigen::MatrixXd dAp1vdve;
extern Eigen::MatrixXd dAp2udue;
extern Eigen::MatrixXd dAp2udve;
extern Eigen::MatrixXd dAp2vdue;
extern Eigen::MatrixXd dAp2vdve;

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
extern Eigen::VectorXd ue_before;
extern Eigen::VectorXd ve_before;
// extern Eigen::VectorXd b;
// extern Eigen::VectorXd c;
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
extern double taus;
extern double taup;

// parameter
extern double rou;
extern double myu;
extern double DT;
extern double T;
extern int outputtime;

extern double E_convergence;
extern int bpm;
extern double u_max;
extern double v_max;
extern double p0;

#endif