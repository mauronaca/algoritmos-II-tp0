#include "ComplexPlane.h"

ComplexPlane::ComplexPlane(){
	row = col = 0;
	this->comp.setReal(0);
	this->comp.setImag(0);
}

ComplexPlane::ComplexPlane(Images & original){
	row = col = 0;
	this->image = original;
	this->comp.setReal(0);
	this->comp.setImag(0);
}

ComplexPlane::~ComplexPlane(){
	this->image.~Images();
	this->comp.~Complejo();
	row = col = 0;
}

ComplexPlane::ComplexPlane(const ComplexPlane & init){
	comp = init.getComp();
	image = init.getImage();
	row = init.getRow();
	col = init.getCol();
}

ComplexPlane& ComplexPlane::operator=(const ComplexPlane & right){
	comp = right.getComp();
	image = right.getImage();
	row = right.getRow();
	col = right.getCol();
}

Complejo getComp(){
	return this->comp;
}

Images getImage(){
	return this->image;
}

int getRow(){
	return this->row;
}

int getCol(){
	return this->col;
}

//guarda en this->comp un número complejo correspondiente a la posición solicitada de la imagen.
void index2Comp(int row, int col){
	Complejo z(0,0);

	if(0 > r >= image.getHeight || 0 > c >= image.getWidth) //valor inválido
		this->comp = z;

	else
	{
		/* Se divide la matriz en cuatro regiones:
			se calcula el valor de la fila y columna "central" de la matriz.
			se reduce a un número entero puesto que, si se tiene una matriz cuadrada,
			no existirá un centro alcanzable. Pero igualmente se puede operar corriendo
			dicho centro un paso hacia atrás.
		*/
		int rowCentral = image.getHeight()/2;
		int colCentral = image.getWidth()/2;
		this->row = row;
		this->col = col;

		if(row <= rowCentral)
			z.setImag((double) 1-row/rowCentral);

		if(row > rowCentral)
			z.setImag((double) -1 + ((image.getHeight() - 1) - row)/rowCentral);
		
		if(col <= colCentral)
			z.setReal((double) -1+col/colCentral);

		if(col > colCentral)
			z.setReal((double) 1 - ((image.getWidth()-1) - col)/colCentral);

		this->comp = z;
	}

}

//guarda en row y col los índices asociados al número complejo entregado
void comp2Index(Complejo & z){
	double real = z.getReal();
	double imaginario = z.getImag();
	

	if(abs(real) > 1 || abs(imaginario) > 1) //sale por fuera del plano 
	{
		this->row = 0;
		this->col = 0;
	} 

	else
	{
		int rowCentral = image.getHeight()/2;
		int colCentral = image.getWidth()/2;
		this->comp = z;

		//se aplican las funciones inversas a las utilizadas en index2comp();
		if(real <= 0)
			this->col = colCentral*(real+1);

		if(real > 0)
			this->col = (real-1)*colCentral + (image.getWidth()-1);

		if(imag <= 0)
			this->row = (1-imag)*rowCentral;

		if(imag > 0)
			this->row = (image.getHeight()-1) - (imaginario+1)*rowCentral;
	}

}

