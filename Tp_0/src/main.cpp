//============================================================================
// Name        : main.cpp
// Author      : Nacachian, Urquiza, Vera
// Version     : 1.1.1
// Description : Trabajo Práctico Nro. 0
//============================================================================


#include <iostream>
#include <string>
#include <cstdio>
#include <algorithm>
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
static bool openOutputFile();


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

static bool inputFileIsPGM = true;

static string outputFileName;


/*====================================================================================*/
//									MAIN
/*====================================================================================*/


int main(int argc, char * const argv[]){

	//------Valido Argumentos ------//
	cmdline cmdl(options);
	cmdl.parse(argc, argv);


	//------		Valido si la imagen es PGM 			 ------//
	//------Se abre en funcion si el archivo es PGM o no ------//
	if(!openOutputFile())
		return 1;

	//------Creo Imagenes de origen y destino ------//
	Images origen;

	std::cout << "Procesando imagen..." << std::endl;	
	if(iss == &cin)
		std::cout << "Ingrese la imagen por consola:" << std::endl;

	//------Cargo la imagen de entrada ------//
	if(!origen.loadFile(iss)){

		// Si en el proceso hubo algun error inesperado (ie. la entrada es cin, la salida es un archivo
		// y lo que se ingresa no es tipo pgm)
		//
		if(oss != &cout)
			std::remove(outputFileName.c_str());
		
		ifs.close();
		ofs.close();
			
		return 1;

	} else {

		Images destino(origen);

		//------Trasnformo y guardo ------//
		transformar_imagen(origen,destino);

		std::cout << "Guardando imagen..." << std::endl;
		destino.saveFile(oss);

	}

	ifs.close();
	ofs.close();

	std::cout << "La transformacion fue exitosa." << std::endl;

	return 0;
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
			//guarda la coordenada en forma de num complejo
			plano.index2Comp(i, j); 
			z_aux = plano.getComp();

			//calcula la anti transformada
			transformada.fun(z_aux);
			z_aux = transformada.getOutput();

			//guarda los indices del pixel del origen
			plano.comp2Index(z_aux);

			//guarda vacío si algun subindice es negativo; caso contrario, guarda el pixel
			if(plano.getRow() < 0 || plano.getCol() < 0)
				destino(i,j)=0; 
			else
				destino(i,j) = origen(plano.getRow(),plano.getCol());

		}
	}

	return;
}

//------------------ Callbacks de CMDLINE ------------------------------//

static void
opt_input(string const &arg)
{
	// Si el nombre del archivos es "-", usaremos la entrada
	// est?dar. De lo contrario, abrimos un archivo en modo
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


	// ============================================================================================================= //
	//				Chequeo si el archivo de entrada contiene la linea P2, o sea si es formato PGM
	// ============================================================================================================= //

	if(iss != &cin){
		string line;
		string auxMagicNUmber;

		while(getline(*iss, line)){

			stringstream ss(line);

			// Chequea si en la linea a leer existe el caracter #. En caso de que exista corta el proceso.
			//
			size_t npos = string::npos;
			if (ss.str().find('#') != npos){
				inputFileIsPGM = false;
				continue;
			}

			auxMagicNUmber = ss.str();

			// Elimina el \n o \r que en algunos .pgm aparece
			//
			for (size_t i = 0; i < auxMagicNUmber.length(); i++){
			    if (		auxMagicNUmber.c_str()[i] == '\r'
			    		|| 	auxMagicNUmber.c_str()[i] == '\n'){
			    	

			    	auxMagicNUmber = auxMagicNUmber.substr(0, i);
			    }

			}

			// Borrar cualquier espacio en blanco del string que almacena P2
			//
			std::string::iterator end_pos = std::remove(auxMagicNUmber.begin(), auxMagicNUmber.end(), ' ');
			auxMagicNUmber.erase(end_pos, auxMagicNUmber.end());

			// Si no es P2, la funcion devuelve falso. Y en ese caso debera cortar la carga del archivo ya que no estamos
			// interesados en otro tipo de formato.
			//
			if( auxMagicNUmber.compare("P2") != 0 ){
				inputFileIsPGM = false;
			} else {
				inputFileIsPGM = true;
			}
			break;


		}
	}


	// ============================================================================================================= //

	// Verificamos que el stream este OK.
	//
	if (!iss->good()) {
		cerr << "cannot open "
			 << arg
			 << "."
			 << endl;
		ifs.close();
		exit(1);
	}


}

static void
opt_output(string const &arg)
{

	// Si el nombre del archivos es "-", usaremos la salida
	// est?dar. De lo contrario, abrimos un archivo en modo
	// de escritura.
	//
	if (arg == "-") {
		oss = &cout;	// Establezco la salida estandar cout como flujo de salida
		cout<< "La direccion del archivo Destino es: Cout (Salida Standar)" << endl;
	} else {
		outputFileName = arg.c_str();
		
		//ofs.open(arg.c_str(), ios::out);
		//oss = &ofs;
		cout<< "La direccion del archivo Destino es: "<< arg.c_str() <<endl;
	}


}

static void
opt_function(string const &arg)
{
	istringstream iss(arg);
	cout<< "La transformacion elegida es f(z)= " <<arg.c_str() <<endl;

	// Intentamos extraer el factor de la l?ea de comandos.
	// Para detectar argumentos que ?nicamente consistan de
	// n?meros enteros, vamos a verificar que EOF llegue justo
	// despu? de la lectura exitosa del escalar.
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

static bool
openOutputFile(){

	if(!inputFileIsPGM){

		ifs.close();
		cout << "El archivo de entrada no tiene formato PGM" << endl;
		return false;
	}

	else {

		if(oss != &cout){
			ofs.open(outputFileName.c_str(), ios::out);
			oss = &ofs;	
		}
		
		// Verificamos que el stream este OK.
		//
		if (!oss->good()) {
			cerr << "cannot open "
		     	<< outputFileName
		     	<< "."
		     	<< endl;

		     ifs.close();
			return false;

		}

		return true;
	}

	//return true;

}