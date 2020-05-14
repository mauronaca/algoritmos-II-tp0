//============================================================================
// Name        : Tp_0.cpp
// Author      :
// Version     :
// Copyright   : 
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "Images.h"
#include "Complejo.h"
using namespace std;

int main() {

	/*----------------------------------------*/
	/*-------- PERDON POR EL DESORDEN --------*/
	/*----------------------------------------*/
	
	Images imagen(10,10,15);
	int** matriz = imagen.getMatrix();
	Complejo Z1, Z2;
	Complejo Z3(5,5);
	Complejo Z4(1,1);
	double a = 10;

	Complejo Z5;
	Z2.setReal(2);
	Z2.setImag(2);

	Z5 = Z3*Z4;
	Z5.printRect();
	Z5 = Z3 + Z4;
	Z5.printRect();
	Z3.printRect();
	Z4.printRect();
	Z5 = Z4*(Z4 + Z2);
	Z5 = a*(2 +Z5 + 2)*100;
	Z5.printRect();

	Z1 = Z2 = Z4;
	Z1 = Z2 + Z3*Z3;

	Z1.printPolar();
	cout << matriz[1][1] << endl;

	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
	return 0;
}
