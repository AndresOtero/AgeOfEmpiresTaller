/*
 * FactoryEdificio.h
 *
 *  Created on: 11 de nov. de 2015
 *      Author: andres
 */
#include <map>
#include <memory>
#include "ObjetoMapa.h"
#include "Entidad.h"

#ifndef FACTORYEDIFICIO_H_
#define FACTORYEDIFICIO_H_
using namespace std;

class FactoryEdificio {
	string raza;
	map<string,ObjetoMapa*> edificios_raza;
public:
	FactoryEdificio();
	FactoryEdificio(string raza);
	void cargarEdificios(map<string,ObjetoMapa*> tipos);
	vector<string> devolverEdificiosCreables();
	void setRaza(string raza);
	map<string,ObjetoMapa*> devolverTipos();
	virtual ~FactoryEdificio();
};

#endif /* FACTORYEDIFICIO_H_ */
