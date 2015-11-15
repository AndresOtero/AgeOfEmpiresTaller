/*
 * mensaje.h
 *
 *  Created on: Oct 25, 2015
 *      Author: tobias
 */

#ifndef GAMECONTROLLERSRC_MENSAJE_H_
#define GAMECONTROLLERSRC_MENSAJE_H_
const int PARAM_STRING_LEN = 20;
const int PARAM_TIPO_STRING_LEN = 7;

enum MensajeType {
	KEEPALIVE,
	QUIT,
	OK,
	RECONNECT,
	LOGIN, /* Cliente => Servidor: params(nombre) */
	ERROR_NOMBRE_TOMADO, /* Servidor => Cliente: El usuario existe y esta conectado, params() */
	MOVER_PERSONAJE,/* params(id_entidad, x , y) */
	ACTUALIZACION_RECURSOS, /* params (oro,plata,madera) */
	NUEVO_PERSONAJE,/*params name, id, pos_x,pos_y*/
	CREAR_ENTIDAD, /*name tipo, pos_x, pos_y*/
	CREAR_ENTIDAD_CONSTRUIDA,
	CREAR_RECURSO,/*name tipo,int cantidad,pos_x,pos_y*/
	FIN_INICIALIZACION,
	PARAM_MAPA,
	CONFIGURACION,
	DISCONNECT,
	ATACAR,/* int id atacante,double1 id atacado*/
	ELIMINAR_PERSONAJE,
	RECOLECCION_RECURSOS, /*int id recolector, double id recurso*/
	ELIMINAR_ENTIDAD, /* int id*/
	SET_ID_RECURSO, /*porque no se puede setear en una instruccion parece MIPS esto*/
	ELIMINAR,
	CONSTRUIR,
	EMPEZAR_ACCION,
	CREAR_PERSONAJE_EDIFICIO,/*Id edificio Nombre de Personaje*/
	TERMINAR_ACCION, //TODO
	COMENZAR_PARTIDA
};

typedef struct {
	MensajeType type;
	char paramNombre[PARAM_STRING_LEN];
	unsigned int paramInt1;
	//unsigned int paramInt2;
	double paramDouble1;
	double paramDouble2;
	char paramTipo[PARAM_TIPO_STRING_LEN];
} msg_t;

class mensaje {
public:
	mensaje();
	virtual ~mensaje();
};

#endif /* GAMECONTROLLERSRC_MENSAJE_H_ */
