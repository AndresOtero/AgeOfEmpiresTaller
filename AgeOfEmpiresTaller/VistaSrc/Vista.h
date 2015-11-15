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
#include "../GameControllerSrc/GameControllerCliente.h"
#include "../ModeloSrc/Pantalla.h"
#include "../ModeloSrc/Configuracion.h"
#include "../ModeloSrc/Personaje.h"
#include "Barra.h"
#include "../ModeloSrc/Mapa.h"
#include "../VistaSrc/DatosSeleccionado.h"
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
	shared_ptr<Barra> barra;
	shared_ptr<FactoryDibujo> factory;
	shared_ptr<CambioDeCoordendas> transformador;
	Pantalla* pantalla;
	shared_ptr<Dibujo> edificioACrear;
	GameControllerCliente * gameController;
	int margen_scroll;
	int seleccion_x_inicio,seleccion_y_inicio,seleccion_x_final,seleccion_y_final;
	Entidad* entidadACrear;

	bool esta_eligiendo,termino_de_elegir;
	double referencia_mapa_x,referencia_mapa_y,velocidad_de_scroll;
	static const int VACIO = 0;
private:
	bool esta_en_seleccion(int x,int y);
	void setear_seleccion();
	void dibujar_mapa();
	void mover_referencia(double vel_x,double vel_y);
	int ancho_por_celda();
	int altura_por_celda();
	vector<int> calcular_bordes();
	void detectar_mouse_borde();
	bool adentro_del_mapa(int coord_x, int coord_y);
	bool adentro_del_mapa(double coord_x, double coord_y);
	void dibujar_personaje(Personaje* personaje);
	bool repito_dibujo(int x,int y,int dimension);
	void corregir_referencia_coordenadas_pantalla_mapa(double& coord_x, double& coord_y);
	void corregir_referencia_coordenadas_mapa_pantalla(double& coord_x, double& coord_y);
	void cargarEdificioACrear(string tipo);
	void dibujar_barra();
	void dibujar_edificio(int mov_x,int mov_y);
	void dejarDeDibujarEdificio();


public:
	Vista(Modelo* modelo,GameControllerCliente* gameControler);
	bool init();
	bool loadMedia();
	void crearPersonaje(string tipo,Personaje* personaje);
	void setear_referencia(double ref_x,double ref_y) ;
	void setear_vista(string nombreJugador);

	bool run();
	virtual ~Vista();


};

#endif /* VISTA_H_ */
