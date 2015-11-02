/*
 * EdificioDeCreacion.cpp
 *
 *  Created on: Nov 1, 2015
 *      Author: tobias
 */

#include "EdificioDeCreacion.h"

vector<string> EdificioDeCreacion::obtenerListaCreables(){

	//TODO PROBAR QUE ESTO ANDE
	//http://www.gamedev.net/topic/516557-extracting-keys-from-a-stdmap/
	vector<string> lista = vector<string>();
	map<string,StatusPersonaje>::iterator i = this->tipos_status.begin();
	for (; i!=this->tipos_status.end(); ++i)
	{
	  string key = i->first;
	  lista.push_back(key);
	  // do something with it here like adding it to a vector
	}
	return lista;
}




EdificioDeCreacion::~EdificioDeCreacion() {
	// TODO Auto-generated destructor stub
}

