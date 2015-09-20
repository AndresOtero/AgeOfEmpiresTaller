#include <SDL2/SDL.h>
#include <iostream>
#include "../ModeloSrc/Modelo.h"
#include "../VistaSrc/Vista.h"
#include "../ModeloSrc/Configuracion.h"

using namespace std;
#include <iostream>
#include "yaml-cpp/yaml.h"
#include <fstream>
#include <string>
#include <vector>
#include "Yaml.h"
#include <memory>
using namespace std;

int main() {
	shared_ptr<Modelo> modelo(new Modelo());
	int tamnio_x_mapa = 100;
	int tamnio_y_mapa = 100;
	modelo->setMapa(tamnio_x_mapa, tamnio_y_mapa);
	shared_ptr<Pantalla> pantalla(new Pantalla());
	shared_ptr<Configuracion> configuracion(new Configuracion());/**
	Agregar ancho y alto de la celda( por default el ancho y alto del default). Sacar velocidad del personaje y agregarsela al personaje.
	**/
	shared_ptr<Vista> vista ( new Vista(modelo,pantalla,configuracion));
	vista->init();
	vista->loadMedia();
	vista->run();
	shared_ptr<Yaml> reader(new Yaml());
	reader->read();
}
