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
	bool reiniciar = true;
	while (reiniciar){
		Yaml* reader=new Yaml();
		Juego* juego = reader->read();

		Modelo* modelo=new Modelo(juego);

		Vista* vista=new Vista(modelo);

		vista->init();
		vista->loadMedia();
		reiniciar = vista->run();
		delete reader;
		delete juego;
		delete modelo;
		delete vista;
	}

}
