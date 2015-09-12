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
	Modelo* m = new Modelo();
	m->setMapa(1,2);
	delete m;
	Vista* vista= new Vista();
	vista->init();
	vista->loadMedia();
	vista->run();
	delete vista;
	Yaml* reader=new Yaml();
	reader->read();
	delete reader;
}