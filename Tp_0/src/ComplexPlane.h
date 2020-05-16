#ifndef COMPLEXPLANE_H_
#define COMPLEXPLANE_H_

#include "Complejo.h"
#include "Images.h"

class ComplexPlane {
private:
	Complejo comp; //número complejo guardado
	Images image; //imagen utilizada
	int row; //fila y
	int col; //columna guardadas para el número complejo entregado

public:
	ComplexPlane();
	ComplexPlane(Images &); //guarda los datos de una imagen para tener sus dimensiones
	~ComplexPlane(); //destructor
	ComplexPlane(const ComplexPlane &other); // constructor copia
	ComplexPlane& operator=(const ComplexPlane &other); //sobrecarga de la asignación

	
	Complejo getComp();
	Images getImage();
	int getRow();
	int getCol();

	void index2Comp(int, int);
	void comp2Index(Complejo &);

};

#endif /* COMPLEXPLANE_H_ */
