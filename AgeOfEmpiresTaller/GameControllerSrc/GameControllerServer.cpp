/*
 * GameControllerServer.cpp
 *
 *  Created on: 21 de oct. de 2015
 *      Author: andres
 */

#include "GameControllerServer.h"

char* GameControllerServer::string_to_char_array(string str){
	int str_size = str.size();
	char charArray[PARAM_STRING_LEN];
	for (int a = 0; a <= str_size; a++) {
		charArray[a] = str[a];
	}
	return charArray;
}

GameControllerServer::GameControllerServer() {
	// TODO Auto-generated constructor stub
}
GameControllerServer::~GameControllerServer() {
	// TODO Auto-generated constructor stub
}

void GameControllerServer::agregarCliente(string name,string tipo){
	ObjetoMapa* obj=this->juego->tipos[tipo];
	Personaje* personaje =new Personaje(obj);
	personaje->setNombreJugador(name);
	int id =this->modelo->crearPersonajeServer(personaje);

	//seteo mensaje
	msg_t mensaje;
	mensaje.type = NUEVO_PERSONAJE;
	strcpy(mensaje.paramNombre,string_to_char_array(tipo));
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
void GameControllerServer::cambiar_destino_personaje(string id, double mov_x,double mov_y){
	this->modelo->cambiar_destino_personaje(id,mov_x,mov_y);
}

void GameControllerServer::inicializacion(){
	this->modelo->get_alto_mapa();
	this->modelo->get_ancho_mapa();
	vector<Entidad*> entidades= this->modelo->obtenerEntidadesDeInicializacion();
	vector<Entidad*>::iterator it = entidades.begin();
	for (; it != entidades.end(); ++it) {
		Entidad* ent = (*it);
		string nombre = ent->objetoMapa->nombre;
		int x =ent->posicion->getX();
		int y =ent->posicion->getY();

	}

}
void GameControllerServer::generarRecursoRandom(){
	Posicion pos = this->modelo->mapa->posicionVacia();
	recurso_t tipo = this->modelo->generarRecursoRandom(pos);
	//creacion mensaje si creo recurso
	if (tipo.cantidad > 0) {
		msg_t mensaje;
		mensaje.type = CREAR_RECURSO;
		//
		//strcpy funciona???
		strcpy(mensaje.paramNombre, string_to_char_array(tipo.nombre));
		mensaje.paramInt1 = tipo.cantidad;
		mensaje.paramDouble1 = pos.getX();
		mensaje.paramDouble2 = pos.getY();
		this->agregarMensaje(mensaje);
	}
}


void GameControllerServer::agregarEntidad(string nombre,int x, int y, int cant){
	this->agregarEntidad(nombre,x,y,cant);
	msg_t mensaje;
	mensaje.type=CREAR_ENTIDAD;
	strcpy(mensaje.paramNombre,string_to_char_array(nombre));
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
				strcpy(mensaje.paramNombre,string_to_char_array(p->getNombreJugador()));
				mensaje.paramDouble1 = mov_x;
				mensaje.paramDouble2 = mov_y;


				this->agregarMensaje(mensaje);
				//Para todos los clientes



			}
}
