//============================================================================
// Name        : Tp_0.cpp
// Author      : Nacachian, Urquiza, Vera
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


/*=====================================================================================*/
// 									ELEMENTOS GLOBALES 
/*=====================================================================================*/

// Opciones del programa (usando la libreria cmdline que proporcionaron en la practica): 
//
/* Hasta no definir las funciones opt_ 
static option_t options[] = {
	{1, "i", "input", "-", opt_input, OPT_DEFAULT},
	{1, "o", "output", "-", opt_output, OPT_DEFAULT},
	{1, "f", "function", NULL, opt_factor, OPT_MANDATORY},
	{0, "h", "help", NULL, opt_help, OPT_DEFAULT},
	{0, },
};*/

// Funciones 
//
typedef enum token_functions {EXPZ, Z}; //, COSZ, SINZ };
const string functions[] = {"exp(z)", "z"}; //, "cos(z)", "sin(z)" };

static istream* iss = 0;
static ostream* oss = 0;
static fstream ifs;
static fstream ofs;


/*====================================================================================*/



int main() {

	/*----------------------------------------*/
	/*-------------- Pruebas -----------------*/
	/*----------------------------------------*/
	
	ifs.open("utils/test1.pgm", ios::in);
	ofs.open("utils/fusible.pgm", ios::out);
	oss = &ofs;
	iss = &ifs;

	string stest;

	if(!iss->good()){
		cout << "1-" << endl;
		cout << "Fallo al abrir el archivo" << endl;
		exit(1);
	}


	Images origen(10,10,15); //NO BORRAR
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
	ComplexTransform transformada(1);

	for(int i = 0; i < altura; i++){
		for(int j = 0; j < ancho; j++){

			plano.index2Comp(i, j); //guarda la coordenada en forma de num complejo
			aux = plano.getComp();

			transformada.fun(aux); //calcula la anti transformada
			aux = transformada.getOutput();
			 
			plano.comp2Index(aux); //guarda los indices del pixel del origen
			
			if(plano.getRow() < 0 || plano.getCol() < 0)
				destino[i][j]=0; //guarda vacío
			else
				destino[i][j]=origen[plano.getRow()][plano.getCol()]; //guarda el pixel
				
		}
	}

	destino.saveFile(oss);
	ifs.close();
	ofs.close();

	return 0;
}
