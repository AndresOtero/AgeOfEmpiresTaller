/*
 * Modelo.cpp
 *
 *  Created on: 29 de ago. de 2015
 *      Author: andres
 */

#include "../ModeloSrc/Modelo.h"
#include "../ModeloSrc/Mapa.h"


Modelo::Modelo() {
	this -> mapa = NULL;
	this -> juego = NULL;
}
void Modelo::setMapa(int ancho,int largo){
	this->mapa=shared_ptr<Mapa>(new Mapa(ancho,largo));
}

void Modelo::setDibujoMapa(vector<vector<dibujo_t>> dibujos){
	int ancho =this->mapa->getAncho();
	int largo =this->mapa->getLargo();
	int i=0,j=0;
	for(;i<ancho;i++){
		for(;j<largo;j++){
			this->mapa->setDibujo(dibujos[i][j],i,j);
		}
	}
}

vector<vector<dibujo_t>> Modelo::dibujar(int x,int 	y,int ancho,int largo){
	/**	Recibe un posicion x,y de comienzo y un ancho y alto para dibujar.
	 	Dibuja entre (x,y),(x+ancho,y),(x,y+largo),(x+ancho)(y+largo)**/
	vector<vector<dibujo_t>> dibujos(ancho);
	for (int i = 0; i < ancho;i++) {
		dibujos[i]=vector<dibujo_t>(largo) ;
	}
	for(int k=0;k<ancho;k++){
		for(int j=0;j<largo;j++){
			dibujos[k][j]=this->mapa->dibujar(x+k,y+j);
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

int Modelo::get_alto_mapa(){
	return mapa->getLargo();
}

int Modelo::get_ancho_mapa(){
	return mapa->getAncho();
}



Modelo::~Modelo() {
	delete this->juego;


}

