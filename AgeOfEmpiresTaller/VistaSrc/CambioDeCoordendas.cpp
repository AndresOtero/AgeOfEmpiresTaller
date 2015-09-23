/*
 * CambioDeCoordendas.cpp
 *
 *  Created on: 19 de set. de 2015
 *      Author: andres
 */

#include "CambioDeCoordendas.h"

CambioDeCoordendas::CambioDeCoordendas(int ancho_por_celda,int alto_por_celda) {
	// TODO Auto-generated constructor stub
	ancho_celda=ancho_por_celda;
	alto_celda=alto_por_celda;
}
void CambioDeCoordendas::transformar_isometrica_pantalla(double iso_x,double iso_y,int& pant_x,int& pant_y){
	pant_x = (( iso_x - iso_y ) * this->ancho_por_celda())/2;
	pant_y =(( iso_x + iso_y)*  this->altura_por_celda()) /2;
}
void CambioDeCoordendas::transformar_isometrica_pantalla(int iso_x,int iso_y,int& pant_x,int& pant_y){
	pant_x = (( iso_x - iso_y ) * this->ancho_por_celda())/2;
	pant_y =(( iso_x + iso_y)*  this->altura_por_celda()) /2;
}

void CambioDeCoordendas::transformar_pantalla_isometrica(int pant_x,int pant_y,double& iso_x,double& iso_y){
	double termino_x=  ( (double)pant_x/ (this->ancho_por_celda()/2)) ;
	double termino_y= ( (double)pant_y/ (this->altura_por_celda()/2) );
	iso_x= (termino_x+ termino_y)/2;//MAGIA NEGRA
	iso_y = (termino_y - termino_x)/2;//En serio no se porque funciona
}

void CambioDeCoordendas::transformar_pantalla_isometrica(int pant_x,int pant_y,int& iso_x,int& iso_y){
	double termino_x=  ( (double)pant_x/ (this->ancho_por_celda()/2)) ;
	double termino_y= ( (double)pant_y/ (this->altura_por_celda()/2) );
	iso_x= (termino_x+ termino_y)/2;//MAGIA NEGRA
	iso_y = (termino_y - termino_x)/2;//En serio no se porque funciona
}
int CambioDeCoordendas::ancho_por_celda(){
	return ancho_celda;
}
int CambioDeCoordendas::altura_por_celda(){
	return alto_celda;
}
CambioDeCoordendas::~CambioDeCoordendas() {
	// TODO Auto-generated destructor stub
}

