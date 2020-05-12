
#ifndef _COMPLEJO_INCLUDE
#define _COMPLEJO_INCLUDE

#include <iostream>
#include <math.h>
#include <iomanip>      // std::setprecision
#include <string.h>

class Complejo{
private:
	double real;
	double imag;

public:
	// Constructores:
	Complejo();
	Complejo(double x, double y);
	Complejo(const Complejo& init); // Para asginar

	// Destructor
	~Complejo();

	// Operadores
	double& operator[] (double index); // Retornar por referencia permite la modificacion del objeto.
	Complejo& operator= (const Complejo& a); // b = a . Retornar referencia quiere decir que el objeto puede ser modificado.
	Complejo operator+ (const Complejo& a); // b + a
	Complejo operator+ (double x);// RE(b) + RE(x)
	Complejo producto(Complejo& b); // Devuelve el producto. POdria devolver referencia y multiplcar al mismo objeto, pero en este caso no
	bool operator== (const Complejo&); // b == a 
  
	// Metodos para obtener valores:
	double getModulo();
	double getReal();
	double getImag();
	double setReal(double x);
	double setImag(double x);
	void print();
};

#else
#endif
