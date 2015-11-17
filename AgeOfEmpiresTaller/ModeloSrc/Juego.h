/*
 * Juego.h
 *
 *  Created on: 20/9/2015
 *      Author: ger
 */

#ifndef JUEGO_H_
#define JUEGO_H_
#include "Pantalla.h"
#include "Oro.h"
#include "Madera.h"
#include "Piedra.h"
#include "Comida.h"


#include "Configuracion.h"
#include "Escenario.h"
#include <map>
typedef enum{
	MODO_DEFAULT, //matar centro civico
	CAPTURAR_BANDERA,
	REGICIDA
}modo_juego;
class Juego {
private :
	modo_juego modo;
	void cargarTiposDefault();
public:
	Juego();
	Juego(Pantalla* pantalla, Configuracion* conf, Escenario* escenario, std::map<std::string, ObjetoMapa*> &tipos );
	void setEscenario(string nombre,int ancho,int largo);
	void setConfiguracion(int margenScroll,int velocidad_personaje);
	void agregarEntidad(string nombre,int x, int y);
	Entidad * centroCivicoDe(string raza);
	void setJuegoCapturarBandera(){
		this->modo= CAPTURAR_BANDERA;
	}
	void setJuegoRegicida(){
		this->modo = REGICIDA;
	}
	Pantalla* pantalla;
	Configuracion* conf;
	Escenario* escenario;
	std::map<std::string, ObjetoMapa*> tipos;
	virtual ~Juego();
};

#endif /* JUEGO_H_ */
