/*
 * CambioDeCoordendas.h
 *
 *  Created on: 19 de set. de 2015
 *      Author: andres
 */

#ifndef CAMBIODECOORDENDAS_H_
#define CAMBIODECOORDENDAS_H_

class CambioDeCoordendas {
	int ancho_celda,alto_celda;
public:
	CambioDeCoordendas(int ancho_celda,int alto_celda);
	void transformar_pantalla_isometrica(int pant_x,int pant_y,int& iso_x,int& iso_y);
	void transformar_pantalla_isometrica(int pant_x,int pant_y,double& iso_x,double& iso_y);
	void transformar_isometrica_pantalla(int iso_x,int iso_y,int& pant_x,int& pant_y);
	void transformar_isometrica_pantalla(double iso_x,double iso_y,int& pant_x,int& pant_y);
	void transformar_isometrica_pantalla(double iso_x,double iso_y,double& pant_x,double& pant_y);
	virtual ~CambioDeCoordendas();
private:
	int ancho_por_celda();
	int altura_por_celda();
};

#endif /* CAMBIODECOORDENDAS_H_ */
