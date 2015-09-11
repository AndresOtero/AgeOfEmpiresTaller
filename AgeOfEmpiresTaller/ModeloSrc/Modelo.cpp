/*
 * Modelo.cpp
 *
 *  Created on: 29 de ago. de 2015
 *      Author: andres
 */

#include "../ModeloSrc/Modelo.h"
#include "../ModeloSrc/Mapa.h"

Modelo::Modelo() {
	// TODO Auto-generated constructor stub
}
void Modelo::setMapa(int ancho,int largo){
	this->mapa=new Mapa(ancho,largo);
	int i=0,j=0;
	for(;i<ancho;i++){
		for(;j<largo;j++){
			this->mapa->setDibujo(new Dibujo(DEFAULT),i,j);
		}
	}
}

void Modelo::setDibujoMapa(dibujo_t** dibujos){
	int ancho =this->mapa->getAncho();
	int largo =this->mapa->getLargo();
	int i=0,j=0;
	for(;i<ancho;i++){
		for(;j<largo;j++){
			this->mapa->setDibujo(new Dibujo(dibujos[i][j]),i,j);
		}
	}
}

dibujo_t** Modelo::dibujar(int x,int 	y,int ancho,int largo){
	/**	Recibe un posicion x,y de comienzo y un ancho y alto para dibujar.
	 	Dibuja entre (x,y),(x+ancho,y),(x,y+largo),(x+ancho)(y+largo)**/
	dibujo_t** dibujos=new dibujo_t*[ancho];
	for (int i = 0; i < ancho;i++) {
		dibujos[i] = new dibujo_t[largo];
	}
	for(int i=0;i<ancho;i++){
		for(int j=0;j<largo;j++){
			dibujos[i][j]=this->mapa->dibujar(x+i,y+j);
		}
	}
	return dibujos;
}
void Modelo::eliminarDibujar(int ancho,int largo,dibujo_t** matriz){
	/**	Elimina la matriz creada por dibujar**/
	for (int i = 0; i < ancho; ++i) {
			delete[] matriz[i] ;
	}
	delete[] matriz;
}




Modelo::~Modelo() {
	// TODO Auto-generated destructor stub
	delete this->mapa;

}

