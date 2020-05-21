//============================================================================
// Name        : Tp_0.cpp
// Author      : Nacachian, Urquiza, Vera
// Version     :
// Copyright   : 
// Description : Trabajo PrÃ¡ctico NÂ° 0
//============================================================================

#include <iostream>
#include "cmdline.h"
#include "Images.h"
#include "Complejo.h"
#include "ComplexPlane.h"
#include "ComplexTransform.h"

using namespace std;


/*=====================================================================================*/
// 									ELEMENTOS GLOBALES 
/*=====================================================================================*/

// Opciones del programa (usando la libreria cmdline que proporcionaron en la practica): 

static void opt_input(string const &);
static void opt_output(string const &);
static void opt_function(string const &);
static void opt_help(string const &);
void multiply(istream *is, ostream *os);


static option_t options[] = {
	{1, "i", "input", "-", opt_input, OPT_DEFAULT},
	{1, "o", "output", "-", opt_output, OPT_DEFAULT},
	{1, "f", "function", NULL, opt_function, OPT_MANDATORY},
	{0, "h", "help", NULL, opt_help, OPT_DEFAULT},
	{0, },
};



// Funciones 
//
//typedef enum token_functions {EXPZ, Z}; //, COSZ, SINZ };
const string functions[] = {"exp(z)", "z"}; //, "cos(z)", "sin(z)" };

static istream* iss = 0;
static ostream* oss = 0;
static fstream ifs;
static fstream ofs;

#define ECLIPSE_BUILD
//#define CONSOLDE_BUILD

#ifdef ECLIPSE_BUILD
	#define INPUT_IMAGE_PATH "Debug/utils/dragon.ascii.pgm"
	#define OUTPUT_IMAGE_PATH "Debug/utils/fusible.pgm"
#endif
#ifdef CONSOLDE_BUILD
	#define INPUT_IMAGE_PATH "utils/dragon.ascii.pgm"
	#define OUTPUT_IMAGE_PATH "utils/fusible.pgm"
#endif


/*====================================================================================*/



int main(int argc, char * const argv[]) {

	/*----------------------------------------*/
	/*-------------- Pruebas -----------------*/
	/*----------------------------------------*/
	
	cmdline cmdl(options);	// Objeto con parametro tipo option_t (struct) declarado globalmente. Ver línea 51 main.cc
	cmdl.parse(argc, argv); // Metodo de parseo de la clase cmdline

//	ifs.open(INPUT_IMAGE_PATH, ios::in);
//	ofs.open(OUTPUT_IMAGE_PATH, ios::out);
//	oss = &ofs;
//	iss = &ifs;
//
//	string stest;
//
//	if(!iss->good()){
//		cout << "1-" << endl;
//		cout << "Fallo al abrir el archivo" << endl;
//		exit(1);
//	}


	Images origen(10,10,15); //NO BORRAR
	origen.loadFile(iss); //NO BORRAR

	int ancho = origen.getWidth(); //NO BORRAR
	int altura = origen.getHeight(); //NO BORRAR

	cout << "Datos origen:" << endl;
	cout << "Ancho: " << ancho << " Altura: " << altura << " Maximo brillo: " << origen.getMaxInt() << endl;
	//cout << origen[1][1] << endl;
	cout << endl;

	//origen.printColours();
	Images destino(origen); //NO BORRAR
	Complejo aux(0,0);
	

	/*TEST DE COMPLEXPLANE Y COMPLEXTRANSFORM*/

	ComplexPlane plano(origen);
	ComplexTransform transformada;

	for(int i = 0; i < altura; i++){
		for(int j = 0; j < ancho; j++){

			plano.index2Comp(i, j); //guarda la coordenada en forma de num complejo
			aux = plano.getComp();

			transformada.fun(aux); //calcula la anti transformada
			aux = transformada.getOutput();
			 
			plano.comp2Index(aux); //guarda los indices del pixel del origen
			
			if(plano.getRow() < 0 || plano.getCol() < 0)
				destino[i][j]=0; //guarda vacÃ­o
			else
				destino[i][j]=origen[plano.getRow()][plano.getCol()]; //guarda el pixel
				
		}
	}

	//origen.printColours();
	//destino.printColours();
	destino.saveFile(oss);
	ifs.close();
	ofs.close();

	return 0;
}

/********** Funciones invocadas por CMDLINE ******************************/

static void
opt_input(string const &arg)
{
	cout<<"La direccion del archivo Origen es :"<< arg.c_str() <<endl;
	// Si el nombre del archivos es "-", usaremos la entrada
	// estándar. De lo contrario, abrimos un archivo en modo
	// de lectura.
	//
	if (arg == "-") {
		iss = &cin;		// Establezco la entrada estandar cin como flujo de entrada
	}
	else {
		ifs.open(arg.c_str(), ios::in); // c_str(): Returns a pointer to an array that contains a null-terminated
										// sequence of characters (i.e., a C-string) representing
										// the current value of the string object.
		iss = &ifs;
	}

	// Verificamos que el stream este OK.
	//
	if (!iss->good()) {
		cerr << "cannot open "
		     << arg
		     << "."
		     << endl;
		exit(1);
	}
}

static void
opt_output(string const &arg)
{
	cout<< "La direccion del archivo Destino es :"<< arg.c_str() <<endl;
	// Si el nombre del archivos es "-", usaremos la salida
	// estándar. De lo contrario, abrimos un archivo en modo
	// de escritura.
	//
	if (arg == "-") {
		oss = &cout;	// Establezco la salida estandar cout como flujo de salida
	} else {
		ofs.open(arg.c_str(), ios::out);
		oss = &ofs;
	}

	// Verificamos que el stream este OK.
	//
	if (!oss->good()) {
		cerr << "cannot open "
		     << arg
		     << "."
		     << endl;
		exit(1);		// EXIT: Terminación del programa en su totalidad
	}
}

static void
opt_function(string const &arg)
{
	istringstream iss(arg);
	cout<< "El La transformacion elegida es f(z)= " <<arg.c_str() <<endl;

	// Intentamos extraer el factor de la línea de comandos.
	// Para detectar argumentos que únicamente consistan de
	// números enteros, vamos a verificar que EOF llegue justo
	// después de la lectura exitosa del escalar.
	//
	string option;
	iss >> option;

	if (iss.bad()) {
		cerr << "cannot read integer factor."
			 << endl;
		exit(1);
	}


	if( option.compare("z") == 0){
		ComplexTransform::setOption(1);
		//cout<< "Testpoint 1" <<endl;
	}else if( option.compare("exp(z)") ==0 ){
		ComplexTransform::setOption(2);
		//cout<< "Testpoint 2" <<endl;
	}else{
		cerr << option <<" No es un parametro Valido "<< endl;
		exit(1);
	}

}

static void
opt_help(string const &arg)
{
	cout << "cmdline [-f function] [-i file] [-o file]"
	     << endl;
	exit(0);
}

