#include <iostream>
#include "namelist.h"

using namespace Eigen;
using namespace std;
double pi = 3.1415926535;
MatrixXd I = MatrixXd::Identity(3, 3);

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

double get_taus(VectorXd ue, VectorXd ve, double nyu, double Se)
{
    double tau;
    double he = sqrt(4. * Se / pi);
    tau = pow(pow((ue.norm() + ve.norm()) / he, 2.) + pow(4. * nyu / he / he, 2.), -0.5);
    return tau;
}

double get_taup(VectorXd ue, VectorXd ve, double nyu, double Se)
{
    double tau;
    double he = sqrt(4. * Se / pi);
    tau = he * (ue.norm() + ve.norm()) / 4.;
    return tau;
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
    Se = 0.;
    taus = 0.;
    taup = 0.;

    for (int i = 0; i < element.rows(); i++)
    {
        Se = get_Se(i, node, element);
        set_uve(i, ue, ve, flow, element);
        set_uve(i, ue_before, ve_before, flow_before, element);
        set_bc(i, be, ce, node, element);
        taus = get_taus(ue, ve, myu / rou, Se);
        taup = get_taup(ue, ve, myu / rou, Se);

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

        Ae = Me * (ue * be.transpose() + ve * ce.transpose());
        dAudue = be.dot(ue) * Me + Ae;
        dAudve = ce.dot(ue) * Me;
        dAvdue = be.dot(ve) * Me;
        dAvdve = ce.dot(ve) * Me + Ae;

        // SUPG
        Ms = taus * (be * ue.transpose() + ce * ve.transpose());
        dMsudu = taus * (2 * be * ue.transpose() + ce * ve.transpose()) * Me;
        dMsudv = taus * (ce * ue.transpose()) * Me;
        dMsvdu = taus * (be * ve.transpose()) * Me;
        dMsvdv = taus * (be * ue.transpose() + 2 * ce * ve.transpose()) * Me;
        dMsu_du = taus * (be * ue_before.transpose()) * Me;
        dMsu_dv = taus * (ce * ue_before.transpose()) * Me;
        dMsv_du = taus * (be * ve_before.transpose()) * Me;
        dMsv_dv = taus * (ce * ve_before.transpose()) * Me;

        As = taus * (be * ue.transpose() + ce * ve.transpose()) * Me * (ue * be.transpose() + ve * ce.transpose());
        dAsudu = taus * (be.transpose() * Me * (be.dot(ue) * ue + ce.dot(ue) * ve) + (be * ue.transpose() + ce * ve.transpose()) * Me * (be.dot(ue) * I + ue * be.transpose() + ve * ce.transpose()));
        dAsudv = taus * (ce.transpose() * Me * (be.dot(ue) * ue + ce.dot(ue) * ve) + (be * ue.transpose() + ce * ve.transpose()) * Me * (ce.dot(ue) * I));
        dAsvdu = taus * (be.transpose() * Me * (be.dot(ve) * ue + ce.dot(ve) * ve) + (be * ue.transpose() + ce * ve.transpose()) * Me * (be.dot(ve) * I));
        dAsvdv = taus * (ce.transpose() * Me * (be.dot(ve) * ue + ce.dot(ve) * ve) + (be * ue.transpose() + ce * ve.transpose()) * Me * (ce.dot(ve) * I + ue * be.transpose() + ve * ce.transpose()));

        Gs1=taus*(be*ue.transpose()+ce*ve.transpose())*Gx.transpose();
        Gs2=taus*(be*ue.transpose()+ce*ve.transpose())*Gy.transpose();
        dGs1pdu=taus*be.transpose()*Gx.transpose();///20241011 pe作ることこから

        add_matrix(Me, M, element, i);
        add_matrix(De, D, element, i);
        add_matrix(Cxe, Cx, element, i);
        add_matrix(Cye, Cy, element, i);
        add_matrix(Gxe, Gx, element, i);
        add_matrix(Gye, Gy, element, i);
        add_matrix(Ae, A, element, i);
        add_matrix(dAudue, dAudu, element, i);
        add_matrix(dAudve, dAudv, element, i);
        add_matrix(dAvdue, dAvdu, element, i);
        add_matrix(dAvdve, dAvdv, element, i);
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

        Ae = Me * (ue * be.transpose() + ve * ce.transpose());
        dAudue = be.dot(ue) * Me + Ae;
        dAudve = ce.dot(ue) * Me;
        dAvdue = be.dot(ve) * Me;
        dAvdve = ce.dot(ve) * Me + Ae;

        add_matrix(Ae, A, element, i);
        add_matrix(dAudue, dAudu, element, i);
        add_matrix(dAudve, dAudv, element, i);
        add_matrix(dAvdue, dAvdu, element, i);
        add_matrix(dAvdve, dAvdv, element, i);
        // add_vector(Axe, Ax, element, i);
        // add_vector(Axe, Ax, element, i);
    }

    P = rou * M * u / DT + rou * A * u - Gx * p + myu * D * u - rou * M * u_before / DT;
    Q = rou * M * v / DT + rou * A * v - Gy * p + myu * D * v - rou * M * v_before / DT;
    R = Cx * u + Cy * v;

    dPdu = rou * M / DT + rou * dAudu + myu * D;
    dPdv = rou * dAudv;
    dPdp = -Gx;
    dQdu = rou * dAvdu;
    dQdv = rou * M / DT + rou * dAvdv + myu * D;
    dQdp = -Gy;
    dRdu = Cx;
    dRdv = Cy;
    dRdp = MatrixXd::Zero(node.rows(), node.rows());
}

void set_LHS_RHS()
{

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