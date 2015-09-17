/*
 * ObjetoMapaAnimado.h
 *
 *  Created on: 17/9/2015
 *      Author: ger
 */

#ifndef OBJETOMAPAANIMADO_H_
#define OBJETOMAPAANIMADO_H_

#include "ObjetoMapa.h"

class ObjetoMapaAnimado: public ObjetoMapa {
public:
	ObjetoMapaAnimado(string nombre, vector <string>  imagenes);
	ObjetoMapaAnimado(string nombre, vector <string>  imagenes, int fps);
	ObjetoMapaAnimado(string nombre, vector <string>  imagenes, int fps, int delay);
	ObjetoMapaAnimado(string nombre,vector <string>  imagenes, int ancho_base, int alto_base, int fps, int delay );
	ObjetoMapaAnimado(string nombre, vector <string>  imagenes, int ancho_base, int alto_base, int pixel_ref_x, int pixel_ref_y, int fps, int delay );
	int fps;
	int delay;
	virtual ~ObjetoMapaAnimado();
};

#endif /* OBJETOMAPAANIMADO_H_ */
