#include <sstream>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <complejo.h>

class image{

private:
	
	int ** valMat;
	Complejo ** zMat;
	int largo;
	int ancho;

public:

	//defecto
	//
	image();

	// Constructor al cual se le pasa el archivo
	//
	image(istream *);

	// Constructor copia
	//
 	image(const image &);

	// DEstructor
	//
	~image();

	// Operador = . A la derecha recibe un objeto constante, y ademas lo devuelve por referencia. 
	//
	const image & operator=(const image &);
	
	// Metodo para transformar. Recibe como parametro el archivo de salida, y la funcion para transformar
	//
	image transform(ostream *, string &);

	// Metodo para guardar la imagen en otro archivo de salida (?) REtorna el mismo objeto
	//
	const image & save(ostream *); 
};