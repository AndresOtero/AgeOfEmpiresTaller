/*
 * GameControllerServer.h
 *
 *  Created on: 21 de oct. de 2015
 *      Author: andres
 */

#ifndef GAMECONTROLLERSRC_GAMECONTROLLERSERVER_H_
#define GAMECONTROLLERSRC_GAMECONTROLLERSERVER_H_

class GameControllerServer:public GameController  {
public:
	GameControllerServer(Modelo* modelo);
	virtual ~GameControllerServer();
};

#endif /* GAMECONTROLLERSRC_GAMECONTROLLERSERVER_H_ */
