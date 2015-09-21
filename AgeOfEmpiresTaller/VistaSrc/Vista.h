/*
 * Vista.h
 *
 *  Created on: 9 de set. de 2015
 *      Author: andres
 */

#include <SDL2/SDL_video.h>
#include <memory>
#include "FactoryDibujo.h"
#include "CambioDeCoordendas.h"
#include "../ModeloSrc/Pantalla.h"
#include "../ModeloSrc/Configuracion.h"

using namespace std;

class Dibujo;
class DibujoPersonaje;
class Modelo;
struct SDL_Renderer;

#ifndef VISTA_H_
#define VISTA_H_

class Vista {
	//The window we'll be rendering to
	SDL_Window* gWindow;
	//The window renderer
	SDL_Renderer* gRenderer;
	shared_ptr<DibujoPersonaje> personaje;
	shared_ptr<Modelo>  modelo;
	shared_ptr<FactoryDibujo> factory;
	shared_ptr<CambioDeCoordendas> transformador;
	shared_ptr<Pantalla> pantalla;
	int margen_scroll;
	float referencia_mapa_x,referencia_mapa_y,velocidad_de_scroll;
	static const int VACIO = 0;

	void dibujar_mapa();

public:
	Vista(shared_ptr<Modelo>  modelo,shared_ptr<Pantalla> pantalla,shared_ptr<Configuracion> configuracion);
	bool init();
	int ancho_por_celda();
	int altura_por_celda();
	vector<int> calcular_bordes();
	bool loadMedia();
	void detectar_mouse_borde();
	int run();
	virtual ~Vista();
private:
	bool adentro_del_mapa(int coord_x,int coord_y);

};

#endif /* VISTA_H_ */
