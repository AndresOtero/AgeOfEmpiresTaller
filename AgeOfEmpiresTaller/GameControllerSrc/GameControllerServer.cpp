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

void GameControllerServer::agregarCliente(string name,string tipo, SDL_mutex *mutex){
	ObjetoMapa* obj=this->juego->tipos[tipo];
	Personaje* personaje =new Personaje(obj);
	personaje->setNombreJugador(name);
	int id =this->modelo->crearPersonajeServer(personaje);

	//seteo mensaje
	msg_t mensaje;
	mensaje.type = LOGIN;
	memcpy(mensaje.paramNombre,string_to_char_array(name),sizeof(mensaje.paramNombre));
	mensaje.paramInt1 = id;
	mensaje.paramDouble1 = personaje->get_posicion().get_x_exacta();
	mensaje.paramDouble2 = personaje->get_posicion().get_y_exacta();

	this->agregarMensaje(mensaje, mutex);
}

void GameControllerServer::desconectar(string Id){
	this->modelo->congelarPersonaje(Id);
	//Congelar en todos
}
void GameControllerServer::reconectar(string Id){
					this->modelo->descongelarPersonaje(Id);
					//Descongelar en todos
			 }
void GameControllerServer::cambiar_destino_personaje(string id, double mov_x,double mov_y){
	this->modelo->cambiar_destino_personaje(id,mov_x,mov_y);
}

queue <msg_t>  GameControllerServer::inicializacion(){
	queue <msg_t> colaInicializacion;
	msg_t mapa;
	mapa.type = PARAM_MAPA;
	mapa.paramDouble1 = this->modelo->get_ancho_mapa();
	mapa.paramDouble2 = this->modelo->get_alto_mapa();
	colaInicializacion.push(mapa);

	msg_t conf;
	conf.type = CONFIGURACION;
	conf.paramDouble1 = this->modelo->juego->conf->get_margen_scroll();
	conf.paramDouble2 =  this->modelo->juego->conf->get_vel_personaje();
	colaInicializacion.push(conf);

	vector<Entidad*> entidades= this->modelo->obtenerEntidadesDeInicializacion();
	vector<Entidad*>::iterator it = entidades.begin();
	for (; it != entidades.end(); it++) {
		msg_t entidad;
		Entidad* ent = (*it);
		memcpy(entidad.paramNombre,string_to_char_array(ent->objetoMapa->nombre),sizeof(entidad.paramNombre));
		entidad.paramDouble1 = ent->posicion->getX();
		entidad.paramDouble2 = ent->posicion->getY();

		if (ent->esUnRecurso()){
			int cant = ((Recurso*)ent)->obtenerRecurso();
			entidad.paramInt1 = cant;
			entidad.type = CREAR_RECURSO;
		}else{
			entidad.type = CREAR_ENTIDAD;
		}
		colaInicializacion.push(entidad);

	}
	vector<Personaje*> personajes=this->modelo->devolverTodosLosPersonajes();
	vector<Personaje*>::iterator iter = personajes.begin();
		for (; iter != personajes.end(); iter++) {
			msg_t msg_crear_personaje;
			Personaje* personaje = (*iter);
			msg_crear_personaje.type=NUEVO_PERSONAJE;
			Posicion pos=personaje->get_posicion();
			memcpy(msg_crear_personaje.paramNombre,string_to_char_array(personaje->getNombreJugador()),sizeof(msg_crear_personaje.paramNombre));
			msg_crear_personaje.paramDouble1=pos.get_x_exacta();
			msg_crear_personaje.paramDouble2=pos.get_y_exacta();
			colaInicializacion.push(msg_crear_personaje);
			if(personaje->estaCongelado()){
				msg_t mensajeDesconexion;
				mensajeDesconexion.type = QUIT;
				memcpy(mensajeDesconexion.paramNombre,string_to_char_array(personaje->getNombreJugador()),sizeof(mensajeDesconexion.paramNombre));
				colaInicializacion.push(mensajeDesconexion);
			}
		}
	return colaInicializacion;

}

void GameControllerServer::generarRecursoRandom(SDL_mutex *mutex){
	Posicion pos = this->modelo->mapa->posicionVacia();
	recurso_t tipo = this->modelo->generarRecursoRandom(pos);
	//creacion mensaje si creo recurso
	if (tipo.cantidad > 0) {
		msg_t mensaje;
		mensaje.type = CREAR_RECURSO;
		memcpy(mensaje.paramNombre,string_to_char_array(tipo.nombre),sizeof(mensaje.paramNombre));
		mensaje.paramInt1 = tipo.cantidad;
		mensaje.paramDouble1 = pos.getX();
		mensaje.paramDouble2 = pos.getY();
		this->agregarMensaje(mensaje, mutex);
	}
}


void GameControllerServer::agregarEntidad(string nombre,int x, int y, int cant, SDL_mutex *mutex){
	this->agregarEntidad(nombre,x,y,cant, mutex);
	msg_t mensaje;
	mensaje.type=CREAR_ENTIDAD;
	memcpy(mensaje.paramNombre,string_to_char_array(nombre),sizeof(mensaje.paramNombre));
	mensaje.paramInt1 = cant;
	mensaje.paramDouble1 = x;
	mensaje.paramDouble2 = y;
	this->agregarMensaje(mensaje, mutex);

}
void GameControllerServer::actualizar(SDL_mutex *mutex) {
	this->modelo->actualizarMapa();		//mueven los tipitos
	vector<Personaje*> personajes = this->modelo->devolverTodosLosPersonajes();
	vector<Personaje*>::iterator it = personajes.begin();
	for (; it != personajes.end(); ++it) {
		Personaje* p = (*it);
		if (p->seMovio()) {
			double mov_x = p->get_posicion().get_x_exacta();
			double mov_y = p->get_posicion().get_y_exacta();

			//creo mensaje y guardo
			msg_t mensaje;
			mensaje.type = MOVER_PERSONAJE;
			memcpy(mensaje.paramNombre,string_to_char_array(p->getNombreJugador()),	sizeof(mensaje.paramNombre));
			mensaje.paramDouble1 = mov_x;
			mensaje.paramDouble2 = mov_y;

			this->agregarMensaje(mensaje, mutex);
			//printf("Encola: mover %d %g %g \n", mensaje.type,mensaje.paramDouble1, mensaje.paramDouble2);

			//solucion fea pero con poca implementacion
			//de la recoleccion de recursos
			//tiene el mismo nombre de jugador que p
			int oro = p->recursosJugador()->cantOro();
			int piedra = p->recursosJugador()->cantMadera();
			int madera = p->recursosJugador()->cantPiedra();
			if ((oro!=0)||(madera!=0)||(piedra!=0)){

			//printf("Recolecto %d,%d,%d \n",p->recursosJugador()->cantOro(),p->recursosJugador()->cantMadera(),p->recursosJugador()->cantPiedra());
				mensaje.type = ACTUALIZACION_RECURSOS;
				mensaje.paramInt1 = p->recursosJugador()->cantOro();
				mensaje.paramDouble1 = p->recursosJugador()->cantMadera();
				mensaje.paramDouble2 = p->recursosJugador()->cantPiedra();
				this->agregarMensaje(mensaje, mutex);
				p->recursosJugador()->reset();//reset, el q acumula es el jugador
			}
		}
	}
}

bool GameControllerServer::hayEventos(SDL_mutex *mutex){
	//printf("Entro aca \n \n");
	plog::init(plog::warning, "Log.txt");
	if (SDL_LockMutex(mutex) == 0) {

		//printf((this->cola.empty())? "Es NUll \n" : "No es Null\n");

		SDL_UnlockMutex(mutex);

		return (!this->cola.empty());
	} else {
	  LOG_WARNING<< "Couldn't lock mutex\n";
	  return false;
	}

}

msg_t GameControllerServer::sacarMensaje(SDL_mutex *mutex){
	plog::init(plog::error, "Log.txt");
	msg_t mensaje;
	if (SDL_LockMutex(mutex) == 0) {

		mensaje = this->cola.front();
		this->cola.pop();
		SDL_UnlockMutex(mutex);
		return mensaje;
	} else {
		LOG_ERROR << "Couldn't lock mutex\n";
	  return mensaje;
	}

}

void GameControllerServer::agregarMensaje(msg_t mensaje,SDL_mutex *mutex){
	plog::init(plog::error, "Log.txt");
	if (SDL_LockMutex(mutex) == 0) {
		this->cola.push(mensaje);
		SDL_UnlockMutex(mutex);
	} else {
		LOG_ERROR << "Couldn't lock mutex\n";
	}

}
