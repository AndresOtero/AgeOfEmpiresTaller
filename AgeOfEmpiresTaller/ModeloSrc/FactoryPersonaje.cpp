/*
 * FactoryPersonaje.cpp
 *
 *  Created on: 13 de nov. de 2015
 *      Author: andres
 */

#include "FactoryPersonaje.h"

FactoryPersonaje::FactoryPersonaje() {
	// TODO Auto-generated constructor stub
}


FactoryPersonaje::~FactoryPersonaje() {
	// TODO Auto-generated destructor stub
}
void FactoryPersonaje::cargarPersonajes(map<string,ObjetoMapa*> tipos){
	map<string, ObjetoMapa*>::iterator it_edificios;
	map<string, ObjetoMapa*>::iterator it_personajes;
		for (it_edificios = tipos.begin(); it_edificios != tipos.end(); it_edificios++)	{
			//first es key, second es value
			printf("Edificio Constructor: %s\n",it_edificios->second->edificio_constructor.c_str());

			for (it_personajes = tipos.begin(); it_personajes != tipos.end(); it_personajes++)	{
				if (it_personajes->second->edificio_constructor == it_edificios->first){

					this->diccionario_de_diccionarios_de_personajes_por_edificio[it_edificios->first][it_personajes->first]=tipos[it_personajes->first];
				}

		}
	}
}
map<string,ObjetoMapa*> FactoryPersonaje::devolverTipos(string edificio){
	return this->diccionario_de_diccionarios_de_personajes_por_edificio[edificio];
}

