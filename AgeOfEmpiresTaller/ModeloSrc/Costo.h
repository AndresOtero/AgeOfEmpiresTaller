/*
 * Costo.h
 *
 *  Created on: Nov 14, 2015
 *      Author: tobias
 */

#ifndef COSTO_H_
#define COSTO_H_

class Costo {
public:
	int oro;
	int madera;
	int piedra;
	int comida;
	Costo();
	void setCosto(int oro,int madera,int piedra,int comida){
		this->oro = oro;
		this->madera = madera;
		this->piedra = piedra;
		this->comida = comida;
	}
	int getOro(){
		return oro;
	}
	int getMadera(){
			return madera;
		}
	int getPiedra() {
		return piedra;
	}
	int getComida() {
		return comida;
	}
	virtual ~Costo();
};

#endif /* COSTO_H_ */
