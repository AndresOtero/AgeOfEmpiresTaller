/*
 * DibujoPersonaje.h
 *
 *  Created on: 18 de set. de 2015
 *      Author: andres
 */

#ifndef DIBUJOPERSONAJE_H_
#define DIBUJOPERSONAJE_H_

#include "DibujoAnimado.h"
#include "vector"
#include "memory.h"
#include <cmath>
#define SDL_RECT rect
#define CANTIDAD_DE_MOVIMIENTOS 8

enum movimientos {IZQUIERDA,DIAGONAL_IZQUIERDA_ARRIBA,ARRIBA,DIAGONAL_DERECHA_ARRIBA,DERECHA,DIAGONAL_DERECHA_ABAJO,ABAJO,DIAGONAL_IZQUIERDA_ABAJO,QUIETO_DERECHA, QUIETO_IZQUIERDA,QUIETO_ARRIBA,QUIETO_ABAJO,QUIETO_DERECHA_ARRIBA,QUIETO_DERECHA_ABAJO,QUIETO_IZQUIERDA_ARRIBA,QUIETO_IZQUIERDA_ABAJO};

using namespace std;
class DibujoPersonaje: public Dibujo {
	vector<SDL_Rect*> spriteClips;
	vector<int> cantidad_de_imagenes;
	int cant_mov;
	int movimiento_actual;
	int acumulador;
	int fps;

public:
	void congelar();
	void descongelar();
	void set_cantidad_de_movimientos(int cant_de_mov);
	void set_cantidad_de_imagenes(int n_mov,int cant_de_imagenes);
	void set_imagen(int n_mov,int n_imagen, int x, int y, int ancho, int alto);
	DibujoPersonaje();
	int get_alto(int n_mov,int n_imagen);
	int get_ancho(int n_mov, int n_imagen);
	int get_alto();
	int get_ancho();
	void render(SDL_Renderer* renderer);
	void elegir_frame(int des_x,int des_y);
	void cambiar_frame();
	~DibujoPersonaje();
};

#endif /* DIBUJOPERSONAJE_H_ */
