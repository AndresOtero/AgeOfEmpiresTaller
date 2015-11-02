/*
 * Cuartel.h
 *
 *  Created on: Nov 1, 2015
 *      Author: tobias
 */

#ifndef CUARTEL_H_
#define CUARTEL_H_

#include "EdificioDeCreacion.h"
#include "ObjetoMapa.h"

class Cuartel: public EdificioDeCreacion {
public:
	Cuartel(ObjetoMapa * objeto,Modelo * modelo):EdificioDeCreacion(objeto,modelo){
		StatusPersonaje status = {350,50,20};
		this->tipos_status["soldado"] = status;
	};
	Cuartel(ObjetoMapa * objeto,int x,int y,Modelo * modelo): EdificioDeCreacion(objeto, x, y,modelo){
		StatusPersonaje status = {350,50,20};
		this->tipos_status["soldado"] = status;
	};
	Cuartel();
	virtual ~Cuartel();
};

#endif /* CUARTEL_H_ */
