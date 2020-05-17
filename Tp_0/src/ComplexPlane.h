/*
 * ComplexPlane.h
 *
 *  Created on: 12 may. 2020
 *      Author: Ramiro
 */

#ifndef COMPLEXPLANE_H_
#define COMPLEXPLANE_H_

#include <vector>
#include <string>
#include "images.h"

typedef enum {
	FX_EXP,
	FX_DEFAULT
} SELECTED_FUNCTION;


class ComplexPlane {

private:

	int realAxesLimit;
	int imagAxesLimit;
	std::vector<std::vector<double>> pComplexPlane;


	ComplexPlane transform(const ComplexPlane InputPlane, SELECTED_FUNCTION FX );
	ComplexPlane antiTransform(const ComplexPlane InputPlane, SELECTED_FUNCTION FX );

public:

	ComplexPlane(int,int);
	virtual ~ComplexPlane();
	ComplexPlane(const ComplexPlane &other);
	ComplexPlane& operator=(const ComplexPlane &other);


	ComplexPlane mappingFromImage(const Images inputImage);
	Images mappingFromComplexPlane(const ComplexPlane inputPlane);


};

#endif /* COMPLEXPLANE_H_ */
