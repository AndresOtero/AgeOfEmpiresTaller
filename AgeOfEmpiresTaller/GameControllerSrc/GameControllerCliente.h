/*
 * GameControllerCliente.h
 *
 *  Created on: 21 de oct. de 2015
 *      Author: andres
 */

#ifndef GAMECONTROLLERSRC_GAMECONTROLLERCLIENTE_H_
#define GAMECONTROLLERSRC_GAMECONTROLLERCLIENTE_H_
#include "GameController.h"

class GameControllerCliente:public GameController  {

public:
	GameControllerCliente(Modelo* modelo);
	virtual ~GameControllerCliente();
};

#endif /* GAMECONTROLLERSRC_GAMECONTROLLERCLIENTE_H_ */
