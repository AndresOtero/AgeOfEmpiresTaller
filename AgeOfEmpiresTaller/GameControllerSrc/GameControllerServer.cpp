/*
 * GameControllerServer.cpp
 *
 *  Created on: 21 de oct. de 2015
 *      Author: andres
 */

#include "GameControllerServer.h"
#define CANTIDAD_PERSONAJES_INICIALES 4
#define MAX_RECURSOS 20

char* GameControllerServer::string_to_char_array(string str) {
	int str_size = str.size();
	char charArray[PARAM_STRING_LEN];
	for (int a = 0; a <= str_size; a++) {
		charArray[a] = str[a];
	}
	return charArray;
}

GameControllerServer::GameControllerServer() {
}
GameControllerServer::~GameControllerServer() {
}

void GameControllerServer::agregarCliente(string name, string tipo,
		SDL_mutex *mutex) {
	ObjetoMapa* obj = this->juego->tipos[tipo];
	Personaje* personaje = new Personaje(obj);
	personaje->setNombreJugador(name);
	int id = this->modelo->crearPersonajeServer(personaje);

	//seteo mensaje
	msg_t mensaje;
	mensaje.type = LOGIN;
	memcpy(mensaje.paramTipo, string_to_char_array(tipo),
			sizeof(mensaje.paramTipo));
	memcpy(mensaje.paramNombre, string_to_char_array(name),
			sizeof(mensaje.paramNombre));
	mensaje.paramInt1 = id;
	mensaje.paramDouble1 = personaje->get_posicion().get_x_exacta();
	mensaje.paramDouble2 = personaje->get_posicion().get_y_exacta();

	this->agregarMensaje(mensaje, mutex);
}

void GameControllerServer::desconectar(string Id) {
	this->modelo->congelarPersonaje(Id);
	//Congelar en todos
}
void GameControllerServer::reconectar(string Id) {
	this->modelo->descongelarPersonaje(Id);
	//Descongelar en todos
}

void GameControllerServer::cambiar_destino_personaje(Id id, double mov_x,
		double mov_y) {
	this->modelo->finalizarAccion(id);
	this->modelo->cambiar_destino_personaje(id, mov_x, mov_y);
}
void GameControllerServer::atacar(Id idAtacante, Id idAtacado) {
	this->modelo->atacarServer(idAtacante, idAtacado);
}

void GameControllerServer::crearEdificio(string nombre, int id_constructor,
		int x, int y, SDL_mutex *mutex) {
	int id = this->modelo->crearEdificio(nombre, x, y);
	if (id != EDIFICIO_SUPERPUESTO) {
		msg_t msg;
		msg.type = CREAR_ENTIDAD;
		memcpy(msg.paramNombre, string_to_char_array(nombre),
				sizeof(msg.paramNombre));
		msg.paramInt1 = id;
		msg.paramDouble1 = x;
		msg.paramDouble2 = y;
		this->agregarMensaje(msg, mutex);
		this->setAccionEntidad(id_constructor, id);
	} else {
		//no pudo crear
	}

}
void GameControllerServer::crearPersonajeEdificio(string name, string tipo,
		Id id_edificio, SDL_mutex *mutex) {
	ObjetoMapa* obj = this->juego->tipos[tipo];
	Personaje* personaje = new Personaje(obj);
	personaje->setNombreJugador(name);
	int id = this->modelo->crearPersonajeServerEdificio(personaje, id_edificio);

	//seteo mensaje
	msg_t mensaje;
	mensaje.type = NUEVO_PERSONAJE;
	memcpy(mensaje.paramTipo, string_to_char_array(tipo),
			sizeof(mensaje.paramTipo));
	memcpy(mensaje.paramNombre, string_to_char_array(name),
			sizeof(mensaje.paramNombre));
	mensaje.paramInt1 = id;
	mensaje.paramDouble1 = personaje->get_posicion().get_x_exacta();
	mensaje.paramDouble2 = personaje->get_posicion().get_y_exacta();

	this->agregarMensaje(mensaje, mutex);
}

void GameControllerServer::crearPersonajeHeroe(string name, string tipo,
		Id id_edificio, SDL_mutex *mutex) {
	ObjetoMapa* obj = this->juego->tipos[tipo];
	Personaje* personaje = new Personaje(obj);
	personaje->esHeroe = true;
	personaje->setNombreJugador(name);
	int id = this->modelo->crearPersonajeServerEdificio(personaje, id_edificio);

	//seteo mensaje
	msg_t mensaje;
	mensaje.type = NUEVO_PERSONAJE;
	memcpy(mensaje.paramTipo, string_to_char_array(tipo),
			sizeof(mensaje.paramTipo));
	memcpy(mensaje.paramNombre, string_to_char_array(name),
			sizeof(mensaje.paramNombre));
	mensaje.paramInt1 = id;
	mensaje.paramDouble1 = personaje->get_posicion().get_x_exacta();
	mensaje.paramDouble2 = personaje->get_posicion().get_y_exacta();

	this->agregarMensaje(mensaje, mutex);
}

void GameControllerServer::crearBandera(string name, string raza, int idCentro,
		SDL_mutex *mutex) {

	string tipo;
	if (raza == "Elfo") {
		tipo = "banderaElfos";
	} else if (raza == "Hobbit") {
		tipo = "banderaHobbit";
	} else if (raza == "Humano") {
		tipo = "banderaHumano";
	} else
		tipo = "banderaMordor";

	ObjetoMapa* obj = this->juego->tipos[tipo];
	obj->raza = raza;

	Entidad* bandera = new Entidad(obj);

	bandera->setEsUnaBandera();

	int id = this->modelo->crearBandera(bandera, idCentro);

	printf("path de la bandera: %s\n", bandera->objetoMapa->imagen.c_str());

	//seteo mensaje
	msg_t mensaje;
	mensaje.type = CREAR_ENTIDAD_CONSTRUIDA;
	memcpy(mensaje.paramNombre,
			string_to_char_array(bandera->objetoMapa->nombre),
			sizeof(mensaje.paramNombre));
	mensaje.paramInt1 = id;
	mensaje.paramDouble1 = bandera->get_posicion().get_x_exacta();
	mensaje.paramDouble2 = bandera->get_posicion().get_y_exacta();

	this->agregarMensaje(mensaje, mutex);
}

queue<msg_t> GameControllerServer::inicializacion() {
	queue<msg_t> colaInicializacion;
	msg_t mapa;
	mapa.type = PARAM_MAPA;
	mapa.paramDouble1 = this->modelo->get_ancho_mapa();
	mapa.paramDouble2 = this->modelo->get_alto_mapa();
	colaInicializacion.push(mapa);

	msg_t conf;
	conf.type = CONFIGURACION;
	conf.paramDouble1 = this->modelo->juego->conf->get_margen_scroll();
	conf.paramDouble2 = this->modelo->juego->conf->get_vel_personaje();
	colaInicializacion.push(conf);

	vector<Entidad*> entidades =
			this->modelo->obtenerEntidadesDeInicializacion();
	vector<Entidad*>::iterator it = entidades.begin();
	for (; it != entidades.end(); it++) {
		msg_t entidad;
		Entidad* ent = (*it);
		memcpy(entidad.paramNombre,
				string_to_char_array(ent->objetoMapa->nombre),
				sizeof(entidad.paramNombre));
		entidad.paramDouble1 = ent->posicion->getX();
		entidad.paramDouble2 = ent->posicion->getY();

		//problema no puede pasar los id de los recursos
		if (!ent->esUnRecurso()) {
			entidad.type = CREAR_ENTIDAD_CONSTRUIDA;
			entidad.paramInt1 = ent->getId();
			colaInicializacion.push(entidad);

		} else {
			int cant = ((Recurso*) ent)->obtenerRecurso();
			entidad.paramInt1 = cant;
			entidad.type = CREAR_RECURSO;
			colaInicializacion.push(entidad);
			entidad.type = SET_ID_RECURSO;
			entidad.paramInt1 = ent->getId();
			colaInicializacion.push(entidad);

		}

	}
	vector<Personaje*> personajes = this->modelo->devolverTodosLosPersonajes();
	vector<Personaje*>::iterator iter = personajes.begin();
	for (; iter != personajes.end(); iter++) {
		msg_t msg_crear_personaje;
		Personaje* personaje = (*iter);
		msg_crear_personaje.type = NUEVO_PERSONAJE;
		Posicion pos = personaje->get_posicion();
		memcpy(msg_crear_personaje.paramTipo,
				string_to_char_array(personaje->objetoMapa->nombre),
				sizeof(msg_crear_personaje.paramTipo));
		memcpy(msg_crear_personaje.paramNombre,
				string_to_char_array(personaje->getNombreJugador()),
				sizeof(msg_crear_personaje.paramNombre));
		msg_crear_personaje.paramDouble1 = pos.get_x_exacta();
		msg_crear_personaje.paramDouble2 = pos.get_y_exacta();
		msg_crear_personaje.paramInt1 = personaje->getId();
		colaInicializacion.push(msg_crear_personaje);
		if (personaje->estaCongelado()) {
			msg_t mensajeDesconexion;
			mensajeDesconexion.type = QUIT;
			memcpy(mensajeDesconexion.paramNombre,
					string_to_char_array(personaje->getNombreJugador()),
					sizeof(mensajeDesconexion.paramNombre));
			colaInicializacion.push(mensajeDesconexion);
		}
	}

	return colaInicializacion;

}

void GameControllerServer::generarRecursoRandom(SDL_mutex *mutex) {

	for (int i = 0; i <= MAX_RECURSOS; i++) {
		Posicion pos = this->modelo->mapa->posicionVacia();
		recurso_t tipo = this->modelo->generarRecursoRandom(pos);
		//creacion mensaje si creo recurso
		if (tipo.cantidad > 0) {
			msg_t mensaje;
			mensaje.type = CREAR_RECURSO;
			memcpy(mensaje.paramNombre, string_to_char_array(tipo.nombre),
					sizeof(mensaje.paramNombre));
			mensaje.paramInt1 = tipo.cantidad;
			mensaje.paramDouble1 = pos.getX();
			mensaje.paramDouble2 = pos.getY();
			this->agregarMensaje(mensaje, mutex);
			mensaje.type = SET_ID_RECURSO;
			mensaje.paramInt1 = this->modelo->mapa->entidad_celda(
					pos.get_x_exacta(), pos.get_y_exacta())->getId();
			this->agregarMensaje(mensaje, mutex);
		}
	}
}

void GameControllerServer::setAccionEntidad(int id_personaje, int id_recurso) {
	//podria reusar para construir esto TODO
	Personaje * personaje = this->modelo->get_Personaje_Por_Id(id_personaje);
	Entidad * entidad = this->modelo->buscarEntidad(id_recurso);
	if (entidad != NULL) {
		personaje->setAccion(entidad);
	}

}

void GameControllerServer::agregarEntidad(string nombre, int x, int y, int cant,
		SDL_mutex *mutex) {
	this->agregarEntidad(nombre, x, y, cant, mutex);
	msg_t mensaje;
	mensaje.type = CREAR_ENTIDAD;
	memcpy(mensaje.paramNombre, string_to_char_array(nombre),
			sizeof(mensaje.paramNombre));
	mensaje.paramInt1 = cant;
	mensaje.paramDouble1 = x;
	mensaje.paramDouble2 = y;
	this->agregarMensaje(mensaje, mutex);

}
void GameControllerServer::actualizar(SDL_mutex *mutex) {
	//printf("Actualizar\n");
	this->modelo->actualizarMapa();		//mueven los tipitos
	//printf("Termino de actualizar\n");
	vector<Personaje*> personajes = this->modelo->devolverTodosLosPersonajes();
	vector<Personaje*>::iterator it = personajes.begin();
	for (; it != personajes.end(); ++it) {
		Personaje* p = (*it);
		if (p->esta_atacando()) {
			//printf("Esta atacando\n");
			p->set_destino_al_ataque();
			if (p->es_adyacente_al_atacado()) {
				if (!p->estaAtacandoCliente()) {
					msg_t msg;
					msg.type = EMPEZAR_ACCION;
					msg.paramInt1 = p->getId();
					this->agregarMensaje(msg, mutex);
				}
				if (p->contar()) {

					p->ejecutar_ataque();
					//printf("Ataca\n");
					msg_t mensaje;
					mensaje.type = ATACAR;
					memcpy(mensaje.paramNombre,
							string_to_char_array(p->getNombreJugador()),
							sizeof(mensaje.paramNombre));
					mensaje.paramInt1 = p->getId();
					mensaje.paramDouble1 = p->get_atacado_id();
					mensaje.paramDouble2 = p->danioInfringido();
					this->agregarMensaje(mensaje, mutex);
				}
			}
		}
		if (p->seMovio()) {
			double mov_x = p->get_posicion().get_x_exacta();
			double mov_y = p->get_posicion().get_y_exacta();

			//creo mensaje y guardo
			msg_t mensaje;
			mensaje.type = MOVER_PERSONAJE;
			memcpy(mensaje.paramNombre,
					string_to_char_array(p->getNombreJugador()),
					sizeof(mensaje.paramNombre));
			mensaje.paramDouble1 = mov_x;
			mensaje.paramDouble2 = mov_y;
			mensaje.paramInt1 = p->getId();
			this->agregarMensaje(mensaje, mutex);

		}
		if (p->esta_recolectando()) {
			p->set_destino(p->get_objetivo()->get_posicion());
			if (p->esAdyacente(p->get_objetivo())) {
				if (!p->estaAtacandoCliente()) {
					msg_t msg;
					msg.type = EMPEZAR_ACCION;
					msg.paramInt1 = p->getId();
					this->agregarMensaje(msg, mutex);
				}
				if (p->contar()) {
					((Recurso *) p->get_objetivo())->recolectar(
							p->recursosJugador(), p->getRecoleccion());
					//solucion para no tener que tener una lista con la info de los jugadores
					msg_t mensaje;
					mensaje.type = ACTUALIZACION_RECURSOS;
					memcpy(mensaje.paramNombre,
							string_to_char_array(p->getNombreJugador()),
							sizeof(mensaje.paramNombre));
					mensaje.paramInt1 = p->getId();
					mensaje.paramDouble1 = p->getRecoleccion();
					mensaje.paramDouble2 =
							((Recurso *) p->get_objetivo())->getId();
					this->agregarMensaje(mensaje, mutex);
					p->recursosJugador()->reset();
					//reset, el q acumula es el jugador
					//puede explotar con muchos recolectando
					Recurso * recurso = (Recurso *) p->get_objetivo();
					if (recurso->seAcabo()) {
						mensaje.type = ELIMINAR_ENTIDAD;
						mensaje.paramInt1 = recurso->getId();
						this->agregarMensaje(mensaje, mutex);
						vector<msg_t> terminados = this->modelo->eliminarEntidad(recurso);
						vector<msg_t>::iterator it;
						for (it = terminados.begin();it!=terminados.end();it++){
							this->agregarMensaje(*it,mutex);
						}
						/*msg_t msg;
						msg.type = TERMINAR_ACCION;
						msg.paramInt1 = p->getId();
						this->agregarMensaje(msg, mutex);*/
						//si el recurso se acabo lo saco y mando mensaje
					}

				}
			}
		}
		if (p->esta_contruyendo()) {
			p->set_destino(p->get_objetivo()->get_posicion());
			if (p->esAdyacente(p->get_objetivo())) {
				if (!p->estaAtacandoCliente()) {
					msg_t msg;
					msg.type = EMPEZAR_ACCION;
					msg.paramInt1 = p->getId();
					this->agregarMensaje(msg, mutex);
				}
				if (p->contar()) {
					msg_t mensaje;
					mensaje.type = CONSTRUIR;
					mensaje.paramInt1 = p->getId();
					mensaje.paramDouble1 = p->get_objetivo()->getId();
					int construyo = p->get_objetivo()->construir(
							p->get_construccion());
					mensaje.paramDouble2 = construyo;
					this->agregarMensaje(mensaje, mutex);
					if (p->get_objetivo()->estaConstruida()) {
						vector<msg_t> terminados = modelo->terminarConstruccion(p->get_objetivo()->getId());
						vector<msg_t>::iterator it;
						for (it = terminados.begin(); it != terminados.end();
								it++) {
							this->agregarMensaje(*it, mutex);
						}
						//tendria q mandarle a todos los tipitos q dejen de atacar
						//hacer que todos los tipitos paren
						//this->modelo->terminarConstruccion(p->get_objetivo());

					}
				}
			}
		}

		if (p->esta_atacando()) {

			if (!p->get_atacado()->esta_vivo()) {
				if (this->objetivo == FLAG) {

					if (p->get_atacado()->esBandera()) {
						capturaBandera(p, p->get_atacado()->get_raza(), mutex);
					}
				} else if (this->objetivo == KING) {
					if (p->get_atacado()->esUnHeroe()) {
						msg_t mensajeHeroe;
						mensajeHeroe.type = ELIMINAR_TODOS;

						memcpy(mensajeHeroe.paramTipo,
								string_to_char_array(
										p->get_atacado()->get_raza()),
								sizeof(mensajeHeroe.paramTipo)); //raza que pierde unidades

						this->agregarMensaje(mensajeHeroe, mutex);
					}
				} else if (this->objetivo == KILL_ALL) {
					if (p->get_atacado()->esUnCentroCivio()) {

						msg_t mensajeCentro;
						mensajeCentro.type = ELIMINAR_TODOS;

						memcpy(mensajeCentro.paramTipo,
								string_to_char_array(
										p->get_atacado()->get_raza()),
								sizeof(mensajeCentro.paramTipo)); //raza que pierde unidades

						this->agregarMensaje(mensajeCentro, mutex);

					}
				}
				//printf("Eliminar algo con id %d\n",p->get_atacado()->getId());
				msg_t mensaje;
				mensaje.type = ELIMINAR;
				mensaje.paramInt1 = p->get_atacado()->getId();
				this->agregarMensaje(mensaje, mutex);
				vector<msg_t> terminados = this->modelo->eliminar(p->get_atacado()->getId());
				vector<msg_t>::iterator it;
				for (it = terminados.begin(); it != terminados.end(); it++) {
					this->agregarMensaje(*it, mutex);
				}

				//chequear que si lo q se elimino termino el juego de alguien
			}
		}

	}
	//printf("Termino de procesar los personajes\n");
}

bool GameControllerServer::hayEventos(SDL_mutex *mutex) {
	bool result;
	bool paso = false;

	while (!paso) {
		if (SDL_LockMutex(mutex) == 0) {
			result = !this->cola.empty();
			SDL_UnlockMutex(mutex);
			paso = true;
		}
	}
	return result;
}

msg_t GameControllerServer::sacarMensaje(SDL_mutex *mutex) {
	msg_t mensaje;
	bool paso = false;
	while (!paso) {
		if (SDL_LockMutex(mutex) == 0) {
			mensaje = this->cola.front();
			this->cola.pop();
			paso = true;
			SDL_UnlockMutex(mutex);
		}
	}
	return mensaje;
}
void GameControllerServer::crearCentroCivicoNuevoUser(string raza,
		string NombreJugador, SDL_mutex *mutex) {
	Entidad * entidad = this->modelo->set_CentroCivicoNuevoServer(raza);
	//creo centro civico
	msg_t mensaje;
	mensaje.type = CREAR_ENTIDAD_CONSTRUIDA;
	memcpy(mensaje.paramNombre,
			string_to_char_array(entidad->objetoMapa->nombre),
			sizeof(mensaje.paramNombre));
	mensaje.paramInt1 = entidad->getId();
	mensaje.paramDouble1 = entidad->get_posicion().getX();
	mensaje.paramDouble2 = entidad->get_posicion().getY();
	this->agregarMensaje(mensaje, mutex);

	string tipito;
	ObjetoMapa* tipo = entidad->devolverPersonajesCreables().begin()->second;
	if (tipo->construccion > 0 || tipo->recoleccion > 0) {
		tipito = tipo->nombre;
	} else {
		map<string, ObjetoMapa*>::iterator it =
				entidad->devolverPersonajesCreables().begin();
		it++;
		tipito = it->first;
	}
	for (int i = 0; i < CANTIDAD_PERSONAJES_INICIALES; i++) {
		this->crearPersonajeEdificio(NombreJugador, tipito, entidad->getId(),
				mutex);
	}

	if (this->objetivo == FLAG) {
		this->crearBandera(NombreJugador, raza, entidad->getId(), mutex);
	} else if (this->objetivo == KING) {
		string heroeTipo;
		if (raza == "Elfo") {
			heroeTipo = "arwen";
		} else if (raza == "Hobbit") {
			heroeTipo = "aragon";
		} else if (raza == "Humano") {
			heroeTipo = "king";
		} else
			heroeTipo = "sauron";

		this->crearPersonajeHeroe(NombreJugador, heroeTipo, entidad->getId(),
				mutex);
	}

	msg_t mssg;
	mssg.type = LOGIN;
	memcpy(mssg.paramNombre, string_to_char_array(NombreJugador),
			sizeof(mssg.paramNombre));
	this->agregarMensaje(mssg, mutex);

}

void GameControllerServer::agregarMensaje(msg_t mensaje, SDL_mutex *mutex) {
	bool paso = false;
	while (!paso) {
		if (SDL_LockMutex(mutex) == 0) {
			this->cola.push(mensaje);
			SDL_UnlockMutex(mutex);
			paso = true;
		}
	}

}

void GameControllerServer::capturaBandera(Personaje* personaje_que_captura,
		string razaPerdedora, SDL_mutex *mutex) {
	vector<Personaje*> personajes = this->modelo->devolverTodosLosPersonajes();
	vector<Personaje*>::iterator iter = personajes.begin();
	vector<Personaje*> personajes_a_cambiar;
	for (; iter != personajes.end(); iter++) {
		Personaje* personaje = (*iter);
		printf("Comparo Perdedora:%s , Personaje : %s\n", razaPerdedora.c_str(),
				personaje->get_raza().c_str());
		if (personaje->get_raza() == razaPerdedora) {
			printf("Personaje cambio %d\n", personaje->getId());
			msg_t mensaje_cambiar;
			mensaje_cambiar.type = CAMBIAR_PERSONAJE;
			mensaje_cambiar.paramInt1 = personaje->getId();
			memcpy(mensaje_cambiar.paramNombre,
					string_to_char_array(
							personaje_que_captura->getNombreJugador()),
					sizeof(mensaje_cambiar.paramNombre)); //raza que pierde unidades
			memcpy(mensaje_cambiar.paramTipo,
					string_to_char_array(personaje_que_captura->get_raza()),
					sizeof(mensaje_cambiar.paramTipo)); //raza que pierde unidades
			this->agregarMensaje(mensaje_cambiar, mutex);
			personajes_a_cambiar.push_back(personaje);
			//this->cambiar_personaje(mensaje_cambiar.paramInt1,personaje_que_captura->getNombreJugador(),personaje_que_captura->get_raza() );
		}

	}
	msg_t mensajePierde;
	mensajePierde.type = PIERDE;
	memcpy(mensajePierde.paramNombre, string_to_char_array(razaPerdedora),sizeof(mensajePierde.paramNombre)); //raza que pierde unidades

	this->agregarMensaje(mensajePierde, mutex);

}
void GameControllerServer::cambiar_personaje(int id_personaje, string nombre,
		string raza) { //nombre y raza a la que cambia
	printf("Id personaje %d\n", id_personaje);
	printf("Nombre %s\n", nombre.c_str());
	printf("Raza %s\n", nombre.c_str());
	this->modelo->cambiar_personaje(id_personaje, nombre, raza);
}
