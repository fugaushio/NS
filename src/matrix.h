#include <iostream>
#include "name.h"
using namespace HOGEHOGE;
using namespace Eigen;

double get_Se(int num_elem, MatrixXd node, MatrixXi element)
{
    double x0 = node(element(num_elem, 0), 0);
    double x1 = node(element(num_elem, 1), 0);
    double x2 = node(element(num_elem, 2), 0);
    double y0 = node(element(num_elem, 0), 1);
    double y1 = node(element(num_elem, 1), 1);
    double y2 = node(element(num_elem, 2), 1);

    return fabs((x1 - x0) * (y2 - y0) - (x2 - x0) * (y1 - y0)) / 2.;
}

void set_bc(int num_elem, VectorXd &b, VectorXd &c, MatrixXd node, MatrixXi element)
{
    double x0 = node(element(num_elem, 0), 0);
    double x1 = node(element(num_elem, 1), 0);
    double x2 = node(element(num_elem, 2), 0);
    double y0 = node(element(num_elem, 0), 1);
    double y1 = node(element(num_elem, 1), 1);
    double y2 = node(element(num_elem, 2), 1);

    b(0) = y1 - y2;
    b(1) = y2 - y0;
    b(2) = y0 - y1;
    b /= 2 * get_Se(num_elem, node, element);
    c(0) = x2 - x1;
    c(1) = x0 - x2;
    c(2) = x1 - x0;
    c /= 2 * get_Se(num_elem, node, element);
}

void set_uve(int num_elem, VectorXd &u, VectorXd &v, MatrixXd flow, MatrixXi element)
{
    u(0) = flow(element(num_elem, 0), 0);
    u(1) = flow(element(num_elem, 1), 0);
    u(2) = flow(element(num_elem, 2), 0);
    v(0) = flow(element(num_elem, 0), 1);
    v(1) = flow(element(num_elem, 1), 1);
    v(2) = flow(element(num_elem, 2), 1);
}

void add_matrix(MatrixXd Xe, MatrixXd &X, MatrixXi element, int i)
{
    for (int j = 0; j < Xe.rows(); j++)
    {
        for (int k = 0; k < Xe.rows(); k++)
        {
            X(element(i, j), element(i, k)) += Xe(j, k);
        }
    }
}

void add_vector(VectorXd Xe, VectorXd &X, MatrixXi element, int i)
{
    for (int j = 0; j < Xe.size(); j++)
    {
        X(element(i, j)) += Xe(j);
    }
}

void set_matrix()
{
    double Se = 0.;
    double tau = 0.;

    for (int i = 0; i < element.rows(); i++)
    {
        Se = get_Se(i, node, element);
        set_uve(i, ue, ve, flow, element);
        set_bc(i, be, ce, node, element);
        Me << 2., 1., 1.,
            1., 2., 1.,
            1., 1., 2.;
        Me *= Se / 12.;

        Cxe << be(0), be(1), be(2), be(0), be(1), be(2), be(0), be(1), be(2);
        Cye << ce(0), ce(1), ce(2), ce(0), ce(1), ce(2), ce(0), ce(1), ce(2);
        Cxe *= Se / 3.;
        Cye *= Se / 3.;

        Gxe = Cxe.transpose();
        Gye = Cye.transpose();
        De = Se * (be * be.transpose() + ce * ce.transpose());

        // tau = get_tau(ue, ve, para(2), Se, flag);
        // Mse = tau * Ae.transpose();
        // Ase = tau * Ae.transpose() * Me.inverse() * Ae;

        add_matrix(Me, M, element, i);
        add_matrix(De, D, element, i);
        add_matrix(Cxe, Cx, element, i);
        add_matrix(Cye, Cy, element, i);
        add_matrix(Gxe, Gx, element, i);
        add_matrix(Gye, Gy, element, i);
    }
}

void set_PQR()
{

    for (int i = 0; i < element.rows(); i++)
    {
        Se = get_Se(i, node, element);
        set_uve(i, ue, ve, flow, element);
        set_bc(i, be, ce, node, element);
        Me << 2., 1., 1.,
            1., 2., 1.,
            1., 1., 2.;
        Me *= Se / 12.;

        Axue = Me * ue * be.transpose();
        Ayve = Me * ve * ce.transpose();
        Axe = Me * be;
        Aye = Me * ce;

        add_matrix(Axue, Axu, element, i);
        add_matrix(Ayve, Ayv, element, i);
        add_vector(Axe, Ax, element, i);
        add_vector(Axe, Ax, element, i);
    }

    P = rou * M * u / DT + rou * (Axu + Ayv) * u - Gx * p + myu * D * u - rou * M * u_before / DT;
    Q = rou * M * v / DT + rou * (Axu + Ayv) * v - Gy * p + myu * D * v - rou * M * v_before / DT;
    R = Cx * u + Cy * v;

    dPdu = rou * M / DT + 2. * rou * Axu + rou * Ayv + myu * D;
    dPdv = rou * Ay * u.transpose();
    dPdp = -Gx;
    dQdu = rou * Ax * v.transpose();
    dQdv = rou * M / DT + rou * Axu + 2. * rou * Ayv + myu * D;
    dQdp = -Gy;
    dRdu = Cx;
    dRdv = Cy;
    dRdp = MatrixXd::Zero(node.rows(), node.rows());
}

void set_LHS_RHS()
{
    LHS = MatrixXd::Zero(3 * node.rows(), 3 * node.rows());
    RHS = VectorXd::Zero(3 * node.rows());

    LHS.block(0, 0, node.rows(), node.rows()) = dPdu;
    LHS.block(0, node.rows(), node.rows(), node.rows()) = dPdv;
    LHS.block(0, 2 * node.rows(), node.rows(), node.rows()) = dPdp;
    LHS.block(node.rows(), 0, node.rows(), node.rows()) = dQdu;
    LHS.block(node.rows(), node.rows(), node.rows(), node.rows()) = dQdv;
    LHS.block(node.rows(), 2 * node.rows(), node.rows(), node.rows()) = dQdp;
    LHS.block(2 * node.rows(), 0, node.rows(), node.rows()) = dRdu;
    LHS.block(2 * node.rows(), node.rows(), node.rows(), node.rows()) = dRdv;
    LHS.block(2 * node.rows(), 2 * node.rows(), node.rows(), node.rows()) = dRdp;

    RHS.segment(0, node.rows()) = -P;
    RHS.segment(node.rows(), node.rows()) = -Q;
    RHS.segment(2 * node.rows(), node.rows()) = -R;
}