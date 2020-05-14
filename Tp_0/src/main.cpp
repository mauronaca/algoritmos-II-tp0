//============================================================================
// Name        : Tp_0.cpp
// Author      :
// Version     :
// Copyright   : 
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "Images.h"
using namespace std;

int main() {
	Images imagen(10,10,15);
	int** matriz = imagen.getMatrix();
	Complejo Z1, Z2;
	Complejo Z3 = (2,3);
	Complejo Z4(1,0);

	Z1 = Z2 = Z4;
	Z1 = Z2 + Z3*Z3; 
	Z1.printPolar();
	cout << matriz[1][1] << endl;

	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
	return 0;
}
