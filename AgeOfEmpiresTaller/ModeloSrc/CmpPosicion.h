/*
 * CmpPosicion.h
 *
 *  Created on: 5 de oct. de 2015
 *      Author: andres
 */

#ifndef CMPPOSICION_H_
#define CMPPOSICION_H_

struct cmp_posiciones { /**
	Necesita un comparador para funcionar el diccionario (igualar claves), luego de mucho buscar encontre el
	que funciona.
 	 	**/
	bool operator()(Posicion const& a, Posicion const& b) const {
		if (a.getX() < b.getX())
			return true;
		if (a.getX() == b.getX()) {
			if (a.getY() < b.getY())
				return true;
			return false;
		}
		return false;

	}
};
typedef struct cmp_posiciones cmp_posiciones;




#endif /* CMPPOSICION_H_ */
