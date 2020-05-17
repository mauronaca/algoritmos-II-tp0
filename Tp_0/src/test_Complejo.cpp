//============================================================================
// Name        : Test Complejo Class
// Author      :
// Version     :
// Copyright   :
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>

#include "Complejo.h"
using namespace std;

int main() {


	Complejo Z1, Z2;
	Z2.setReal(2);
	Z2.setImag(2);

	Complejo Z3(5,5);
	Complejo Z4(1,1);
	Complejo Z5;

	Z3.printRect();

	Z4.printRect();

	Z5 = Z3*Z4;
	Z5.printRect();

	Z5 = Z3 + Z4;
	Z5.printRect();

	double a = 10;


	Z5 = Z4*(Z4 + Z2);
	Z5 = a*(2 +Z5 + 2)*100;
	Z5.printRect();


	Z1 = Z2 = Z4;
	Z1 = Z2 + Z3*Z3;

	Z1.printPolar();
}
