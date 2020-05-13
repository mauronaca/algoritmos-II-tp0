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

	cout << matriz[1][1] << endl;

	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
	return 0;
}
