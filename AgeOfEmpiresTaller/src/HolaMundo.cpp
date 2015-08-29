/*
 * HolaMundo.cpp
 *
 *  Created on: 29 de ago. de 2015
 *      Author: andres
 */

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

int main () {
	HolaMundo* hola;
	hola= new HolaMundo();
	hola->saludar();
	delete hola;
	return 0;
}
