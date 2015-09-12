#include <SDL2/SDL.h>
#include <iostream>
#include "../ModeloSrc/Modelo.h"
#include "../VistaSrc/Vista.h"

using namespace std;
#include <iostream>
#include "yaml-cpp/yaml.h"
#include <fstream>
#include <string>
#include <vector>
#include "Yaml.h"

int main() {
	cout << "Hola Gaston\n";
	Modelo* modelo = new Modelo();
	int tamnio_x_mapa = 5;
	int tamnio_y_mapa = 3;
	modelo->setMapa(tamnio_x_mapa, tamnio_y_mapa);
	Vista* vista= new Vista(modelo);
	vista->init();
	vista->loadMedia();
	vista->run();
	delete vista;
	Yaml* reader=new Yaml();
	reader->read();
	delete reader;
}
