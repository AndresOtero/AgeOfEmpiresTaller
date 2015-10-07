/*
 * Entidad.h
 *
 *  Created on: 17/9/2015
 *      Author: ger
 */

#ifndef ENTIDAD_H_
#define ENTIDAD_H_
#include "ObjetoMapa.h"
#include "Posicion.h"

/*obs: la entidad tiene el tipo (ObjetoMapa donde guardo imagen, bases, pixels ref. Se comparte para todas las entidades de un mismo tipo).
 *  Incluye la posicion de cada entidad
 */
class Entidad {
public:
	Entidad(ObjetoMapa* objetoMapa);
	Entidad(ObjetoMapa* objetoMapa, int x, int y);
	void mostrar_contenido();
	ObjetoMapa* objetoMapa;
	Posicion* posicion;
	virtual ~Entidad();
};

#endif /* ENTIDAD_H_ */
