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

/*obs: la entidad tiene el tipo (ObjetoMapa donde guardo imagen, bases, pixels ref. Se comparte para todas las entidades de un mismo tipo).
 *  Incluye la posicion de cada entidad
 */

class Entidad :public Atacable{
	bool seleccionado=false;
	int vida;
	string raza;
	map<string,ObjetoMapa*> diccionario_de_personajes;
	int velocidad_cosntruccion;
public:
	Entidad(ObjetoMapa* objetoMapa);
	Entidad(ObjetoMapa* objetoMapa, int x, int y);
	void cargarPersonajes(map<string,ObjetoMapa*> tipos);
	string mostrar_contenido();
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
	Posicion get_posicion(){
		return *(this->posicion);
	}
	void recibirDanio(int danio){
		this->vida-=danio;
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

};

#endif /* ENTIDAD_H_ */
