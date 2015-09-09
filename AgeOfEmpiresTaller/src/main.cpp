#include <SDL2/SDL.h>
#include <iostream>
#include "../ModeloSrc/Mapa.h"
#include "../VistaSrc/Vista.h"

using namespace std;


int main() {
	cout <<"hola\n";
	Mapa* m = new Mapa(1,2);
	delete m;
	Vista* vista= new Vista();
	vista->init();
	vista->loadMedia();
	vista->run();
	delete vista;
}
