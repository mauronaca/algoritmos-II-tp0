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
			this->imagen[filas][cols] = 0;

	this->magicNumber = "";
}

Images::~Images() {
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

	// Pido memoria p/ la matriz
	//
	this->imagen = new int * [this->height];
	for(int filas = 0; filas < height; filas++)
		this->imagen[filas] = new int[width];

	// Inicializo la matriz
	//
	for(int filas = 0; filas < height; filas++)
		for(int cols = 0; cols < width; cols++)
			this->imagen[filas][cols] = other.imagen[filas][cols];
}

const Images& Images::operator=(const Images &other) {
	if(this == &other)
		return *this;

	this->width = other.width;
	this->height = other.height;
	this->maxInt = other.maxInt;
	this->magicNumber = other.magicNumber;

	// Pido memoria p/ la matriz
	//
	this->imagen = new int * [this->height];
	for(int filas = 0; filas < height; filas++)
		this->imagen[filas] = new int[width];

	// Inicializo la matriz
	//
	for(int filas = 0; filas < height; filas++)
		for(int cols = 0; cols < width; cols++)
			this->imagen[filas][cols] = other.imagen[filas][cols];

	return *this;

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


bool pgmParser(int & nline, int & nfils, int & ncols, std::stringstream  * ss , Images * image){
	if(ss->peek() == EOF)
		return true;

	// Chequea si en la linea a leer existe el caracter #. En caso de que exista corta el proceso.
	//
	size_t npos = string::npos;
	if (ss->str().find('#') != npos){
		nline--;
		return true;
	}

	// Primera linea el header
	//
	if(nline == 1){
		image->magicNumber = ss->str();

		// Elimina el \n o \r que en algunos .pgm aparece
		//
		for (size_t i = 0; i < image->magicNumber.length(); i++){
		    if (		image->magicNumber.c_str()[i] == '\r'
		    		|| 	image->magicNumber.c_str()[i] == '\n'
		    		|| 	image->magicNumber.c_str()[i] == '\r\n'){

		    	image->magicNumber = image->magicNumber.substr(0, i);
		    }
		}
		// Si no es P2, la funcion devuelve falso. Y en ese caso debera cortar la carga del archivo ya que no estamos
		// interesados en otro tipo de formato.
		//
		if( image->magicNumber.compare("P2") != 0 ){
			cerr << "Formato no .pgm" << endl;
			return false;
		}
		return true;
	}

	// Segunda linea. Primero elimina la matriz cargada por el construcutor. Luego lee los nuevos tama;os
	// Por ultimo pide memoria para la matriz con los nuevos tamalios
	//
	if(nline == 2){
		for(int i = 0; i < image->height; i++)
			delete [] image->imagen[i];
		delete [] image->imagen;

		*ss >> image->width >> image->height;

		image->imagen = new int * [image->height];

		for(int filas = 0; filas < image->height; filas++)
			image->imagen[filas] = new int[image->width];

		return true;
	}

	// Tercera linea, lee el maximo brillo.
	//
	if(nline == 3){
		*ss >> image->maxInt;
		return true;
	}

	// Comienza a leer los colores
	//
	while( nfils < image->height && !ss->eof() ) {
		for(; (ncols < image->width) && !ss->eof(); ncols++){
			*ss >> image->imagen[nfils][ncols];
		}
		if(ncols == image->width){
			ncols = 0;
			nfils++;
		}
	}

	return true;
}

const Images & Images::loadFile(std::istream * image){

	if(!image->good()){
		cerr << "Fallo al abrir el archivo" << endl;
		return *this;
	}

	string line;
	int nline = 1;
	int nfils = 0;
	int ncols = 0;

	while( getline(*image, line) ){
		stringstream ss(line);
		if(!pgmParser(nline, nfils, ncols, &ss, this))
			return *this;
		nline++;
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
