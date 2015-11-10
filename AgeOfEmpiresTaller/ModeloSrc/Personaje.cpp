/*
 * Personaje.cpp
 *
 *  Created on: 21 de set. de 2015
 *      Author: andres
 */

#include "Personaje.h"
#define FACTOR_VELOCIDAD 100
#define FACTOR_CONTADOR 10


Personaje::Personaje(){
	this->objetoMapa = new ObjetoMapa("protagonistaDefault", "img/protagonista/spartan_small.png");
	this->referencia_mapa_x=5;
	this->referencia_mapa_y=2;
	this->destino=Posicion(referencia_mapa_x,referencia_mapa_y);
	this->camino=Posicion(referencia_mapa_x,referencia_mapa_y);
	this->objetoMapa->fps = 8; //FPS DEFAULT
	this->velocidad=0.1;
	this->objetoMapa->delay = 0; //delay default
	this->dibujo = 0;
	this->recursos = new RecursosJugador();
	this->congelado=false;
	this->atacado=NULL;
	this->objetivo=NULL;
}
Personaje::Personaje(ObjetoMapa* objetoMapa){
	this->referencia_mapa_x=1;
	this->referencia_mapa_y=1;
	this->destino=Posicion(referencia_mapa_x,referencia_mapa_y);
	this->camino=Posicion(referencia_mapa_x,referencia_mapa_y);
	this->velocidad=float(objetoMapa->velocidad)/FACTOR_VELOCIDAD;
	this->vida=objetoMapa->vida;
	this->fuerza=objetoMapa->fuerza;
	this->armadura=objetoMapa->armadura;
	this->recoleccion=objetoMapa->recoleccion;
	this->construccion=objetoMapa->construccion;
	this->objetoMapa = objetoMapa;
	this->contador_ataque=Contador(objetoMapa->velocidad*FACTOR_CONTADOR);
	this->dibujo = 0;
	this->recursos = new RecursosJugador();
	this->congelado=false;
	this->atacado=NULL;
	this->objetivo=NULL;
}
Personaje::Personaje(ObjetoMapa* objetoMapa, int x, int y){
	this->referencia_mapa_x=x;
	this->referencia_mapa_y=y;
	this->destino=Posicion(referencia_mapa_x,referencia_mapa_y);
	this->camino=Posicion(referencia_mapa_x,referencia_mapa_y);
	this->velocidad=float(objetoMapa->velocidad)/FACTOR_VELOCIDAD;
	this->vida=objetoMapa->vida;
	this->fuerza=objetoMapa->fuerza;
	this->armadura=objetoMapa->armadura;
	this->recoleccion=objetoMapa->recoleccion;
	this->construccion=objetoMapa->construccion;
	this->contador_ataque=Contador(objetoMapa->velocidad*FACTOR_CONTADOR);
	this->objetoMapa = objetoMapa;
	this->dibujo = 0;
	this->recursos = new RecursosJugador();
	this->congelado=false;
	this->atacado=NULL;
	this->objetivo=NULL;

}

dibujo_t Personaje::dibujar(){
	return dibujo;
}
string Personaje::mostrar_contenido(){
	return this->objetoMapa->nombre+string(",")+this->nombreJugador;
}
void Personaje::set_posicion(Posicion pos){
	this->referencia_mapa_x=pos.get_x_exacta();
	this->referencia_mapa_y=pos.get_y_exacta();
	this->destino=pos;
	this->camino=pos;
}

Posicion Personaje::get_posicion(){
	return Posicion(referencia_mapa_x,referencia_mapa_y);
}
void Personaje::set_destino(Posicion destino){
	this->destino=destino;
}
void Personaje::set_camino(Posicion camino){
	this->camino=camino;
}
Posicion Personaje::get_destino(){
	return destino;
}
Posicion Personaje::get_camino(){
	return camino;
}
void Personaje::mover() {
	double x = camino.get_x_exacta();
	double y = camino.get_y_exacta();
	double delta_x = (double) (x - referencia_mapa_x);
	double delta_y = (double) (y - referencia_mapa_y);
	double distancia = sqrt(delta_x * delta_x + delta_y * delta_y);
	if (distancia != 0) {
		se_movio=true;
		if (distancia < velocidad) {
			distancia = velocidad;
		}
		if ((sqrt(delta_x * delta_x) > distancia)
				&& (sqrt(delta_x * delta_x) < distancia)) {

			this->referencia_mapa_x = x;
		}
		if ((sqrt(delta_y * delta_y) > distancia)
				&& ((sqrt(delta_y * delta_y) < distancia))) {
			this->referencia_mapa_y = y;
		}
		double des_x = (velocidad * delta_x) / distancia;
		double des_y = (velocidad * delta_y) / distancia;

		this->referencia_mapa_x += des_x;
		this->referencia_mapa_y += des_y;
	}else{
		se_movio=false;
	}

}
msg_t Personaje::interactuar(Personaje* otro_personaje){
	msg_t mensaje;
	if(this->getNombreJugador()!=otro_personaje->getNombreJugador()){
		mensaje.type = ATACAR;
		mensaje.paramInt1 = id;
		mensaje.paramDouble1 = otro_personaje->getId();
		return mensaje;
	}
	mensaje.type=KEEPALIVE;
	return mensaje;
}

msg_t Personaje::interactuar(Entidad* otra_entidad){
	msg_t mensaje;

	//estos datos los tengo que cargar igual en ambos
	//no puedo pasar el id al crear los recursos, por lo que paso la posicion
	mensaje.paramInt1 = id;
	mensaje.paramDouble1 = otra_entidad->getId();

	if (otra_entidad->esUnRecurso()) {//falta q sea un aldeano
		printf("Interaccion Recurso\n");
		mensaje.type = RECOLECCION_RECURSOS;
		return mensaje;
	//} else if (this->puedeAtacar()) {//falta ver q sea del enemigo
		//mensaje.type = ATACAR_EDIFICIO;
		//return mensaje;
	}
	// si es de el la entidad
	printf("Manda keep alive\n");
	mensaje.type=KEEPALIVE;
	return mensaje;
}

int Personaje::atacar(Personaje* otro_personaje){
	return this->fuerza;
}
void Personaje::set_ataque(Personaje* otro_personaje){
	this->atacado=otro_personaje;
}
void Personaje::dejar_de_atacar(){
	this->destino=this->get_posicion();
	this->atacado=NULL;
}
int  Personaje::danioInfringido(){
	return 5;
}
bool  Personaje::ejecutar_ataque(){
	if(this->atacado&&contador_ataque.contar()){
		this->atacado->recibirDanio(this->danioInfringido());
		return true;
	}
	return false;
}
void  Personaje::recibirDanio(int danio){
	this->vida-=danio;
	printf("La vida es: %d\n",vida);
}
bool operator== (Personaje &P1, Personaje &P2)
{
    return (P1.getId()==P2.getId());
}

void Personaje::setAccion(Entidad * entidad){
	if(this->atacado == NULL){
		objetivo = entidad;
	}
}
void Personaje::terminarAccion(){
	this->atacado=NULL;
	this->objetivo=NULL;
}

RecursosJugador* Personaje::recursosJugador(){
	return recursos;
}
Personaje::~Personaje() {
	delete recursos;
}
void Personaje::set_destino_al_ataque(){
	this->set_destino(this->atacado->get_posicion());
}
bool Personaje::es_adyacente_al_atacado(){
	printf( (this->atacado->get_posicion().es_adyacente(this->get_posicion()))?"Es adyacente":"No es adyacente");
	return this->atacado->get_posicion().es_adyacente(this->get_posicion());
}
