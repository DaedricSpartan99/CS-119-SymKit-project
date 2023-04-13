
#include <iostream>

#include "vector.h"
#include "iosymkit.h"

using namespace std;

int main()
{

    // Test constructeur par initializer list
    Vector v = {0, 1, 2};

    //Test operator []
    double x = v[0];
    cout << "x set" << endl;
    double y = v[1];
    cout << "y set" << endl;
    double z = v[2];
    cout << "z set" << endl;

    cout << "here we have" << endl;

    //Test operator <<
    cout << v << endl;

    Vector w {5, 6, 7};

    //Test operateurs * / + -
    cout << (w*3) << endl;

    cout << (v/2) << endl;

    cout << (v*w) << endl;

    cout << (v+w) << endl;

    cout << (v-w) << endl;

    Vector v1 = {1};

    // Test somme entre vecteurs de dimension differente
    cout << (v+v1) << endl;
    cout << (v1+v) << endl;

    // Test operator ^
    Vector res = v ^ w;

    cout << res << endl;
    
    // Test operator !=
    if( v != w )
		cout << "ouiii" << endl; 
    else
		cout << "nooon" << endl;

    // Test operateur de copie
    Vector v1(v);
	
    // Test operateur ==
    if( v == v1 )
        cout << "ouiii" << endl;
    else
        cout << "nooon" << endl;

}
