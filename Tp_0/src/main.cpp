//============================================================================
// Name        : main.cpp
// Author      : Nacachian, Urquiza, Vera
// Version     : 1.1.1
// Description : Trabajo Practico N� 0
//============================================================================


#include <iostream>
#include "cmdline.h"
#include "Images.h"
#include "Complejo.h"
#include "ComplexPlane.h"
#include "ComplexTransform.h"

using namespace std;


/*=====================================================================================*/
// 									PROTOTIPOS
/*=====================================================================================*/


static void opt_input(string const &);
static void opt_output(string const &);
static void opt_function(string const &);
static void opt_help(string const &);
void transformar_imagen(const Images & origen, Images & destino);


/*=====================================================================================*/
// 								ELEMENTOS GLOBALES
/*=====================================================================================*/

static option_t options[] = {
	{1, "i", "input", "-", opt_input, OPT_DEFAULT},
	{1, "o", "output", "-", opt_output, OPT_DEFAULT},
	{1, "f", "function", NULL, opt_function, OPT_MANDATORY},
	{0, "h", "help", NULL, opt_help, OPT_DEFAULT},
	{0, },
};
//typedef enum token_functions {EXPZ, Z}; //, COSZ, SINZ };
const string functions[] = {"exp(z)", "z"}; //, "cos(z)", "sin(z)" };

static istream* iss = 0;
static ostream* oss = 0;
static fstream ifs;
static fstream ofs;


/*====================================================================================*/
//									MAIN
/*====================================================================================*/


int main(int argc, char * const argv[]){

	//------Valido Argumentos ------//
	cmdline cmdl(options);
	cmdl.parse(argc, argv);

	//------Creo Imagenes de origen y destino ------//
	Images origen;
	Images destino(origen);

	//------Trasnformo y guardo ------//
	origen.loadFile(iss);
	transformar_imagen(origen,destino);
	destino.saveFile(oss);

	if(iss != &cin)
		ifs.close();
	if(oss != &cout)
		ofs.close();

	exit(0);
}




/*====================================================================================*/
// 						FUNCIONES INVOCADAS EN EL MAIN
/*====================================================================================*/


void transformar_imagen(const Images & origen, Images & destino){

	if(&origen == &destino)
		return;

	Complejo z_aux(0,0);
	ComplexPlane plano(origen);
	ComplexTransform transformada;

	int ancho = origen.getWidth();
	int altura = origen.getHeight();


	for(int i = 0; i < altura; i++){
		for(int j = 0; j < ancho; j++){

			plano.index2Comp(i, j); //guarda la coordenada en forma de num complejo
			z_aux = plano.getComp();

			transformada.fun(z_aux); //calcula la anti transformada
			z_aux = transformada.getOutput();

			plano.comp2Index(z_aux); //guarda los indices del pixel del origen

			if(plano.getRow() < 0 || plano.getCol() < 0)
				destino(i,j)=0; //guarda vacío
			else
				destino(i,j) = origen(plano.getRow(),plano.getCol()); //guarda el pixel

		}
	}

	return;
}

//------------------ Callbacks de CMDLINE ------------------------------//

static void
opt_input(string const &arg)
{
	// Si el nombre del archivos es "-", usaremos la entrada
	// est�ndar. De lo contrario, abrimos un archivo en modo
	// de lectura.
	//
	if (arg == "-") {
		iss = &cin;		// Establezco la entrada estandar cin como flujo de entrada
		cout<<"La direccion del archivo Origen es : Cin (Entrada Standar)" <<endl;

	}
	else {
		ifs.open(arg.c_str(), ios::in); // c_str(): Returns a pointer to an array that contains a null-terminated
										// sequence of characters (i.e., a C-string) representing
										// the current value of the string object.
		iss = &ifs;
		cout<<"La direccion del archivo Origen es :"<< arg.c_str() <<endl;

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

	// Si el nombre del archivos es "-", usaremos la salida
	// est�ndar. De lo contrario, abrimos un archivo en modo
	// de escritura.
	//
	if (arg == "-") {
		oss = &cout;	// Establezco la salida estandar cout como flujo de salida
		cout<< "La direccion del archivo Destino es: Cout (Salida Standar)" << endl;
	} else {
		ofs.open(arg.c_str(), ios::out);
		oss = &ofs;
		cout<< "La direccion del archivo Destino es: "<< arg.c_str() <<endl;
	}

	// Verificamos que el stream este OK.
	//
	if (!oss->good()) {
		cerr << "cannot open "
		     << arg
		     << "."
		     << endl;
		exit(1);		// EXIT: Terminaci�n del programa en su totalidad
	}
}

static void
opt_function(string const &arg)
{
	istringstream iss(arg);
	cout<< "La transformacion elegida es f(z)= " <<arg.c_str() <<endl;

	// Intentamos extraer el factor de la l�nea de comandos.
	// Para detectar argumentos que �nicamente consistan de
	// n�meros enteros, vamos a verificar que EOF llegue justo
	// despu�s de la lectura exitosa del escalar.
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

