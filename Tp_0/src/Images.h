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
#include <string.h>


class Images {
private:
	int width;
	int height;
	int maxInt; // Intensidad maxima de la imagen
	int ** imagen; // Matriz. Podria usarse la clase vector... Por ahora lo implemento asi
	std::string magicNumber; //

	class fila{
		friend class Images;
	private:
		Images & matriz;
		int fil;
		fila(Images & imagen_, int fila_): matriz(imagen_), fil(fila_) {}
	public:
		int & operator[](const int col) {
			if( col >= matriz.width || col < 0)
				return matriz.imagen[fil][0];
			return matriz.imagen[fil][col];
		}
	};

public:
	Images();
	Images(int, int, int); // Inicializa ** mat
	virtual ~Images(); // Debe liberar memoria de ** mat
	Images(const Images &other);

	const Images& operator=(const Images &other);
	int & operator[](const std::pair<int,int> &);
	fila operator[](const int);

	friend bool pgmParser(int & , int &, int &, std::stringstream  * , Images * );

	const Images & loadFile(std::istream * ); // Duda si recibirlo por referencia o puntero/
	const Images & saveFile(std::ostream * ); // Duda si rei\cibirlo por referencia o puntero


	int getMaxInt();
	int getWidth();
	int getHeight();
	std::string getMagicNumber();
	int ** getColours();

	void printColours();

	bool isPGM();
};

#endif /* IMAGES_H_ */
