/*
 * RecursosJugador.cpp
 *
 *  Created on: Sep 30, 2015
 *      Author: tobias
 */

#include "RecursosJugador.h"

RecursosJugador::RecursosJugador() {
	this->oro = 0;
	this->madera = 0;
	this->piedra = 0;
	this->comida = 0;
}

int validarRecurso(int cant){
	if (cant>=0)
		return cant;
	//avisar por log que no estan bien los parametros
	return 0;
}

RecursosJugador::RecursosJugador(int oro, int madera, int piedra, int comida) {
	//carga de todas formas los parametros
	this->oro = validarRecurso(oro);
	this->madera = validarRecurso(madera);
	this->piedra = validarRecurso(piedra);
	this->comida = validarRecurso(comida);
}
bool RecursosJugador::estaVacio(){
	if ((this->oro > 0) || (this->madera > 0) || (this->piedra >0) ){
		return false;
	}
	return true;
}
void RecursosJugador::reset(){
	this->oro= 0;
	this->madera= 0;
	this->piedra = 0;
}
void RecursosJugador::colectarOro(int cant){
	this->oro+=cant;
}
void RecursosJugador::colectarMadera(int cant){
	this->madera+=cant;
}
void RecursosJugador::colectarPiedra(int cant){
	this->piedra+=cant;
}
void RecursosJugador::colectarComida(int cant){
	this->comida+=cant;
}

int RecursosJugador::cantOro(){
	return this->oro;
}
int RecursosJugador::cantPiedra(){
	return this->piedra;
}

int RecursosJugador::cantMadera(){
	return this->madera;
}
int RecursosJugador::cantComida(){
	return this->comida;
}

bool RecursosJugador::puedePagar(Costo costo){
	bool puede = true;
	if (this->comida < costo.getComida()){
		printf("Comida a pagar %d\n",costo.getComida());
		puede =false;
	}else if (this->oro < costo.getOro()){
		printf("Oro a pagar %d\n",costo.getOro());
		puede =false;
	}else if (this->piedra < costo.getPiedra()){
		printf("Piedra a pagar %d\n",costo.getPiedra());
		puede =false;
	}else if (this->madera < costo.getMadera()){
		printf("Madera a pagar %d\n",costo.getComida());
		puede =false;
	}
	return puede;
}

bool RecursosJugador::pagar(Costo costo){
	if (this->puedePagar(costo)) {
		this->oro -= costo.getOro();
		this->comida -= costo.getComida();
		this->madera -= costo.getMadera();
		this->piedra -= costo.getPiedra();
		return true;
	}
	return false;

}
void RecursosJugador::reintegrarCosto(Costo costo){
	this->colectarComida(costo.getComida());
	this->colectarPiedra(costo.getPiedra());
	this->colectarOro(costo.getOro());
	this->colectarMadera(costo.getMadera());
}


RecursosJugador::~RecursosJugador() {
	// TODO Auto-generated destructor stub
}

