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

void GameControllerServer::cambiar_destino_personaje(Id id, double mov_x,double mov_y){
	this->modelo->cambiar_destino_personaje(id,mov_x,mov_y);
}
void GameControllerServer::atacar(Id idAtacante, Id idAtacado){
	this->modelo->atacarServer(idAtacante,idAtacado);
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

		//problema no puede pasar los id de los recursos
		if (!ent->esUnRecurso()){
			entidad.type = CREAR_ENTIDAD;
			entidad.paramInt1 = ent->getId();
			colaInicializacion.push(entidad);

		}else{
			int cant = ((Recurso*)ent)->obtenerRecurso();
			entidad.paramInt1 = cant;
			entidad.type = CREAR_RECURSO;
			colaInicializacion.push(entidad);
			entidad.type = SET_ID_RECURSO;
			entidad.paramInt1 = ent->getId();
			colaInicializacion.push(entidad);

		}


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
			msg_crear_personaje.paramInt1=personaje->getId();
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
		mensaje.type = SET_ID_RECURSO;
		mensaje.paramInt1 = this->modelo->mapa->entidad_celda(pos.get_x_exacta(),pos.get_y_exacta())->getId();
		this->agregarMensaje(mensaje, mutex);

	}
}

void GameControllerServer::setAccionEntidad(int id_personaje,int id_recurso){
	Personaje * personaje = this->modelo->get_Personaje_Por_Id(id_personaje);
	Entidad * entidad = this->modelo->buscarEntidad(id_recurso);
	if (entidad != NULL){
		personaje->setAccion(entidad);
	}

}

/*void GameControllerServer::setRecoleccion(int id_personaje,int x , int y){
	Entidad * entidad = this->modelo->mapa->entidad_celda(x,y);
	if (entidad==NULL)
		return;
	Personaje * personaje = this->modelo->get_Personaje_Por_Id(id_personaje);
	personaje->setAccion(entidad);
	printf("%d\n",((Recurso *) entidad)->obtenerRecurso());
}*/

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
		if(p->esta_atacando()){
			printf("Esta atacando\n");
			p->set_destino_al_ataque();
		}
		if (p->seMovio()) {
			double mov_x = p->get_posicion().get_x_exacta();
			double mov_y = p->get_posicion().get_y_exacta();

			//creo mensaje y guardo
			msg_t mensaje;
			mensaje.type = MOVER_PERSONAJE;
			memcpy(mensaje.paramNombre,string_to_char_array(p->getNombreJugador()),	sizeof(mensaje.paramNombre));
			mensaje.paramDouble1 = mov_x;
			mensaje.paramDouble2 = mov_y;
			mensaje.paramInt1 = p->getId();
			this->agregarMensaje(mensaje, mutex);



		}
		if (p->tieneRecursos()){
			//solucion que soluciona no tener que tener una lista con la info de los jugadores
			msg_t mensaje;
			mensaje.type = ACTUALIZACION_RECURSOS;
			memcpy(mensaje.paramNombre,string_to_char_array(p->getNombreJugador()),sizeof(mensaje.paramNombre));
			mensaje.paramInt1 = p->recursosJugador()->cantOro();
			mensaje.paramDouble1 = p->recursosJugador()->cantMadera();
			mensaje.paramDouble2 = p->recursosJugador()->cantPiedra();
			this->agregarMensaje(mensaje, mutex);
			p->recursosJugador()->reset();
			//reset, el q acumula es el jugador
			Recurso * recurso = (Recurso *)p->get_objetivo();
			if (recurso->seAcabo()){
				this->modelo->eliminarEntidad(recurso);
				p->terminarAccion();
				mensaje.type = ELIMINAR_ENTIDAD;
				mensaje.paramInt1 = recurso->getId();
				this->agregarMensaje(mensaje, mutex);
				//si el recurso se acabo lo saco y mando mensaje
			}
		}
		}
}

bool GameControllerServer::hayEventos(SDL_mutex *mutex){
	bool result;
	bool paso = false;

	while (!paso){
		if (SDL_LockMutex(mutex) == 0) {
			result = !this->cola.empty();
			SDL_UnlockMutex(mutex);
			paso = true;
		}
	}
	return result;
}

msg_t GameControllerServer::sacarMensaje(SDL_mutex *mutex){
	msg_t mensaje;
	bool paso = false;
	while (!paso){
		if (SDL_LockMutex(mutex) == 0) {
			mensaje = this->cola.front();
			this->cola.pop();
			paso = true;
			SDL_UnlockMutex(mutex);
		}
	}
	return mensaje;
}

void GameControllerServer::agregarMensaje(msg_t mensaje,SDL_mutex *mutex){
	bool paso = false;
	while (!paso){
		if (SDL_LockMutex(mutex) == 0) {
			this->cola.push(mensaje);
			SDL_UnlockMutex(mutex);
			paso= true;
		}
	}

}
