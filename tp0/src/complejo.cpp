#include "complejo.h"


Complejo::Complejo(){
	this->real = 0;
	this->imag = 0;
}
Complejo::Complejo(double x, double y){
	this->real = x;
	this->imag = y;
}
Complejo::Complejo(const Complejo& init){
	if(this != &init){ // Pregunto si ambas direcciones coinciden, el &init indica la direccion del objeto que pase por argumento
		this->real = init.real;
		this->imag = init.imag;
	}
}
Complejo::~Complejo(){
	this->real = 0;
	this->imag = 0;
}

double& Complejo::operator[] (double i){
	if(i == 1)
		return this->imag;
	else
		return this->real;
}
Complejo& Complejo::operator= (const Complejo& a){
	if(&a != this){
		this->real = a.real;
		this->imag = a.imag;

		return *this;
	}
	return *this;
}
Complejo Complejo::operator+ (const Complejo& a){
	Complejo aux;
 
	aux.real = this->real + a.real;
	aux.imag = this->imag + a.imag;

	return aux;
}
Complejo Complejo::operator+ (double a){
	Complejo aux;

	aux.real = this->real + a;

	return aux;
}
Complejo Complejo::producto(Complejo& z){
	// Si no devuelvo por referencia no modifico al objeto que llama, pero no puedo hacer el producto encadenado
	Complejo aux;

	double a = this->real;
	double b = this->imag;
	double c = z.real;
	double d = z.imag;
	// (ac - bd)+i(ad + bc)

	aux.real = a*c - b*d;
	aux.imag = a*d + b*c;

	return aux;
}
double Complejo::getModulo(){
	return sqrt((pow(this->real,2) + pow(this->imag,2)));
}

double Complejo::getReal(){
	return this->real;
}

double Complejo::getImag(){
	return this->imag;
}


double Complejo::setReal(double x){
	this->real = x;
	return this->real;
}


double Complejo::setImag(double x){
	this->imag = x;
	return this->imag;
}

void Complejo::print(){
	std::cout << floor(this->real);
	if(this->imag < 0)
		std::cout << floor(this->imag) << "i" << std::endl;
	else{
		std::cout << "+";
		std::cout << std::setprecision(2) << floor(this->imag) << "i" << std::endl;
	}
}

