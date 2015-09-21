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
	shared_ptr<Yaml> reader(new Yaml());
	Juego* juego = reader->read();

	shared_ptr<Modelo> modelo(new Modelo(juego));

	shared_ptr<Vista> vista ( new Vista(modelo));

	vista->init();
	vista->loadMedia();
	vista->run();

}
