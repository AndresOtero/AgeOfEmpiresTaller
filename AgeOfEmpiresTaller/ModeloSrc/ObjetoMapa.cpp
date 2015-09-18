/*
 * ObjetoMapa.cpp
 *
 *  Created on: 16/9/2015
 *      Author: ger
 */

#include "ObjetoMapa.h"

ObjetoMapa::ObjetoMapa(string nombre, vector <string>  imagenes ){
	this -> nombre = nombre;
	this -> imagenes = imagenes;
	this -> baseLogica = new BaseLogica();
	this -> pixelsReferencia = new PixelsReferencia();

}
ObjetoMapa::ObjetoMapa(string nombre, vector <string> imagenes , int ancho_base, int alto_base ){
	this -> nombre = nombre;
	this -> imagenes = imagenes;
	this -> baseLogica = new BaseLogica(ancho_base,alto_base);
	this -> pixelsReferencia = new PixelsReferencia();

}
ObjetoMapa::ObjetoMapa(string nombre, vector <string> imagenes, int ancho_base, int alto_base, int pixel_ref_x, int pixel_ref_y ){
	this -> nombre = nombre;
	this -> imagenes = imagenes;
	this -> baseLogica = new BaseLogica(ancho_base,alto_base);
	this -> pixelsReferencia = new PixelsReferencia(pixel_ref_x, pixel_ref_y);
}

ObjetoMapa::~ObjetoMapa() {
	delete this -> baseLogica;
	delete this -> pixelsReferencia;
}

