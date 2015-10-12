/*
 * GenerarID.h
 *
 *  Created on: Oct 12, 2015
 *      Author: tobias
 */

#ifndef GENERARID_H_
#define GENERARID_H_
#include <iostream>

class GenerarID {
private:
	int devolver;
public:
	static int id;
	GenerarID(){devolver = id++;};
	int otroID(){return devolver;};
	virtual ~GenerarID();
};

#endif /* GENERARID_H_ */
