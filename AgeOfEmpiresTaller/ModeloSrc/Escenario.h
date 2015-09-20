/*
 * Escenario.h
 *
 *  Created on: 17/9/2015
 *      Author: ger
 */

#ifndef ESCENARIO_H_
#define ESCENARIO_H_
#include <string>
#include <map>
#include "Entidad.h"
#include "EntidadAnimada.h"

using namespace std;
class Escenario {
public:
	Escenario();
	Escenario(string nombre, int size_x, int size_y);
	string nombre;
	int size_x;
	int size_y;
	vector<Entidad*> entidades;
	EntidadAnimada* protagonista;
	Entidad* getTexturaDefault(); //para rellenar todos los espacios del mapa que no vengan del escenario. EJ: Pasto
	virtual ~Escenario();
};

#endif /* ESCENARIO_H_ */
