/*
 * Juego.h
 *
 *  Created on: 20/9/2015
 *      Author: ger
 */

#ifndef JUEGO_H_
#define JUEGO_H_
#include "Pantalla.h"
#include "Oro.h"
#include "Madera.h"
#include "Piedra.h"


#include "Configuracion.h"
#include "Escenario.h"
#include <map>

class Juego {
private :
	void cargarTiposDefault();
public:
	Juego();
	Juego(Pantalla* pantalla, Configuracion* conf, Escenario* escenario, std::map<std::string, ObjetoMapa*> &tipos );
	void setEscenario(string nombre,int ancho,int largo);
	void setConfiguracion(int margenScroll,int velocidad_personaje);
	void agregarEntidad(string nombre,int x, int y);


	Pantalla* pantalla;
	Configuracion* conf;
	Escenario* escenario;
	std::map<std::string, ObjetoMapa*> tipos;
	virtual ~Juego();
};

#endif /* JUEGO_H_ */
