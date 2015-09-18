/*
 * ObjetoMapa.h
 *
 *  Created on: 16/9/2015
 *      Author: ger
 */

#ifndef OBJETOMAPA_H_
#define OBJETOMAPA_H_

#include <string>
#include <vector>
#include "BaseLogica.h"
#include "PixelsReferencia.h"

using namespace std;

class ObjetoMapa {

public:
	string nombre;
	vector <string> imagenes;
	BaseLogica* baseLogica;
	PixelsReferencia* pixelsReferencia;
	ObjetoMapa(string nombre, vector <string>  imagenes);
	ObjetoMapa(string nombre,vector <string>  imagenes, int ancho_base, int alto_base );
	ObjetoMapa(string nombre, vector <string>  imagenes, int ancho_base, int alto_base, int pixel_ref_x, int pixel_ref_y );

	virtual ~ObjetoMapa();
};

#endif /* OBJETOMAPA_H_ */
