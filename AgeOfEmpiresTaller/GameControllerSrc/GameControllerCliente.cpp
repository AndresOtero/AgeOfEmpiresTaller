/*
dibu * GameControllerCliente.cpp
 *
 *  Created on: 21 de oct. de 2015
 *      Author: andres
 */

#include "GameControllerCliente.h"

char* GameControllerCliente::string_to_char_array(string str){
	int str_size = str.size();
	char charArray[PARAM_STRING_LEN];
	for (int a = 0; a <= str_size; a++) {
		charArray[a] = str[a];
	}
	return charArray;
}

GameControllerCliente::GameControllerCliente() {
}


GameControllerCliente::~GameControllerCliente() {
}
string GameControllerCliente::nombreJugador() {
	return this->juego->escenario->jugador->getNombre();
}
bool GameControllerCliente::esNombre(char* nombre) {
	return (!this->juego->escenario->jugador->getNombre().compare(nombre));
}
string GameControllerCliente::ipJugador() {
	return this->juego->escenario->jugador->getIp();
}


void GameControllerCliente::cambiar_destino_personaje(Id id, double mov_x,double mov_y){

	msg_t mensaje;

	mensaje.type = MOVER_PERSONAJE;

	mensaje.paramDouble1 = mov_x;
	mensaje.paramDouble2 = mov_y;
	mensaje.paramInt1=id;
	this->agregarMensaje(mensaje);

}

void GameControllerCliente::eliminarEntidad(int id){
	this->modelo->eliminarEntidadPorID(id);
}
void GameControllerCliente::eliminar(int id){
	this->modelo->eliminar(id);
}
void GameControllerCliente::mover_personaje(Id id,double mov_x,double mov_y){
	this->modelo->cambiar_destino_personaje(id,mov_x,mov_y);
}
void GameControllerCliente::ataque(Id idAtacado,int danio){
	//aca crasheaba mal
	Personaje* p=this->modelo->get_Personaje_Por_Id(idAtacado);
	if (p){
		p->recibirDanio(danio);
	}else{
		Entidad * entidad = this->modelo->buscarEntidad(idAtacado);
		//no chequeo q sea null porque deberia existir
		entidad->recibirDanio(danio);
	}

}

void GameControllerCliente::interactuar(Personaje* personaje,Posicion p){
	//si no esta en rango no puede hacer nada
	if(this->modelo->afueraDelMapa(p.getX(),p.getY())){
		return;
	}
	Personaje* otro_personaje=this->modelo->devolverPersonaje(p.getX(),p.getY());
	Entidad * otra_entidad = this->modelo->mapa->entidad_celda(p.getX(),p.getY());
	if(otro_personaje!=NULL){
		msg_t mensaje=personaje->interactuar(otro_personaje);
		this->agregarMensaje(mensaje);
		return;
	}

	if (otra_entidad != NULL) {
		msg_t msg = personaje->interactuar(otra_entidad);
		this->agregarMensaje(msg);
		return;
	}
}
void GameControllerCliente::eliminar_personaje(Id id){
	this->modelo->eliminar_personaje_por_Id(id);
}
void GameControllerCliente::setMapa(int ancho, int largo){
	this->modelo->setMapa(largo,ancho);
}

void GameControllerCliente::setId(double x, double y, int id){
	Entidad* entidad = this->modelo->mapa->entidad_celda(floor(x),floor(y));
	if (entidad!=NULL){
		entidad->setId(id);
	}
}

void GameControllerCliente::conectarCliente(string name,string str, int x,int y,dibujo_t dibujo,int id){
	ObjetoMapa* obj= this->juego->tipos[str];

	Personaje* personaje =new Personaje(obj,x,y);
	personaje->setNombreJugador(name);
	personaje->setDibujo(dibujo);
	personaje->setId(id);
	this->modelo->agregarPersonajeCliente(personaje);


}

void GameControllerCliente::agregarEntidad(string nombre,int x, int y, int cant){
	this->modelo->agregarEntidad(nombre,x,y,cant);
}
void GameControllerCliente::acutalizarRecursos(int oro, int madera, int piedra){
	this->modelo->actualizarRecursos(oro,madera,piedra);
}
void GameControllerCliente::desconectar(string id){
	this->modelo->congelarPersonaje(id);
}

void GameControllerCliente::reconectar(string id){
	this->modelo->descongelarPersonaje(id);
}


bool GameControllerCliente::hayEventos(){
	return (!this->cola.empty());
}
msg_t GameControllerCliente::sacarMensaje(){
	msg_t mensaje = this->cola.front();
	this->cola.pop();
	return mensaje;
}
void GameControllerCliente::agregarMensaje(msg_t mensaje){
	this->cola.push(mensaje);
}
