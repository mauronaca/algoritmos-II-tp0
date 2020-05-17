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


#define INPUT_IMAGE_PATH "Debug/utils/dragon.ascii.pgm"
#define OUTPUT_IMAGE_PATH "Debug/utils/fusible.pgm"

int main() {

	/*----------------------------------------*/
	/*-------------- Pruebas -----------------*/
	/*----------------------------------------*/
	
	ifs.open(INPUT_IMAGE_PATH, ios::in);
	ofs.open(OUTPUT_IMAGE_PATH, ios::out);
	oss = &ofs;
	iss = &ifs;

	string stest;

	if(!iss->good()){
		cout << "1-" << endl;
		cout << "Fallo al abrir el archivo" << endl;
		exit(1);
	}

	Images imagen(10,10,15);
	Images imagenDefault;
	imagen.loadFile(iss);

	cout << "Datos imagen:" << endl;
	cout << "Ancho: " << imagen.getWidth() << " Altura: " << imagen.getHeight() << " Maximo brillo: " << imagen.getMaxInt() << endl;
	cout << imagen[1][1] << endl;
	cout << endl;

	//imagen.printColours();
	//imagenDefault.printColours();
	//imagen.saveFile(oss);

	ifs.close();
	ofs.close();

	return 0;
}
