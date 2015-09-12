#include <SDL2/SDL.h>
#include <iostream>
#include "../ModeloSrc/Modelo.h"
#include "../VistaSrc/Vista.h"

using namespace std;


int main() {
	cout << "Hola Gaston";
	Modelo* m = new Modelo();
	m->setMapa(1,2);
	delete m;
	Vista* vista= new Vista();
	vista->init();
	vista->loadMedia();
	vista->run();
	delete vista;
}
