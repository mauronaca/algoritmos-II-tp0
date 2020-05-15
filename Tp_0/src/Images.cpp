/*
 * Images.cpp
 *
 *  Created on: 12 may. 2020
 *      Author: Ramiro
 */

#include "Images.h"
#include <cstdlib>

using namespace std;

Images::Images() {
	this->width = 10;
	this->height = 10;
	this->maxInt = 255;

	// Pido memoria para la matriz. En el caso que se use la clase vector no se como sera
	//
	this->imagen = new int * [this->height];

	for(int filas = 0; filas < height; filas++)
		this->imagen[filas] = new int[width];

	// Inicializo la matriz
	//
	for(int filas = 0; filas < height; filas++)
		for(int cols = 0; cols < width; cols++)
			this->imagen[filas][cols] = this->maxInt;

	this->magicNumber = "";
}

Images::Images(int width, int height, int max) {

	if(width <= 0 || height <= 0){
		// Valores por defecto: (Los elegi sin criterio)
		this->width = 10;
		this->height = 10;
		this->maxInt = 255;

	} else
	{
		this->width = width;
		this->height = height;
		this->maxInt = max;
	}

	// Pido memoria para la matriz. En el caso que se use la clase vector no se como sera
	//
	this->imagen = new int * [this->height];

	for(int filas = 0; filas < height; filas++)
		this->imagen[filas] = new int[width];

	// Inicializo la matriz
	//
	for(int filas = 0; filas < height; filas++)
		for(int cols = 0; cols < width; cols++)
			this->imagen[filas][cols] = this->maxInt;

	this->magicNumber = "";
}

Images::~Images() {
	// TODO Auto-generated destructor stub

	for(int i = 0; i < height; i++)
		delete [] this->imagen[i];
	delete [] this->imagen;

	this->width = 0;
	this->height = 0;
	this->maxInt = 0;
	this->magicNumber = "";

}

Images::Images(const Images &other) {
	this->width = other.width;
	this->height = other.height;
	this->maxInt = other.maxInt;

	this->magicNumber = other.magicNumber;
	this->imagen = other.imagen;
}

const Images& Images::operator=(const Images &other) {
	// TODO Auto-generated method stub

}

int & Images::operator[](const std::pair<int,int> & index){
	int row = index.first;
	int col = index.second;

	if( (row < 0 || row >= this->height) && (col < 0 || col >= this->width) )
		return this->imagen[0][0];

	return this->imagen[row][col];
}

Images::fila Images::operator[](const int fil){
	if( fil < 0 || fil >= this->height)
			return fila(*this, 0);
	return fila(*this, fil);
}

int Images::getWidth(){
	return this->width;
}

int Images::getMaxInt(){
	return this->maxInt;
}

int Images::getHeight(){
	return this->height;
}

int ** Images::getColours(){
	return this->imagen;
}

std::string Images::getMagicNumber(){
	return this->magicNumber;
}

bool Images::isPGM(){
	if(magicNumber == "P2")
		return true;
	return false;
}

void Images::printColours(){
	for(int i = 0; i < this->height; i++){
		for(int j = 0; j < this->width; j++){
			//cout << this->imagen[i][j] << " ";
            std::cout << std::left << std::setw(2) << this->imagen[i][j];
		}
		cout << endl;
	}
}

/*----------------------------------------*/
/*-----------Manejo de archivos-----------*/
/*----------------------------------------*/

// Precondicion: Validar el archivo.pgm

const Images & Images::loadFile(std::istream * image){
	string auxstr;
	stringstream buffer;

	if(!image->good()){
		cerr << "Fallo al abrir el archivo" << endl;
		return *this;
	}

	/* Lee la primer linea, el header. Si no corresponde con un tipo P2, corta la lectura */
	getline(*image, this->magicNumber);
	// En algunos archivos hay un \n o \r al final. Lo elimino del string.
	for (size_t i = 0; i < this->magicNumber.length(); i++){
	    if (this->magicNumber.c_str()[i] == '\r'
	    		|| this->magicNumber.c_str()[i] == '\n'
	    		|| this->magicNumber.c_str()[i] == '\r\n'){
	    	this->magicNumber = this->magicNumber.substr(0, i);
	    }
	}
	if( this->magicNumber.compare("P2") != 0 ){
		cerr << "Formato no .pgm" << endl;
		return *this;
	}

	/* Lee la segunda linea, generalmente algun comentario.*/
	getline(*image, auxstr);
	//auxstr = auxstr.substr(2); // Se puede sacar, lo que hace es eliminar los 2 primeros caracteres
	cout << auxstr << endl;

	/*--------------------------------------*/
	/*Reasigno el tama? de la imagen. Borro*/
	/*de la memoria la matriz y				*/
	/* vuelvo a pedir memoria para el		*/
	/* nuevo tama?							*/
	/*--------------------------------------*/
	/* Libero mat*/
	for(int i = 0; i < height; i++)
		delete [] this->imagen[i];
	delete [] this->imagen;

	/* Leo los nuevos tama?s desde el archivo*/
	buffer << image->rdbuf();
	buffer >> this->width >> this->height;

	/* Vuelvo a pedir memoria */
	this->imagen = new int * [this->height];

	for(int filas = 0; filas < height; filas++)
		this->imagen[filas] = new int[width];
	/*--------------------------------------*/

	buffer >> this->maxInt;

	/*--------------------------------------*/
	/* Colorear la imagen					*/
	/*--------------------------------------*/
	for(int filas = 0; filas < this->height; filas++){
		for(int cols = 0; cols < this->width; cols++){
			buffer >> imagen[filas][cols];
		}
	}

	return *this;
}

const Images & Images::saveFile(ostream * image){

	if(!image->good()){
		cerr << "Fallo al abrir el archivo" << endl;
		return *this;
	}

	*image << this->magicNumber << endl;
	*image << "# Imagen .pgm generada desde tp0.exe" << endl;
	*image << this->width << " " << this->height << endl;
	*image << this->maxInt << endl;

	for(int fils = 0; fils < this->height; fils++){
		for(int cols = 0; cols < this->width; cols++){
			*image << this->imagen[fils][cols] << endl;
		}
	}

	return *this;
}















