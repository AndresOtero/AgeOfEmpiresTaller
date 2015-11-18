/*
 * FactoryDibujo.cpp
 *
 *  Created on: 16 de set. de 2015
 *      Author: andres
 */

#include "FactoryDibujo.h"
#define DIBUJOS_POR_DEFAULT 4
#define CANTIDAD_DE_PARAMETROS 4
enum parametros {
	X = 0, Y = 1, ANCHO = 2, ALTO = 3
};

FactoryDibujo::FactoryDibujo(SDL_Renderer* gRenderer) {
	// TODO Auto-generated constructor stub
	this->dibujos = vector<shared_ptr<Dibujo>>(DIBUJOS_POR_DEFAULT, NULL);
	this->gRenderer = gRenderer;
	this->cantidad_de_dibujos = this->dibujos.size();
	this->dibujo_actual = 1;
	this->ancho_tile = 0;
	this->alto_tile = 0;
}
bool FactoryDibujo::crear_dibujo_personaje(string path,
		int cantidad_de_movimientos, int frames, int fps) {
	//printf("path: %s\n",path.c_str());
	shared_ptr<DibujoPersonaje> dibujo_nuevo = shared_ptr<DibujoPersonaje>(
			new DibujoPersonaje());
	if (dibujo_nuevo->cargar_archivo(path, gRenderer)) {
		dibujo_nuevo->setFps(fps);
		dibujo_nuevo->set_cantidad_de_movimientos(cantidad_de_movimientos);

		int ancho = dibujo_nuevo->getWidth() / frames;
		int alto = dibujo_nuevo->getHeight() / frames;

		for (int i = 0; i < cantidad_de_movimientos; i++) {
			dibujo_nuevo->set_cantidad_de_imagenes(i, frames);
			for (int j = 0; j < frames; j++) {
				dibujo_nuevo->set_imagen(i, j, j * ancho, i * alto, ancho,
						alto);
			}
		}
		this->set_dibujo(dibujo_nuevo);
		return true;
	}
	return false;
}
bool FactoryDibujo::crear_dibujo_animado(string path, vector<int> pixeles, int fps,	int delay) {
	//printf("path: %s\n",path.c_str());
	shared_ptr<DibujoAnimado> dibujo_nuevo = shared_ptr<DibujoAnimado>(
			new DibujoAnimado());
	if (dibujo_nuevo->cargar_archivo(path, gRenderer)) {

		dibujo_nuevo->set_cantidad_de_imagenes(DIBUJOS_POR_DEFAULT);

		int ancho = dibujo_nuevo->getWidth() / DIBUJOS_POR_DEFAULT;

		for (int i = 0; i < DIBUJOS_POR_DEFAULT; i++) {
			dibujo_nuevo->setPixeles(pixeles[X], pixeles[Y]);
			dibujo_nuevo->set_imagen(i, i * ancho,0, dibujo_nuevo->getHeight(),	ancho);
		}

		dibujo_nuevo->set_fps(fps);
		dibujo_nuevo->set_delay(delay);
		this->set_dibujo(dibujo_nuevo);
		return true;
	}
	return false;
}
bool FactoryDibujo::crear_dibujo_tile(string path) {
	shared_ptr<Dibujo_Estatico> dibujo_nuevo = shared_ptr<Dibujo_Estatico>(
			new Dibujo_Estatico());
	if (dibujo_nuevo->cargar_archivo(path, gRenderer)) {
		this->ancho_tile = dibujo_nuevo->getWidth();
		this->alto_tile = dibujo_nuevo->getHeight();
		dibujo_nuevo->set_imagen(0, 0);
		this->set_dibujo(dibujo_nuevo);
		return true;
	}
	return false;
}
bool FactoryDibujo::crear_dibujo_estatico(string path,
		vector<int> parametros_de_imagen) {
	//printf("path: %s\n",path.c_str());
	shared_ptr<Dibujo_Estatico> dibujo_nuevo = shared_ptr<Dibujo_Estatico>(
			new Dibujo_Estatico());
	if (dibujo_nuevo->cargar_archivo(path, gRenderer)) {
		dibujo_nuevo->setPixeles(parametros_de_imagen[X],
				parametros_de_imagen[Y]);
		this->set_dibujo(dibujo_nuevo);
		return true;
	}
	return false;
}
int FactoryDibujo::ultimo_dibujo() {
	return (dibujo_actual - 1);
}

void FactoryDibujo::set_dibujo(shared_ptr<Dibujo> dibujo) {
	if (this->dibujos.capacity() == dibujo_actual) {
		this->dibujos.resize(this->dibujos.capacity() * 2, NULL);
	}
	this->dibujos.insert(this->dibujos.begin() + dibujo_actual, dibujo);
	dibujo_actual++;
}

shared_ptr<Dibujo> FactoryDibujo::get_dibujo(int n_dibujo) {
	if (n_dibujo >= this->dibujo_actual) {
		return NULL;
	}
	return this->dibujos[n_dibujo];
}
dibujo_t FactoryDibujo::get_idDibujo(string nombre) {
	//no chequea q no exista el nombre!!!!!!
	if (nombre.empty()) {
		return DEFAULT;
	}
	return this->hashDibujos[nombre];
}

void FactoryDibujo::setHashDibujos(
		std::map<std::string, dibujo_t> hashDibujos) {
	this->hashDibujos = hashDibujos;
}

FactoryDibujo::~FactoryDibujo() {

}

