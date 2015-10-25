/*
 * mensaje.h
 *
 *  Created on: Oct 25, 2015
 *      Author: tobias
 */

#ifndef GAMECONTROLLERSRC_MENSAJE_H_
#define GAMECONTROLLERSRC_MENSAJE_H_
const int PARAM_STRING_LEN = 20;

enum MensajeType {
	KEEPALIVE,
	QUIT,
	OK,
	RECONNECT,
	LOGIN, /* Cliente => Servidor: params(nombre) */
	ERROR_NOMBRE_TOMADO, /* Servidor => Cliente: El usuario existe y esta conectado, params() */
	MOVER_PERSONAJE,/* params(id_entidad, x , y) */
	ACTUALIZACION_RECURSOS, /* params (oro,plata,madera) */
};
typedef struct {
	MensajeType type;
	char paramNombre[PARAM_STRING_LEN];
	unsigned int paramInt1;
	double paramDouble1;
	double paramDouble2;
} msg_t;

class mensaje {
public:
	mensaje();
	virtual ~mensaje();
};

#endif /* GAMECONTROLLERSRC_MENSAJE_H_ */
