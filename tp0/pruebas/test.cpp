// Prueba de la clase cmdline

#include <iostream>
#include <fstream>
#include <string.h>
#include <cmdline.h>
#include <sstream>
#include <cstdlib>
#include <iomanip>

using namespace std;

// Clase para el programa:
//
class data{
private:
	string s;
	static const string reserv[2];
	bool flag;
public:
	data(string sinit){
		this->s = sinit;
		if(sinit != reserv[0] || sinit != reserv[1])
			flag = false;
		else
			flag = true;
	}
	data(){ this->s = reserv[0]; }
	~data();
	bool ok(){
		return flag;
	}
};

// Funciones asiociadas a cada opcion de argumentos por cmdline. 
// Indican las instrucciones para extraer cada argumento
// Seran manipuladas por la estructura de option_t.
//
static void opt_inputf(string const &); 
//static void opt_outputf(string const &);
static void opt_indata(string const &);

/*---------------------------------------------------------*/
/*-------------------- Elementos Globales -----------------*/
/*---------------------------------------------------------*/

const char* def_val = "-"; // Caracter de defecto para los argumentos de cmdline 

// Variable que sera extraida de la linea de comandos (esto es del programa en si, independiente de la libreria cmdline).
//
static string data; 

// Declaro todas los argumentos que tendra el programa
//
static option_t options[] = {
	{1, "i", "input", def_val, opt_inputf, OPT_DEFAULT},
	{1, "s", "string", NULL, opt_indata, OPT_MANDATORY},
	//{1, "o", "output", def_val, opt_outputf, OPT_DEFAULT},
	{0, } // Eso es necesario, si no la clase cmdline se rompe.
};

static istream* iss = 0;// Objeto que maneja el flujo de entrada (por defecto se usa std::cin, el de la linea de comando)
static ostream* oss = 0;// Objeto que maneja el flujo de salida de datos (por defecto seria std::cout)
static fstream ifs;		// Para manejar archivos. Declaro un objeto de entrada de datos   
static fstream ofs;		// Declaro un objeto de salida de datos.

// Inicializo las palabras reservadas de la clase data.
const string data::reserv[2]= {
		"hola mundo!", 
		"hello world!"
	};

/*---------------------------------------------------------*/
/*------------------------ Funciones ----------------------*/
/*---------------------------------------------------------*/

static void opt_inputf(string const & arg){
	
	// Se verifica si el argumento pasado es por defecto:
	//
	if(arg == def_val){
		iss = &cin;
	}
	else{
		ifs.open(arg.c_str(), ios::in); // Abrir archivo de input pasado por argumento.
		iss = &ifs; 				// Ahora digo que el flujo de entrada es el archivo de input.
	}

	// Se verifica si se pudo abrir el archivo, o si hubo algun problema en el istream:
	//
	if(!iss->good()){
		cerr 
			<< "no se pudo abrir " 
			<< arg << "."
			<< endl;
		exit(1);
	} 
	if(iss != &cin){
		cout 
			<< "se ha abierto el archivo "
			<< arg << "."
			<< endl;
	}
}

static void opt_indata(string const & arg){
	// Funcion para extraer el dato pasado por argumento 
	// 
	//	

	istringstream iss(arg);

	iss >> data;

	if(iss.bad()){
		cerr 
		<< "no se pudo leer" 
		<< arg << "." 
		<< endl;
		exit(1);
 	}


}

/*---------------------------------------------------------*/
/*------------------------- Main --------------------------*/
/*---------------------------------------------------------*/

int main(int argc, char* const argv[]){
	cout << "bienvenuti" << endl;

	cmdline cmdl(options);
	cmdl.parse(argc, argv);
	
	cout << data << endl;
	cout << "hasta luego!" << endl;
}


















