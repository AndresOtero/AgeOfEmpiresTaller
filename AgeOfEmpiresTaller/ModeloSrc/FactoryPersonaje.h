/*
 * FactoryPersonaje.h
 *
 *  Created on: 13 de nov. de 2015
 *      Author: andres
 */

#ifndef FACTORYPERSONAJE_H_
#define FACTORYPERSONAJE_H_
using namespace std;
#include <map>
#include <memory>
#include "ObjetoMapa.h"
class FactoryPersonaje {
private:
	string edificio;
	map<string,map<string,ObjetoMapa*>> diccionario_de_diccionarios_de_personajes_por_edificio;

public:
	FactoryPersonaje() ;
	void cargarPersonajes(map<string,ObjetoMapa*> tipos);
	map<string,ObjetoMapa*> devolverTipos(string edificio);
	virtual ~FactoryPersonaje();
};

#endif /* FACTORYPERSONAJE_H_ */
