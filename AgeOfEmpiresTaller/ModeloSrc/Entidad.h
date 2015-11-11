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

/*obs: la entidad tiene el tipo (ObjetoMapa donde guardo imagen, bases, pixels ref. Se comparte para todas las entidades de un mismo tipo).
 *  Incluye la posicion de cada entidad
 */

class Entidad :public Atacable{
	bool seleccionado=false;
	int vida;
public:
	Entidad(ObjetoMapa* objetoMapa);
	Entidad(ObjetoMapa* objetoMapa, int x, int y);
	string mostrar_contenido();
	ObjetoMapa* objetoMapa;
	Posicion* posicion;
	bool esUnRecurso();
	bool esAdyacente(Posicion pos);
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
		printf("Vida %d\n",vida);
	}
	bool esta_vivo(){
		return (vida>0);
	}
	int getArmadura(){
		return 0;
	}
	virtual ~Entidad();
	int id;
	int getId(){
		return id;
	}
	void setId(int id){
		this->id=id;
	}

};

#endif /* ENTIDAD_H_ */
