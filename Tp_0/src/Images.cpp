/*
 * Images.cpp
 *
 *  Created on: 12 may. 2020
 *      Author: Ramiro
 */

#include "Images.h"

Images::Images(int width, int height, int max) {
	
	if(width <= 0 || height <= 0){
		// Valores por defecto: (Los elegi sin criterio)
		this->width = 10; 
		this->height = 10;
		this->maxInt = 15;	

	} else
	{
		this->width = width;
		this->height = height;
		this->maxInt = max;
	}

	// Pido memoria para la matriz. En el caso que se use la clase vector no se como sera
	//
	this->mat = new int * [this->height];

	for(int filas = 0; filas < height; filas++)
		this->mat[filas] = new int[width];

	// Inicializo la matriz
	//
	for(int filas = 0; filas < height; filas++)
		for(int cols = 0; cols < width; cols++)
			this->mat[filas][cols] = 0;

}

Images::~Images() {
	// TODO Auto-generated destructor stub

	std::cout << "~Images()" << std::endl;

	this->width = 10; 
	this->height = 10;
	this->maxInt = 15;	

	for(int i = 0; i < height; i++)
		delete [] this->mat[i];
	delete [] this->mat;

}

Images::Images(const Images &other) {
	// TODO Auto-generated constructor stub

}

const Images& Images::operator=(const Images &other) {
	// TODO Auto-generated method stub

}

int Images::getWidth(){
	return this->width;
}

int Images::getHeight(){
	return this->height;
}

int ** Images::getMatrix(){
	return this->mat;
}