/*
 * Juego.h
 *
 *  Created on: 20/9/2015
 *      Author: ger
 */

#ifndef JUEGO_H_
#define JUEGO_H_
#include "Pantalla.h"
#include "Configuracion.h"
#include "Escenario.h"
#include <map>

class Juego {
public:
	Juego();
	Juego(Pantalla* pantalla, Configuracion* conf, Escenario* escenario, std::map<std::string, ObjetoMapa*> &tipos );
	Pantalla* pantalla;
	Configuracion* conf;
	Escenario* escenario;
	std::map<std::string, ObjetoMapa*> tipos;
	virtual ~Juego();
};

#endif /* JUEGO_H_ */
