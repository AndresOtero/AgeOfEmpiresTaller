/*
 * FactoryDibujo.h
 *
 *  Created on: 16 de set. de 2015
 *      Author: andres
 */
#include "../ModeloSrc/Celda.h"
#include "Dibujo.h"
#include "DibujoAnimado.h"
#include "DibujoPersonaje.h"
#include "DibujoEstatico.h"
#include "vector"
#include "memory.h"
using namespace std;
#ifndef FACTORYDIBUJO_H_
#define FACTORYDIBUJO_H_

class FactoryDibujo {
	/**Guarda los dibujos**/
	vector<shared_ptr<Dibujo>> dibujos;
	int cantidad_de_dibujos;
	int dibujo_actual;
	SDL_Renderer* gRenderer;
public:
	FactoryDibujo(SDL_Renderer* gRenderer);
	bool crear_dibujo_estatico(string path, vector<int>parametros_de_imagen);
	bool crear_dibujo_personaje(string path,int cantidad_de_movimientos,vector<int> cantidad_de_imagenes,vector<vector<vector<int> >>parametros_de_imagen,int fps,int velocidad);
	bool crear_dibujo_animado(string path,vector<int> pixeles,std::vector<std::vector<int> >parametros_de_imagen,int fps, int delay);
	shared_ptr<Dibujo> get_dibujo(int n_dibujo);
	int ultimo_dibujo();
	virtual ~FactoryDibujo();
private:
	void set_dibujo(shared_ptr<Dibujo> dibujo);
};

#endif /* FACTORYDIBUJO_H_ */
