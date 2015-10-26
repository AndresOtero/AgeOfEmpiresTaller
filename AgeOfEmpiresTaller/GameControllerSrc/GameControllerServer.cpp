/*
 * GameControllerServer.cpp
 *
 *  Created on: 21 de oct. de 2015
 *      Author: andres
 */

#include "GameControllerServer.h"

GameControllerServer::GameControllerServer() {
	// TODO Auto-generated constructor stub
}
GameControllerServer::~GameControllerServer() {
	// TODO Auto-generated constructor stub
}

void GameControllerServer::agregarCliente(string tipo){
	ObjetoMapa* obj=this->juego->tipos[tipo];
	Personaje* personaje =new Personaje(obj);
	int id =this->modelo->crearPersonajeServer(personaje);
	//mandarle el id y el personaje a todos los clientes
	//this->modelo->crearPersonajeCliente(personaje);
	//Setear Ḿodelo del que lo mando
	//this->modelo->setearPersonajeCliente(id,personaje->get_posicion())
}

void GameControllerServer::desconectar(string Id){
	//this->modelo->congelarPersonaje(Id);
	//Congelar en todos
}
void GameControllerServer::reconectar(string Id){
					//this->modelo->descongelarPersonaje(Id);
					//Descongelar en todos
			 }

void GameControllerServer::actualizar(){
	this->modelo->actualizarMapa();//mueven los tipitos
	vector<Personaje*> personajes=this->modelo->devolverTodosLosPersonajes();
	vector<Personaje*>::iterator it = personajes.begin();
			for (; it != personajes.end(); ++it) {
				Personaje* p = (*it);
				double mov_x=p->get_posicion().get_x_exacta();
				double mov_y=p->get_posicion().get_x_exacta();
					//Para todos los clientes

					 //void cambiar_destino_personaje(int p->getId(), double mov_x,double mov_y);

			}
}
