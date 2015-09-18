/*
 * FactoryDibujo.h
 *
 *  Created on: 16 de set. de 2015
 *      Author: andres
 */
#include "../ModeloSrc/Celda.h"
#include "Dibujo.h"
#include <vector>
using namespace std;
#ifndef FACTORYDIBUJO_H_
#define FACTORYDIBUJO_H_

class FactoryDibujo {
	/**Guarda los dibujos**/
	vector<shared_ptr<Dibujo>> dibujos;
	size_t cantidad_de_dibujos;
	size_t dibujo_actual;
	SDL_Renderer* gRenderer;
public:
	FactoryDibujo(SDL_Renderer* gRenderer);
	bool crear_dibujo(string path,size_t cantidad_de_imagenes,std::vector<std::vector<int> >parametros_de_imagen);
	shared_ptr<Dibujo> get_dibujo(size_t n_dibujo);
	size_t ultimo_dibujo();
	virtual ~FactoryDibujo();
private:
	void set_dibujo(shared_ptr<Dibujo> dibujo);
};

#endif /* FACTORYDIBUJO_H_ */
