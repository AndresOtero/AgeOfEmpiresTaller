/*
 * GenerarID.cpp
 *
 *  Created on: Oct 12, 2015
 *      Author: tobias
 */

#include "GeneradorNumeros.h"

#include <iostream>


GeneradorNumeros::~GeneradorNumeros() {
	// TODO Auto-generated destructor stub
}

int GeneradorNumeros::numeroRandom(int min,int max){
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<double> dist(min, max);

	return dist(mt);
}
