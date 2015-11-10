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
#include <unistd.h>
#include <cstdio>
#include <memory>
#include <iostream>
#include <map>

using namespace std;
#ifndef FACTORYDIBUJO_H_
#define FACTORYDIBUJO_H_

class FactoryDibujo {
	/**Guarda los dibujos**/
	vector<shared_ptr<Dibujo>> dibujos;
	int cantidad_de_dibujos;
	int dibujo_actual;
	SDL_Renderer* gRenderer;
	std::map<std::string, dibujo_t> hashDibujos;
	int ancho_tile, alto_tile;
public:
	FactoryDibujo(SDL_Renderer* gRenderer);
	bool crear_dibujo_tile(string path);
	bool crear_dibujo_estatico(string path, vector<int>parametros_de_imagen);
	bool crear_dibujo_personaje(string path,int cantidad_de_movimientos,int frames,int fps);
	bool crear_dibujo_animado(string path,vector<int> pixeles,std::vector<std::vector<int> >parametros_de_imagen,int fps, int delay);
	shared_ptr<Dibujo> get_dibujo(int n_dibujo);
	int ultimo_dibujo();
	int get_idDibujo(string nombre);
	void setHashDibujos(std::map<std::string, dibujo_t> hashDibujos);
	virtual ~FactoryDibujo();
	int getAnchoTile(){
		return this->ancho_tile;
	}
	int getAltoTile(){
		return this->alto_tile;
	}
private:
	void set_dibujo(shared_ptr<Dibujo> dibujo);
};

#endif /* FACTORYDIBUJO_H_ */
