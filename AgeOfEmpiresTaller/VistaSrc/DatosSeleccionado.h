/*
 * DatosSeleccionado.h
 *
 *  Created on: Nov 14, 2015
 *      Author: tobias
 */
#include <string>
#ifndef DATOSSELECCIONADO_H_
#define DATOSSELECCIONADO_H_
using namespace std;
typedef enum{
	RECURSO,
	PERSONAJE,
	EDIFICIO,
	VACIO
}tipo_seleccionado;

class DatosSeleccionado {
public:
	DatosSeleccionado();
	void setTipo(tipo_seleccionado tipo){
		this->tipo = tipo;
	}
	void setNombre(string nombre){
		this->nombre = nombre;
	}
	void setJugador(string jugador){
		this->jugador = jugador;
	}
	void setVida(int *actual,int total){
		this->vida_actual = actual;
		this->vida_total = total;
	}
	void setConstruccion(int *actual, int total){
		this->consturccion_actual = actual;
		this->construccion_total = total;
	}
	void setRecurso(int *recurso){
		this->recurso = recurso;
	}
	string getNombre(){
		return nombre;
	}
	string getJugador(){
		return jugador;
	}
	int getVidaActual(){
		return *(this->vida_actual);
	}
	int getVidaTotal(){
		return this->vida_total;
	}
	int getConstruccionActual(){
		return *(this->consturccion_actual);
	}
	int getConstruccionTotal(){
		return this->construccion_total;
	}
	int getRecurso(){
		return *(this->recurso);
	}
	tipo_seleccionado getTipoSeleccionado(){
		return this->tipo;
	}
	virtual ~DatosSeleccionado();
private:
	string nombre;
	string jugador;
	int *vida_actual;
	int vida_total;
	int *consturccion_actual;
	int construccion_total;
	int *recurso;
	tipo_seleccionado tipo;


};

#endif /* DATOSSELECCIONADO_H_ */
