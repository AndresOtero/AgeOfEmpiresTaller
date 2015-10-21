#include <SDL2/SDL.h>
#include <iostream>
#include "../ModeloSrc/Modelo.h"
#include "../VistaSrc/Vista.h"
#include "../ModeloSrc/Configuracion.h"
#include "../VistaSrc/CambioDeCoordendas.h"
#include "../GameControllerSrc/GameControllerCliente.h"
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
		delete reader;
		Modelo* modelo=new Modelo(juego);
		Vista* vista=new Vista(modelo);
		vista->init();
		vista->loadMedia();
		reiniciar = vista->run();
		delete modelo;
		delete vista;

	}

}
