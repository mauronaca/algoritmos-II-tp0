/*
 * ComplexPlane.h
 *
 *  Created on: 12 may. 2020
 *      Author: Ramiro
 */

#ifndef COMPLEXPLANE_H_
#define COMPLEXPLANE_H_

class ComplexPlane {
public:
	ComplexPlane();
	virtual ~ComplexPlane();
	ComplexPlane(const ComplexPlane &other);
	ComplexPlane& operator=(const ComplexPlane &other);
};

#endif /* COMPLEXPLANE_H_ */
