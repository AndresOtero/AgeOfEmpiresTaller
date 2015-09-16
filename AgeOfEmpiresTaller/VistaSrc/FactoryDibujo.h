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
	vector<Dibujo* > dibujos;
	size_t cantidad_de_dibujos;
	size_t dibujo_actual;
public:
	FactoryDibujo();
	size_t set_dibujo(Dibujo* dibujo);
	Dibujo* get_dibujo(size_t n_dibujo);
	virtual ~FactoryDibujo();
};

#endif /* FACTORYDIBUJO_H_ */
