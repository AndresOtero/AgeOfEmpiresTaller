/*
 * FactoryEdificio.cpp
 *
 *  Created on: 11 de nov. de 2015
 *      Author: andres
 */

#include "FactoryEdificio.h"

FactoryEdificio::FactoryEdificio() {
	this->raza="";
}

FactoryEdificio::FactoryEdificio(string raza) {
	this->raza = raza;
}
void FactoryEdificio::setRaza(string raza){
	this->raza =raza;
}
void FactoryEdificio::cargarEdificios(map<string,ObjetoMapa*> tipos){

	map<string, ObjetoMapa*>::iterator it;
	for (it = tipos.begin(); it != tipos.end(); it++)
	{
		//first es key, second es value
		if (it->second->raza == this->raza && (it->second->velocidad_construcccion!=0)){
	    	printf("igualo raza y connstruyo\n");
	    	this->edificios_raza[it->first]=tipos[it->first];
	    }

	}
	printf("salio\n");


}

map<string,ObjetoMapa*> FactoryEdificio::devolverTipos(){
	return this->edificios_raza;
}

vector<string> FactoryEdificio::devolverEdificiosCreables(){
	vector<string> nombres;
	map<string, ObjetoMapa*>::iterator it;
		for (it = edificios_raza.begin(); it != edificios_raza.end(); it++)
		{
			nombres.push_back(it->first);
		}
	return nombres;
}


FactoryEdificio::~FactoryEdificio() {
	// TODO Auto-generated destructor stub
}

