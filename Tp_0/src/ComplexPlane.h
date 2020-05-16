/*
 * ComplexPlane.h
 *
 *  Created on: 12 may. 2020
 *      Author: Ramiro
 */

#ifndef COMPLEXPLANE_H_
#define COMPLEXPLANE_H_

#include "Complejo.h"
#include "Images.h"

class ComplexPlane {
private:
	Complejo comp; //número complejo guardado
	Images image; //imagen
	int index; //indice del pixel de una imagen (?)

public:
	ComplexPlane();
	virtual ~ComplexPlane();
	ComplexPlane(const ComplexPlane &other);
	ComplexPlane& operator=(const ComplexPlane &other);


	//Complejo index2Comp();
	//Int comp2Index();

};

#endif /* COMPLEXPLANE_H_ */
