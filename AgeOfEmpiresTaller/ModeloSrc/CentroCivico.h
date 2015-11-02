/*
 * CentroCivico.h
 *
 *  Created on: Nov 1, 2015
 *      Author: tobias
 */

#ifndef CENTROCIVICO_H_
#define CENTROCIVICO_H_

#include "EdificioDeCreacion.h"


class CentroCivico: public EdificioDeCreacion {
public:
	CentroCivico(ObjetoMapa * objeto,Modelo * modelo): EdificioDeCreacion(objeto,modelo){
		StatusPersonaje status = {200,0,20};
		this->tipos_status["aldeano"] = status;
	};
	CentroCivico(ObjetoMapa * objeto,int x, int y,Modelo * modelo): EdificioDeCreacion(objeto,x,y,modelo){
		StatusPersonaje status = {200,0,20};
		this->tipos_status["aldeano"] = status;
	};
	Personaje * crearPersonaje(string nombre);
	virtual ~CentroCivico();
};

#endif /* CENTROCIVICO_H_ */
