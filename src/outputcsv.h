#pragma once
#include <iostream>
#include <fstream>
#include <eigen3/Eigen/Core>
#include <eigen3/Eigen/Dense>

using namespace std;
using namespace Eigen;

void outputfile(MatrixXd node, MatrixXd flow, VectorXd p, MatrixXi element, int timestep)
{
    int points = node.rows();
    int cells = element.rows();
    int n_gons = element.cols();
    int type;
    if (n_gons == 4)
        type = 9;
    else if (n_gons == 3)
        type = 5;
    char filename[32];
    sprintf(filename, "data_%d.vtu", timestep);

    ofstream ofs(filename);

    if (!ofs)
    {
        cout << "can not open file" << endl;
        return;
    }

    ofs << "<VTKFile type='UnstructuredGrid' version='1.0' byte_order='LittleEndian' header_type='UInt64'>" << endl
        << "<UnstructuredGrid>" << endl;
    ofs << "<Piece NumberOfPoints= '" << points << "' NumberOfCells = '" << cells << "' > " << endl;
    // points
    ofs << "<Points>" << endl
        << "<DataArray type='Float64' Name='Points' NumberOfComponents='3' format='ascii'>" << endl;

    for (int i = 0; i < points; i++)
    {
        ofs << node(i, 0) << " " << node(i, 1) << " " << node(i, 2) << endl;
    }

    ofs << "</DataArray>" << endl
        << "</Points>" << endl;
    // pointsdata
    ofs << "<PointData>" << endl;
    // flow
    ofs << "<DataArray type='Float64' Name='flow' NumberOfComponents='3' format='ascii'>" << endl;

    for (int i = 0; i < points; i++)
    {
        ofs << flow(i, 0) << " " << flow(i, 1) << " " << flow(i, 2) << endl;
    }
    ofs << "</DataArray>" << endl;
    // pressure
    ofs << "<DataArray type='Float64' Name='pressure' NumberOfComponents='3' format='ascii'>" << endl;

    for (int i = 0; i < points; i++)
    {
        ofs << p(i) << " " << 0 << " " << 0 << endl;
    }

    ofs << "</DataArray>" << endl;
    ofs << "</PointData>" << endl;

    // cells
    ofs << "<Cells>" << endl
        << "<DataArray type='Int32' Name='connectivity' format='ascii'>" << endl;
    for (int i = 0; i < cells; i++)
    {
        for (int j = 0; j < n_gons; j++)
        {
            ofs << element(i, j) << " ";
        }
        ofs << endl;
    }
    ofs << "</DataArray>" << endl;
    ofs << "<DataArray type='Int32' Name='offsets' format='ascii'>" << endl;
    for (int i = 0; i < cells; i++)
        ofs << n_gons * (i + 1) << " ";

    ofs << endl
        << "</DataArray>" << endl;
    ofs << "<DataArray type='UInt8' Name='types' format='ascii'>" << endl;
    for (int i = 0; i < cells; i++)
        ofs << type << " ";
    ofs << endl
        << "</DataArray>" << endl;

    ofs << "</Cells>" << endl
        << "</Piece>" << endl
        << "</UnstructuredGrid>" << endl
        << "</VTKFile>";
}