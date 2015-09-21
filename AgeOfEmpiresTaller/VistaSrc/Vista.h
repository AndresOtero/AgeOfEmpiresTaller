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
	Pantalla* pantalla;
	int margen_scroll;
	float referencia_mapa_x,referencia_mapa_y,velocidad_de_scroll;
	static const int VACIO = 0;
private:
	void dibujar_mapa();
	void mover_referencia(float vel_x,float vel_y);
	int ancho_por_celda();
	int altura_por_celda();
	vector<int> calcular_bordes();
	void detectar_mouse_borde();
	bool adentro_del_mapa(int coord_x, int coord_y);
	bool adentro_del_mapa(float coord_x, float coord_y);


public:
	Vista(shared_ptr<Modelo> modelo);
	bool init();
	bool loadMedia();
	int run();
	virtual ~Vista();


};

#endif /* VISTA_H_ */
