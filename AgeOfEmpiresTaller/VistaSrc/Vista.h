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
#include "../ModeloSrc/Personaje.h"
using namespace std;

class Dibujo;
class DibujoPersonaje;
class Modelo;
struct SDL_Renderer;

#ifndef VISTA_H_
#define VISTA_H_

class Vista {
	SDL_Window* gWindow;
	SDL_Renderer* gRenderer;
	Modelo* modelo;
	shared_ptr<FactoryDibujo> factory;
	shared_ptr<CambioDeCoordendas> transformador;
	Pantalla* pantalla;
	int margen_scroll;
	double referencia_mapa_x,referencia_mapa_y,velocidad_de_scroll;
	static const int VACIO = 0;
private:
	void dibujar_mapa();
	void mover_referencia(double vel_x,double vel_y);
	int ancho_por_celda();
	int altura_por_celda();
	vector<int> calcular_bordes();
	void detectar_mouse_borde();
	bool adentro_del_mapa(int coord_x, int coord_y);
	bool adentro_del_mapa(double coord_x, double coord_y);
	void dibujar_personaje(double mover_x, double mover_y);
	void corregir_referencia_coordenadas_pantalla_mapa(double& coord_x, double& coord_y);
	void corregir_referencia_coordenadas_mapa_pantalla(double& coord_x, double& coord_y);


public:
	Vista(Modelo* modelo);
	bool init();
	bool loadMedia();
	int run();
	virtual ~Vista();


};

#endif /* VISTA_H_ */
