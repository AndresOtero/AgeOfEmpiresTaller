/*
 * GameController.h
 *
 *  Created on: 21 de oct. de 2015
 *      Author: andres
 */

#ifndef GAMECONTROLLERSRC_GAMECONTROLLER_H_
#define GAMECONTROLLERSRC_GAMECONTROLLER_H_

class GameController {
	Modelo modelo;
public:
	GameController(Modelo* modelo);
	virtual ~GameController();
};

#endif /* GAMECONTROLLERSRC_GAMECONTROLLER_H_ */
