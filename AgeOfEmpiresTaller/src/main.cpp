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
	modelo->setMapa(10,15);
	Vista* vista= new Vista(modelo);
	vista->init();
	vista->loadMedia();
	vista->run();
	delete vista;
	Yaml* reader=new Yaml();
	reader->read();
	delete reader;
}
