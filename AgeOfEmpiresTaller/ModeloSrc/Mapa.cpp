/*
 * Mapa.cpp
 *
 *  Created on: 29 de ago. de 2015
 *      Author: andres
 */

#include "../ModeloSrc/Mapa.h"
#include "../ModeloSrc/Celda.h"

Mapa::Mapa(int largo, int ancho) {
	// TODO Auto-generated constructor stub
	this->largo=largo;
	this->ancho=ancho;
	this->celdas = new Celda**[largo];
	for (int i = 0; i < largo; ++i) {
		this->celdas[i] = new Celda*[ancho];
	}
	for(int i =0; i<largo;i++){
		for(int j=0;j<ancho;j++){
			celdas[largo][ancho]=new Celda();
		}
	}

}

Mapa::~Mapa() {
	// TODO Auto-generated destructor stub
}

