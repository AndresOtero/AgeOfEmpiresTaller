/*
 * Vista.h
 *
 *  Created on: 9 de set. de 2015
 *      Author: andres
 */

#include <SDL2/SDL_video.h>
#include <memory>
#include "FactoryDibujo.h"

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
	int sensibilidad_de_scroll;
	float referencia_mapa_x,referencia_mapa_y,velocidad_de_scroll;
	void dibujar_mapa();

public:
	Vista(shared_ptr<Modelo>  modelo);
	bool init();
	int ancho_por_celda();
	int altura_por_celda();
	void transformar_isometrica_pantalla(float iso_x,float iso_y,int& pant_x,int& pant_y);
	void transformar_isometrica_pantalla(int iso_x,int iso_y,int& pant_x,int& pant_y);
	void transformar_pantalla_isometrica(int pant_x,int pant_y,float& iso_x,float& iso_y);
	void transformar_pantalla_isometrica(int pant_x,int pant_y,int& iso_x,int& iso_y);
	vector<int> calcular_bordes();
	bool loadMedia();
	void detectar_mouse_borde();
	int run();
	virtual ~Vista();

};

#endif /* VISTA_H_ */
