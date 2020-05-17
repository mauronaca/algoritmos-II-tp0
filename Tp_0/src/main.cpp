//============================================================================
// Name        : Tp_0.cpp
// Author      : Nacacchian, Urquiza, Vera
// Version     :
// Copyright   : 
// Description : Trabajo Práctico N° 0
//============================================================================

#include <iostream>
#include "Images.h"
#include "Complejo.h"
#include "ComplexPlane.h"
#include "ComplexTransform.h"
using namespace std;

static istream* iss = 0;
static ostream* oss = 0;
static fstream ifs;
static fstream ofs;

int main() {

	/*----------------------------------------*/
	/*-------------- Pruebas -----------------*/
	/*----------------------------------------*/
	
	ifs.open("utils/marcie.ascii.pgm", ios::in);
	ofs.open("utils/fusible.pgm", ios::out);
	oss = &ofs;
	iss = &ifs;

	string stest;

	if(!iss->good()){
		cout << "1-" << endl;
		cout << "Fallo al abrir el archivo" << endl;
		exit(1);
	}


	Images origen; //NO BORRAR
	origen.loadFile(iss); //NO BORRAR

	int ancho = origen.getWidth(); //NO BORRAR
	int altura = origen.getHeight(); //NO BORRAR

	cout << "Datos origen:" << endl;
	cout << "Ancho: " << ancho << " Altura: " << altura << " Maximo brillo: " << origen.getMaxInt() << endl;
	cout << origen[1][1] << endl;
	cout << endl;

	//origen.printColours();
	Images destino(origen); //NO BORRAR
	Complejo aux(0,0);
	

	/*TEST DE COMPLEXPLANE Y COMPLEXTRANSFORM*/

	ComplexPlane plano(origen);
	ComplexTransform transformada(2);

	for(int i = 0; i < altura; i++){
		for(int j = 0; j < ancho; j++){
			plano.index2Comp(i, j); //guarda la coordenada en forma de num complejo
			aux = plano.getComp();

			transformada.fun(aux); //calcula la salida
			aux = transformada.getOutput();
			 
			plano.comp2Index(aux); //guarda los indices del pixel del origen
			
			if(plano.getRow() >= 0 && plano.getCol() >= 0)
				destino[i][j]=origen[plano.getRow()][plano.getCol()]; //guarda el pixel
			else 
				destino[i][j]=0; //guarda vacío
		}
	}

	destino.saveFile(oss);
	ifs.close();
	ofs.close();

	return 0;
}
