/*
 * Personaje.cpp
 *
 *  Created on: 21 de set. de 2015
 *      Author: andres
 */

#include "Personaje.h"
#define FACTOR_VELOCIDAD 100
#define FACTOR_CONTADOR 5

Personaje::Personaje() {
	this->esHeroe= false;
	this->adyacente = false;
	this->atacando_cliente = false;
	this->objetoMapa = new ObjetoMapa("protagonistaDefault", "img/protagonista/spartan_small.png");
	this->referencia_mapa_x = 5;
	this->referencia_mapa_y = 2;
	this->destino = Posicion(referencia_mapa_x, referencia_mapa_y);
	this->camino = Posicion(referencia_mapa_x, referencia_mapa_y);
	this->objetoMapa->fps = 8; //FPS DEFAULT
	this->velocidad = 0.1;
	this->objetoMapa->delay = 0; //delay default
	this->recursos = new RecursosJugador();
	this->congelado = false;
	this->atacado = NULL;
	this->objetivo = NULL;
}
Personaje::Personaje(ObjetoMapa* objetoMapa) {
	this->esHeroe= false;
	this->adyacente = false;
	this->referencia_mapa_x = 1;
	this->referencia_mapa_y = 1;
	this->destino = Posicion(referencia_mapa_x, referencia_mapa_y);
	this->camino = Posicion(referencia_mapa_x, referencia_mapa_y);
	this->velocidad = float(objetoMapa->velocidad) / FACTOR_VELOCIDAD;
	this->vida = objetoMapa->vida;
	this->fuerza = objetoMapa->fuerza;
	this->armadura = objetoMapa->armadura;
	this->recoleccion = objetoMapa->recoleccion;
	this->construccion = objetoMapa->construccion;
	this->objetoMapa = objetoMapa;
	this->contador_ataque = Contador(objetoMapa->velocidad * FACTOR_CONTADOR);
	this->recursos = new RecursosJugador();
	this->congelado = false;
	this->atacando_cliente = false;
	this->atacado = NULL;
	this->objetivo = NULL;
	this->costo.setCosto(objetoMapa->oro, objetoMapa->madera, objetoMapa->piedra, objetoMapa->comida);
	GeneradorNumeros generar;
	int id = generar.otroID();
	this->id = id;
}
Personaje::Personaje(ObjetoMapa* objetoMapa, int x, int y) {
	this->referencia_mapa_x = x;
	this->referencia_mapa_y = y;
	this->destino = Posicion(referencia_mapa_x, referencia_mapa_y);
	this->camino = Posicion(referencia_mapa_x, referencia_mapa_y);
	this->velocidad = float(objetoMapa->velocidad) / FACTOR_VELOCIDAD;
	this->vida = objetoMapa->vida;
	this->fuerza = objetoMapa->fuerza;
	this->armadura = objetoMapa->armadura;
	this->recoleccion = objetoMapa->recoleccion;
	this->construccion = objetoMapa->construccion;
	this->contador_ataque = Contador(objetoMapa->velocidad * FACTOR_CONTADOR);
	this->objetoMapa = objetoMapa;
	this->recursos = new RecursosJugador();
	this->congelado = false;
	this->costo.setCosto(objetoMapa->oro, objetoMapa->madera, objetoMapa->piedra, objetoMapa->comida);
	this->adyacente = false;
	this->atacando_cliente = false;
	this->atacado = NULL;
	this->objetivo = NULL;
	GeneradorNumeros generar;
	int id = generar.otroID();
	this->id = id;
}

dibujo_t Personaje::dibujar() {
	return dibujo_actual;
}
DatosSeleccionado Personaje::mostrar_contenido() {
	DatosSeleccionado datos;
	datos.setTipo(PERSONAJE);
	datos.setNombre(this->objetoMapa->nombre);
	datos.setJugador(this->nombreJugador);
	datos.setVida(&this->vida, this->objetoMapa->vida);
	return datos;
}
void Personaje::set_posicion(Posicion pos) {
	this->referencia_mapa_x = pos.get_x_exacta();
	this->referencia_mapa_y = pos.get_y_exacta();
	this->destino = pos;
	this->camino = pos;
}

Posicion Personaje::get_posicion() {
	return Posicion(referencia_mapa_x, referencia_mapa_y);
}
void Personaje::set_destino(Posicion destino) {
	this->destino = destino;
}
void Personaje::set_camino(Posicion camino) {
	this->camino = camino;
}
Posicion Personaje::get_destino() {
	return destino;
}
Posicion Personaje::get_camino() {
	return camino;
}
void Personaje::mover() {
	double x = camino.get_x_exacta();
	double y = camino.get_y_exacta();
	double delta_x = (double) (x - referencia_mapa_x);
	double delta_y = (double) (y - referencia_mapa_y);
	double distancia = sqrt(delta_x * delta_x + delta_y * delta_y);
	if (distancia != 0) {
		se_movio = true;
		this->atacando_cliente = false;

		if (distancia < velocidad) {
			distancia = velocidad;
		}
		if ((sqrt(delta_x * delta_x) > distancia) && (sqrt(delta_x * delta_x) < distancia)) {

			this->referencia_mapa_x = x;
		}
		if ((sqrt(delta_y * delta_y) > distancia) && ((sqrt(delta_y * delta_y) < distancia))) {
			this->referencia_mapa_y = y;
		}
		double des_x = (velocidad * delta_x) / distancia;
		double des_y = (velocidad * delta_y) / distancia;

		this->referencia_mapa_x += des_x;
		this->referencia_mapa_y += des_y;
		dibujo_anterior = dibujo_actual;
		dibujo_actual = dibujo_esta_moviendo;
	} else {
		se_movio = false;
		if (!this->atacando_cliente) {
			dibujo_anterior = dibujo_actual;
			dibujo_actual = dibujo_esta_quieto;
		} else {
			dibujo_anterior = dibujo_actual;
			dibujo_actual = dibujo_atacando;
		}
	}

}
msg_t Personaje::interactuar(Personaje* otro_personaje) {
	msg_t mensaje;
	if (this->getNombreJugador() != otro_personaje->getNombreJugador()) {
		mensaje.type = ATACAR;
		mensaje.paramInt1 = id;
		mensaje.paramDouble1 = otro_personaje->getId();
		return mensaje;
	}
	mensaje.type = KEEPALIVE;
	return mensaje;
}

msg_t Personaje::interactuar(Entidad* otra_entidad) {
	msg_t mensaje;

	//estos datos los tengo que cargar igual en ambos
	mensaje.paramInt1 = id;
	mensaje.paramDouble1 = otra_entidad->getId();
	if (this->get_raza() == otra_entidad->get_raza()) {
		if (this->puedeCrear() && (!otra_entidad->estaConstruida())) {
			mensaje.type = CONSTRUIR;
			return mensaje;
		}
	} else {

		if (otra_entidad->esUnRecurso() && this->puedeRecolectar()) {
			mensaje.type = RECOLECCION_RECURSOS;
			return mensaje;
		} else if (this->puedeAtacar() && (!otra_entidad->esUnRecurso())) { //falta ver q sea del enemigo
			mensaje.type = ATACAR;
			return mensaje;
		}
	}
	printf("No hace nada\n");
	mensaje.type = KEEPALIVE;
	return mensaje;
}
bool Personaje::esAdyacente(Entidad* entidad) {
	if ((this->objetivo == entidad) && (this->adyacente)) {
		return true;
	} else
		this->adyacente = entidad->esAdyacente(this->get_posicion());
	return adyacente;
}
int Personaje::atacar(Atacable* otro_personaje){
	GeneradorNumeros generador;
	int danio;
	//cuanta mas fuerza mas probable que pegue
	if (generador.numeroRandom(0,this->fuerza)!=0){
		//pega la diferencia entre fuerza armadura por su fuerza
		//puede dar o muchisimo o poco
		danio = floor(exp(-generador.numeroRandom(0,otro_personaje->getArmadura()/this->fuerza))*this->fuerza);
	}else{
		danio = 0;
	}
	//printf("Danio %d\n",danio);
	return danio;
}
void Personaje::set_ataque(Atacable* otro_personaje) {
	this->atacado = otro_personaje;
}
void Personaje::dejar_de_atacar() {
	this->destino = this->get_posicion();
	this->atacado = NULL;
	this->objetivo = NULL;
}
int  Personaje::danioInfringido(){
	return atacar(this->atacado);
}
bool Personaje::ejecutar_ataque() {
	if (this->atacado) {
		this->atacado->recibirDanio(this->danioInfringido());
		return true;
	}
	return false;
}
void  Personaje::recibirDanio(int danio){
	int resultado = vida -danio;
	if (resultado <0){
		this->vida = 0;
	}else{
		this->vida = resultado;
	}
}
bool operator==(Personaje &P1, Personaje &P2) {
return (P1.getId() == P2.getId());
}

void Personaje::setAccion(Entidad * entidad) {
if (this->atacado == NULL) {
	objetivo = entidad;
}
}
void Personaje::terminarAccion() {
	this->set_destino(this->get_posicion());
	this->atacando_cliente = false;
	this->atacado = NULL;
	this->objetivo = NULL;
}

RecursosJugador* Personaje::recursosJugador() {
	return recursos;
}
Personaje::~Personaje() {
	delete recursos;
}
void Personaje::set_destino_al_ataque() {
	this->set_destino(this->atacado->get_posicion());
}

bool Personaje::esAdyacente(Posicion pos) {
	return this->get_posicion().es_adyacente(pos);
}
bool Personaje::es_adyacente_al_atacado() {
	return this->atacado->esAdyacente(this->get_posicion());
}
