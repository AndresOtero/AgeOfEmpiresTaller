/*
 * CmpDistanciasTuplas.h
 *
 *  Created on: 5 de oct. de 2015
 *      Author: andres
 */
#ifndef CMPDISTANCIASTUPLAS_H_
#define CMPDISTANCIASTUPLAS_H_
using namespace std;

class CompDistancias
{
public:
    bool operator()(pair<Posicion,double> p1,pair<Posicion,double> p2) {
        return p1.second>p2.second;
    }
};




#endif /* CMPDISTANCIASTUPLAS_H_ */
