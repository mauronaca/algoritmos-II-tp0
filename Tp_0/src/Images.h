/*
 * Images.h
 *
 *  Created on: 12 may. 2020
 *      Author: Ramiro
 */

#ifndef IMAGES_H_
#define IMAGES_H_

// Librerias para manejo de archivos 
#include <sstream>
#include <iostream>
#include <fstream>
#include <iomanip>

#include <string.h>
#include <cstdlib>


class Images {
private:
	// Ancho de la imagen
	int width;
	
	// Altura de la imagen
	int height;
	
	// Intensidad maxima de la imagen
	int maxInt; 
	
	// Matriz donde se almacenan los valores de intensidad
	int ** imagen; 
	
	// El header o algo asi, donde dice P2. Si es P2, el formato es pgm
	std::string magicNumber; 
	
	// Clase fila. Sirve como ayuda para sobrecargar el operador [], de manera que s pueda acceder a la matriz
	// imagen usando la notacion [][].
	//
	// Los atributos son una instancia de Images y el indice de la fila a la que se quiere acceder.
	// Se sobrecarga el operador [], de manera que el argumento sea el indice de la coluumna a la que se quiere acceder
	// y devuelva por referencia el valor de la matriz.
	//
	class fila{
		friend class Images;
	private:
		Images & matriz;
		int fil;
		// Constructor
		fila(Images & imagen_, int fila_): matriz(imagen_), fil(fila_) {}
		// Como no maneja memoria dinamica no se detalle el destructor
	public:
		// Sobrecarga operador []
		int & operator[](const int col) {
			if( col >= matriz.width || col < 0)
				return matriz.imagen[fil][0];
			return matriz.imagen[fil][col];
		}
	};

public:
	// Constructor por defecto, inicializa todo en 0
	Images();
	
	// Constructor, se le pasa como argumento, ancho, alto y maxima intensdad
	Images(int, int, int); 
	
	// Destructor, debera liberar la memoria de la matriz.
	~Images(); 
	
	// Constructor por copia
	Images(const Images &other);

	// Sobreacarga del operador =
	const Images& operator=(const Images &other);
	
	// Sobrecarga del operador []
	int & operator[](const std::pair<int,int> &);
	
	// Otro tipo de sobrecarga del operador []
	//
	// La idea es que se pueda acceder al atributo matriz de la siguiente manera: Images imagen; imagen[fila][columna];
	// Entonces sobrecargo al operador [], de tal manera que su argumento sea la fila, y devuelva una instancia de la
	// clase fila. La clase fila a su vez tendra tambien sobrecarhado el operador [], y este tendra como argumento el indice
	// de columna y devolvera el valor de la matriz.
	//
	fila operator[](const int);
	
	// Funcion para procesar cada linea del archivo con formato .pgm (la usa el metodo de loadFile)
	friend bool pgmParser(int & , int &, int &, std::stringstream  * , Images * );
	
	// Carga un archivo .pgm.
	const Images & loadFile(std::istream * ); 
	
	// Se guarda la instancia de Images en un archiv formato .pgm
	const Images & saveFile(std::ostream * ); 

	// Obtencion de los atributos
	int getMaxInt();
	int getWidth();
	int getHeight();
	std::string getMagicNumber();
	int ** getColours();
	
	// Imprime la matriz
	void printColours();
	
	// Devuelve true si la instanciatiene almacenado datos de una imagen pgm 
	bool isPGM();
};

#endif /* IMAGES_H_ */
