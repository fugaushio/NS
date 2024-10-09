#include <iostream>
#include "src/calc.h"
#include "src/namelist.h"
#include "src/inputdata.h"

using namespace std;

int main(int argc, char *argv[])
{
    string filename1 = argv[1];
    string filename2 = argv[2];
    string filename3 = argv[3];
    string filename4 = argv[4];
    string filename5 = argv[5];
    string filename6 = argv[6];
    get_parameter(filename1);
    get_geometry(filename2, filename3);
    set_0condition();
    get_BCPoint(filename4,filename5,filename6);

    timeforward();
    cout << "all finish" << endl;
    return 0;
}