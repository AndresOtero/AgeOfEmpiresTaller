#include <SDL2/SDL.h>
#include <iostream>
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

