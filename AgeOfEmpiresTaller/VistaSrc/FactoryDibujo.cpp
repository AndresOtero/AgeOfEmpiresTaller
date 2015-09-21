/*
 * FactoryDibujo.cpp
 *
 *  Created on: 16 de set. de 2015
 *      Author: andres
 */

#include "FactoryDibujo.h"
#define DIBUJOS_POR_DEFAULT 5
#define CANTIDAD_DE_PARAMETROS 4
enum parametros {X=0,Y=1,ANCHO=2,ALTO=3};

FactoryDibujo::FactoryDibujo(SDL_Renderer* gRenderer) {
	// TODO Auto-generated constructor stub
	this->dibujos=vector<shared_ptr<Dibujo>>(DIBUJOS_POR_DEFAULT,NULL);
	this->gRenderer=gRenderer;
	this->cantidad_de_dibujos=this->dibujos.size();
	this->dibujo_actual=1;
}
bool FactoryDibujo::crear_dibujo_personaje(string path,int cantidad_de_movimientos,vector<int> cantidad_de_imagenes,std::vector<std::vector<int> >parametros_de_imagen,int fps,int velocidad){
	shared_ptr<DibujoPersonaje> dibujo_nuevo = shared_ptr<DibujoPersonaje>(new DibujoPersonaje());
	if (!dibujo_nuevo->cargar_archivo(path,gRenderer)) {
		printf("Failed to load image!\n");
	} else {
		dibujo_nuevo->set_cantidad_de_movimientos(cantidad_de_movimientos);
		for(int i=0;i<cantidad_de_movimientos;i++){
			dibujo_nuevo->set_cantidad_de_imagenes(i,cantidad_de_imagenes[i]);
			for (int j = 0; j < cantidad_de_imagenes[i]; j++) {
						dibujo_nuevo->set_imagen(i,j, parametros_de_imagen[i][X], parametros_de_imagen[i][Y],parametros_de_imagen[i][ANCHO], parametros_de_imagen[i][ALTO]);
			}
		}

		dibujo_nuevo->set_velocidad(velocidad);
		this->set_dibujo(dibujo_nuevo);
		return true;
	}
	return false;
}
bool FactoryDibujo::crear_dibujo_animado(string path,std::vector<std::vector<int> >parametros_de_imagen,int fps){
	shared_ptr<DibujoAnimado> dibujo_nuevo = shared_ptr<DibujoAnimado>(new DibujoAnimado());
	if (!dibujo_nuevo->cargar_archivo(path, gRenderer)) {
		printf("Failed to load image!\n");
	} else {
		dibujo_nuevo->set_cantidad_de_imagenes(DIBUJOS_POR_DEFAULT);
		for (int i = 0; i < DIBUJOS_POR_DEFAULT; i++) {
			dibujo_nuevo->set_imagen(i, parametros_de_imagen[i][X], parametros_de_imagen[i][Y]);
		}
		dibujo_nuevo->set_fps(fps);
		this->set_dibujo(dibujo_nuevo);
		return true;
	}
	return false;
}
bool FactoryDibujo::crear_dibujo_estatico(string path, vector<int>parametros_de_imagen){
	shared_ptr<Dibujo_Estatico> dibujo_nuevo = shared_ptr<Dibujo_Estatico>(new Dibujo_Estatico());
	if (!dibujo_nuevo->cargar_archivo(path, gRenderer)) {
		printf("Failed to load image!\n");
	} else {
		dibujo_nuevo->set_imagen(parametros_de_imagen[X], parametros_de_imagen[Y]);
		this->set_dibujo(dibujo_nuevo);
		return true;
	}
	return false;
}
int FactoryDibujo::ultimo_dibujo(){
	return (dibujo_actual-1);
}

void FactoryDibujo::set_dibujo(shared_ptr<Dibujo> dibujo){
	if(this->dibujos.capacity()==dibujo_actual){
		this->dibujos.resize(this->dibujos.capacity()*2,NULL);
	}
	this->dibujos.insert(this->dibujos.begin()+dibujo_actual,dibujo);
	dibujo_actual++;
}

shared_ptr<Dibujo> FactoryDibujo::get_dibujo(int n_dibujo){
	if(n_dibujo>=this->dibujo_actual){
		return NULL;
	}
	return this->dibujos[n_dibujo];
}


FactoryDibujo::~FactoryDibujo() {

}

