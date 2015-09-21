/*
 * FactoryDibujo.h
 *
 *  Created on: 16 de set. de 2015
 *      Author: andres
 */
#include "../ModeloSrc/Celda.h"
#include "DibujoPersonaje.h"
#include "vector"
#include "memory.h"

#include "DibujoEstatico.h"
#include "DibujoEstaticoAnimado.h"
using namespace std;
#ifndef FACTORYDIBUJO_H_
#define FACTORYDIBUJO_H_

class FactoryDibujo {
	/**Guarda los dibujos**/
	vector<shared_ptr<Dibujo_Estatico>> dibujos;
	size_t cantidad_de_dibujos;
	size_t dibujo_actual;
	SDL_Renderer* gRenderer;
public:
	FactoryDibujo(SDL_Renderer* gRenderer);
	bool crear_dibujo(string path, vector<int>parametros_de_imagen);
	bool crear_dibujo_animado(string path,size_t cantidad_de_imagenes,std::vector<std::vector<int> >parametros_de_imagen,int fps);
	bool crear_dibujo_personaje(string path,size_t cantidad_de_movimientos,vector<int> cantidad_de_imagenes,std::vector<std::vector<int> >parametros_de_imagen,int fps,int velocidad);
	shared_ptr<Dibujo_Estatico> get_dibujo(size_t n_dibujo);
	size_t ultimo_dibujo();
	virtual ~FactoryDibujo();
private:
	void set_dibujo(shared_ptr<Dibujo_Estatico> dibujo);
};

#endif /* FACTORYDIBUJO_H_ */
