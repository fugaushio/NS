#include <iostream>
#include "src/calc.h"
#include "src/namelist.h"
#include "src/inputdata.h"

using namespace std;

int main()
{
    get_parameter();
    //get_geometry();
    //set_0condition();

    //timeforward();
    cout << "all finish" << endl;
    return 0;
}