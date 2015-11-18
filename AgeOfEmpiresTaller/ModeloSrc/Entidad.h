/*
 * Entidad.h
 *
 *  Created on: 17/9/2015
 *      Author: ger
 */

#ifndef ENTIDAD_H_
#define ENTIDAD_H_
#include "GeneradorNumeros.h"
#include "ObjetoMapa.h"
#include "Posicion.h"
#include "Atacable.h"
#include "FactoryPersonaje.h"
#include "Costo.h"
#include "../VistaSrc/DatosSeleccionado.h"

/*obs: la entidad tiene el tipo (ObjetoMapa donde guardo imagen, bases, pixels ref. Se comparte para todas las entidades de un mismo tipo).
 *  Incluye la posicion de cada entidad
 */

class Entidad :public Atacable{
	bool seleccionado=false;
	int vida;
	string raza;
	map<string,ObjetoMapa*> diccionario_de_personajes;
	int velocidad_cosntruccion;
	Costo costo;
	bool esUnaBandera;
public:
	Entidad(ObjetoMapa* objetoMapa);
	Entidad(ObjetoMapa* objetoMapa, int x, int y);
	void cargarPersonajes(map<string,ObjetoMapa*> tipos);
	DatosSeleccionado mostrar_contenido();
	ObjetoMapa* objetoMapa;
	Posicion* posicion;
	bool esUnRecurso();
	bool esAdyacente(Posicion pos);
	void set_posicion(int x, int y){
		this->posicion->set(x,y);
	}
	void seleccionar(){
		this->seleccionado=true;
	}
	void deselccionar(){
		this->seleccionado=false;
	}
	bool estaSeleccionado(){
		return seleccionado;
	}
	Costo getCosto(){
		return this->costo;
	}
	Posicion get_posicion(){
		return *(this->posicion);
	}
	void recibirDanio(int danio){
		int resultado = vida - danio;
		if (resultado < 0) {
			this->vida = 0;
		} else {
			this->vida = resultado;
		}
	}
	bool esta_vivo(){
		return (vida>0);
	}
	int getArmadura(){
		return 0;
	}
	bool estaConstruida(){
		return (this->velocidad_cosntruccion<=0);
	}
	int construir(int construccion){
		this->velocidad_cosntruccion-=construccion;
		return construccion;

	}
	void finalizarConstruccion(){
			this->velocidad_cosntruccion=0;
		}
	string get_raza(){
		return raza;
	}
	bool esUnCentroCivio();
	
	bool setEsUnaBandera(){
		esUnaBandera=true;
	}

	bool esBandera(){
		return esUnaBandera;
	}
	bool esInternaLaPosicion(int x, int y);
	virtual ~Entidad();
	int id;
	int getId(){
		return id;
	}
	void setId(int id){
		this->id=id;
	}
	map<string,ObjetoMapa*> devolverPersonajesCreables();
	bool  puedeCrearPersonajes();
	bool estaEnRango(int rango, Posicion pos);

};

#endif /* ENTIDAD_H_ */
