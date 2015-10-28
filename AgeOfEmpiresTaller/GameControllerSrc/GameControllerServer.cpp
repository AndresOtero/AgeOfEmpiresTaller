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

	//seteo mensaje
	msg_t mensaje;
	mensaje.type = NUEVO_PERSONAJE;
	strcpy(mensaje.paramNombre,tipo.c_str());
	mensaje.paramInt1 = id;
	mensaje.paramDouble1 = personaje->get_posicion().get_x_exacta();
	mensaje.paramDouble2 = personaje->get_posicion().get_y_exacta();

	this->agregarMensaje(mensaje);
	//dsps deberian sacarlo y mandarlo a todos
}

void GameControllerServer::desconectar(string Id){
	//this->modelo->congelarPersonaje(Id);
	//Congelar en todos
}
void GameControllerServer::reconectar(string Id){
					//this->modelo->descongelarPersonaje(Id);
					//Descongelar en todos
			 }
void GameControllerServer::cambiar_destino_personaje(int id, double mov_x,double mov_y){
	this->modelo->cambiar_destino_personaje(id,mov_x,mov_y);
}

void GameControllerServer::agregarEntidad(string nombre,int x, int y, int cant){
	this->agregarEntidad(nombre,x,y,cant);
	msg_t mensaje;
	mensaje.type=CREAR_ENTIDAD;
	//strcpy TODO
	mensaje.paramInt1 = cant;
	mensaje.paramDouble1 = x;
	mensaje.paramDouble2 = y;
	this->agregarMensaje(mensaje);

}
void GameControllerServer::actualizar(){
	this->modelo->actualizarMapa();//mueven los tipitos
	vector<Personaje*> personajes=this->modelo->devolverTodosLosPersonajes();
	vector<Personaje*>::iterator it = personajes.begin();
			for (; it != personajes.end(); ++it) {
				Personaje* p = (*it);
				double mov_x=p->get_posicion().get_x_exacta();
				double mov_y=p->get_posicion().get_y_exacta();

				//creo mensaje y guardo
				msg_t mensaje;
				mensaje.type = MOVER_PERSONAJE;
				mensaje.paramDouble1 = mov_x;
				mensaje.paramDouble2 = mov_y;
				mensaje.paramInt1 = p->getId();

				this->agregarMensaje(mensaje);
				//Para todos los clientes



			}
}
