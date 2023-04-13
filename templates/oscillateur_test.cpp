#include <iostream>
#include <vector>

#include "oscillateur.h"

using namespace std;

int main()
{
 //Test constructeur par Vector
 Oscillateur o({1,0,0},{0,0,0})
 
 // Test accesseurs
 cout << o.getp() << endl;
 cout << o.getp_prime << endl;
 
 //Test manipulateurs
 o.setp({1,0});
 o.setp_prime({2});
 
 //Test operator <<
 cout << o << endl;
 
 vector v1({1,1,1});
 vector v2({2,1,2});

 //Test consctructeur par vector
 Oscillateur o2(v1,v2);
 
 cout << o2 << endl;
 
 return 0
}
