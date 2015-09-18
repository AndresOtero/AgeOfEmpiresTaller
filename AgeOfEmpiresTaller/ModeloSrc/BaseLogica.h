/*
 * BaseLogica.h
 *
 *  Created on: 16/9/2015
 *      Author: ger
 */

#ifndef BASELOGICA_H_
#define BASELOGICA_H_

class BaseLogica {
public:
	BaseLogica();
	BaseLogica(int ancho, int alto);
	int ancho;
	int alto;
	virtual ~BaseLogica();
};

#endif /* BASELOGICA_H_ */
