
#include <iostream>

#include "iosymkit.h"
#include "svector.h"

using namespace std;

int main()
{
    //Test constructeur par initializer_list
    SVector<3> v = {0, 1, 2};

    cout << "Second access" << endl;

    //Test operator []
    double x = v[0];
    cout << "x set" << endl;
    double y = v[1];
    cout << "y set" << endl;
    double z = v[2];
    cout << "z set" << endl;

    cout << "here" << endl;

    //Test operator <<
    cout << v << endl;

    SVector<3> w = {5, 6, 7};

    cout << w << endl;

    // Test operator ^
    SVector<3> res = v ^ w;

    cout << res << endl;
}
