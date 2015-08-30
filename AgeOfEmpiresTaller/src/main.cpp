#include <SDL2/SDL.h>
#include <iostream>
#include "../ModeloSrc/Mapa.h"

using namespace std;

class HolaMundo {
	public:
		HolaMundo(){};
    	void saludar ();
    	~HolaMundo(){};
};

void HolaMundo::saludar () {
  cout <<"hola";
}

int main() {
	HolaMundo* hola;
	hola = new HolaMundo();
	hola->saludar();
	delete hola;
	Mapa* m = new Mapa(1,2);
	bool jaja=m->celdaOcupada(1,1);
	bool j=false;
	delete m;
	return 0;
}
