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
	LOGIN, /* Cliente => Servidor: params(nombre) */
	ERROR_NOMBRE_TOMADO, /* Servidor => Cliente: El usuario existe y esta conectado, params() */
	MOVER_PERSONAJE,/* params(id_entidad, x , y) */
	ACTUALIZACION_RECURSOS, /* params (oro,plata,madera) */
};
typedef struct {
	MensajeType type;
	char paramNombre[PARAM_STRING_LEN];
	unsigned int param1;
	unsigned int param2;

} msg_t;
class mensaje {
public:
	mensaje();
	virtual ~mensaje();
};

#endif /* GAMECONTROLLERSRC_MENSAJE_H_ */
