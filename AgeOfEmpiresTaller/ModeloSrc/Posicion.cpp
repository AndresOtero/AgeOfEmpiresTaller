/*
 * Posicion.cpp
 *
 *  Created on: 17/9/2015
 *      Author: ger
 */

#include "Posicion.h"
#include "math.h"

Posicion::Posicion() {
	this -> x = 0;
	this -> y = 0;
}
Posicion::Posicion(int x, int y) {
	this -> x = x;
	this -> y = y;
}
Posicion::Posicion(double x, double y) {
	this -> x = x;
	this -> y = y;
}
double Posicion::distancia(Posicion posicion) {
	double delta_x = (double) (x - posicion.get_x_exacta());
	double delta_y = (double) (y - posicion.get_y_exacta());
	return sqrt(delta_x * delta_x + delta_y * delta_y);
}
double Posicion::distancia_manhattan(Posicion posicion) {
	double delta_x = (double) (getX() - posicion.getX());
	double delta_y = (double) (getY() - posicion.getY());
	return floor(sqrt(delta_x * delta_x)+sqrt( delta_y * delta_y));
}
bool operator== (Posicion &P1, Posicion &P2)
{
    return ((P1.getX()== P2.getX())&&
            (P1.getY() == P2.getY()));
}
bool operator== (Posicion const &P1, Posicion const &P2)
{
    return ((P1.getX()== P2.getX())&&
            (P1.getY() == P2.getY()));
}
Posicion operator+(const Posicion &c1, const Posicion &c2)
{
    return Posicion(c1.x+c2.x,c1.y+c2.y);
}
Posicion operator-(const Posicion &c1, const Posicion &c2)
{
    return Posicion(c1.x-c2.x,c1.y-c2.y);
}


Posicion::~Posicion(){

}
