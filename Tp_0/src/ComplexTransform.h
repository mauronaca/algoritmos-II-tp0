#ifndef COMPLEXTRANSFORM_H_
#define COMPLEXTRANSFORM_H_

#include "Complejo.h"

class ComplexTransform{
private:
	Complejo input;
	Complejo output;
	int option; //1: z ; 2: exp(z) ;3 rotar; en otro caso: z

public:
	ComplexTransform(); //constructor
	ComplexTransform(int ); //con parámetros
	~ComplexTransform(); //destructor

	void fun(Complejo &);

	Complejo getInput();
	Complejo getOutput();


};

#endif
