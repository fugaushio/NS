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
    get_parameter(filename1);
    get_geometry(filename2, filename3);
    set_0condition();

    timeforward();
    cout << "all finish" << endl;
    return 0;
}