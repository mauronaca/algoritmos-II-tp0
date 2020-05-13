/*
 * Images.h
 *
 *  Created on: 12 may. 2020
 *      Author: Ramiro
 */

#ifndef IMAGES_H_
#define IMAGES_H_

#include <sstream>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <fstream>


class Images {
private:
	int width;
	int height;
	int maxInt; // Intensidad maxima de la imagen
	int ** mat; // Matriz

public:
	Images();
	Images(int, int, int); // Inicializa ** mat
	virtual ~Images(); // Debe liberar memoria de ** mat
	Images(const Images &other);

	const Images& operator=(const Images &other);

	const Images & loadFile(std::istream & );
	const Images & saveFile(std::ostream & );

	int getWidth();
	int getHeight();
	int ** getMatrix();
};

#endif /* IMAGES_H_ */
