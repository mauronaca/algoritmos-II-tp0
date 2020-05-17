/*
 * ComplexPlane.cpp
 *
 *  Created on: 12 may. 2020
 *      Author: Ramiro
 */

#include "ComplexPlane.h"
#include "Images.h"

ComplexPlane::ComplexPlane(int realAxesLimit, int imagAxesLimit) {
    this->realAxesLimit = realAxesLimit;
    this->imagAxesLimit = imagAxesLimit;
    pComplexPlane.resize(realAxesLimit);
    for (unsigned i = 0; i < pComplexPlane.size(); i++)
    {
    	pComplexPlane[i].resize(imagAxesLimit);
    }
}

// Constructor for Given Matrix
ComplexPlane mappingFromImage(const Images inputImage)
{

	int realAxesLimit = inputImage.getWidth();
	int imagAxesLimit = inputImage.getHeight();

	ComplexPlane OutputPlane(realAxesLimit,imagAxesLimit);

	for (unsigned i = 0; i < realAxesLimit; i++)
	{
		for (unsigned i = 0; i < realAxesLimit; i++)
		{
			OutputPlane[i][j]=inputImage[i][j];
		}
	}



}


ComplexPlane::~ComplexPlane() {
	// TODO Auto-generated destructor stub
}

ComplexPlane::ComplexPlane(const ComplexPlane &other) {
	// TODO Auto-generated constructor stub

}

ComplexPlane& ComplexPlane::operator=(const ComplexPlane &other) {
	// TODO Auto-generated method stub

}

ComplexPlane transform(const ComplexPlane InputPlane, SELECTED_FUNCTION FX )
{

};

ComplexPlane antiTransform(const ComplexPlane InputPlane, SELECTED_FUNCTION FX )
{};



Images mappingFromComplexPlane(const ComplexPlane inputPlane)
{};
