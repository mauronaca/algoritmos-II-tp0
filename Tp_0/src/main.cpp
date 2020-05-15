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

static istream* iss = 0;
static ostream* oss = 0;
static fstream ifs;
static fstream ofs;

int main() {

	/*----------------------------------------*/
	/*-------------- Pruebas -----------------*/
	/*----------------------------------------*/
	
	ifs.open("utils/dragon.ascii.pgm", ios::in);
	ofs.open("utils/fusible.pgm", ios::out);
	oss = &ofs;
	iss = &ifs;

	string stest;

	if(!iss->good()){
		cout << "1-" << endl;
		cout << "Fallo al abrir el archivo" << endl;
		exit(1);
	}


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

	Images imagen(10,10,15);
	Images imagenDefault;
	imagen.loadFile(iss);

	cout << "Datos imagen:" << endl;
	cout << "Ancho: " << imagen.getWidth() << " Altura: " << imagen.getHeight() << " Maximo brillo: " << imagen.getMaxInt() << endl;
	cout << imagen[1][1] << endl;
	cout << endl;

	imagen.printColours();
	//imagenDefault.printColours();
	imagen.saveFile(oss);

	ifs.close();
	ofs.close();

	return 0;
}
