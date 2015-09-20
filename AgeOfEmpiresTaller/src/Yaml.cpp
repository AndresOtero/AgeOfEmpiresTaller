/*
 * Yaml.cpp
 *
 *  Created on: 12 de set. de 2015
 *      Author: andres
 */

#include "Yaml.h"
#include "../ModeloSrc/ObjetoMapa.h"
#include "../ModeloSrc/Pantalla.h"
#include "../ModeloSrc/Configuracion.h"
#include "../ModeloSrc/Escenario.h"
#include "../ModeloSrc/Juego.h"
//#include "../ModeloSrc/ObjetoMapaAnimado.h"
#include <map>
Yaml::Yaml() {
}
const std::string tag_pantalla = "pantalla";
const std::string tag_pantalla_ancho = "ancho";
const std::string tag_pantalla_alto = "alto";

const std::string tag_config = "configuracion";
const std::string tag_config_vel_personaje = "vel_personaje";
const std::string tag_config_margen_scroll = "margen_scroll";

const std::string tag_tipos = "tipos";
const std::string tag_tipos_nombre = "nombre";
const std::string tag_tipos_imagen = "imagen";
const std::string tag_tipos_ancho_base = "ancho_base";
const std::string tag_tipos_alto_base = "alto_base";
const std::string tag_tipos_pixel_ref_x = "pixel_ref_x";
const std::string tag_tipos_pixel_ref_y = "pixel_ref_y";
const std::string tag_tipos_delay = "delay";
const std::string tag_tipos_fps = "fps";

const std::string tag_escenario = "escenario";
const std::string tag_escenario_nombre = "nombre";
const std::string tag_escenario_size_x = "size_x";
const std::string tag_escenario_size_y = "size_y";
const std::string tag_escenario_entidades = "entidades";
const std::string tag_escenario_entidades_x = "x";
const std::string tag_escenario_entidades_y = "y";
const std::string tag_escenario_entidades_tipo = "tipo";
const std::string tag_escenario_protagonista = "protagonista";
const std::string tag_escenario_protagonista_x = "x";
const std::string tag_escenario_protagonista_y = "y";
const std::string tag_escenario_protagonista_tipo = "tipo";

typedef struct {
	int x;
	int y;
	std::string tipo;
} Entidad_t;

typedef struct {
	std::string tipo;
	int x;
	int y;
} Protagonista_t;

typedef struct {
	std::string nombre;
	int size_x;
	int size_y;
	Protagonista_t protagonista;
} Escenario_t;

typedef struct {
	int ancho;
	int alto;
} Pantalla_t;

typedef struct {
	int vel_personaje;
	int margen_scroll;
} Configuracion_t;

typedef struct  {
   std::string nombre;
   std::string imagen;
   int ancho_base;
   int alto_base;
   int pixel_ref_x ;
   int pixel_ref_y ;
   int fps;
   int delay;
} Objeto_mapa_t;

typedef struct {
	Pantalla_t pantalla;
	Configuracion_t configuracion;
	Escenario_t escenario;

}ConfiguracionJuego_t;

int Yaml::read()
{
	Juego* juego;
	try {
	   std::ifstream fin("YAML/configuracion.yaml");
	   YAML::Parser parser(fin);
	   YAML::Node doc;
	   parser.GetNextDocument(doc);

	   ConfiguracionJuego_t conf;
	   Pantalla* pantalla;
	   Configuracion* configuracion;
	   std::map<std::string, ObjetoMapa*> tipos;
	   Escenario* escenario;
	   EntidadAnimada* protagonista;

	   if (const YAML::Node *pPantalla = doc.FindValue(tag_pantalla)){
		   if (const YAML::Node *pPantallaAncho = (*pPantalla).FindValue(tag_pantalla_ancho)){
			   (*pPantallaAncho) >> conf.pantalla.ancho;
			   if (const YAML::Node *pPantallaAlto = (*pPantalla).FindValue(tag_pantalla_alto)){
				   (*pPantallaAlto) >> conf.pantalla.alto;
				   pantalla = new Pantalla(conf.pantalla.ancho,conf.pantalla.alto);
			   }else{
				   //log pantalla sin alto
				   pantalla = new Pantalla();
			   }
		   }else{
			   //log conf pantalla sin ancho

			   pantalla = new Pantalla();
		   }

	   }else{
		   // log no tiene pantalla
		   pantalla = new Pantalla();
	   }

		if (const YAML::Node *pConfiguracion = doc.FindValue(tag_config)){
			if (const YAML::Node *pConfigVel = (*pConfiguracion).FindValue(tag_config_vel_personaje)){
				(*pConfigVel) >> conf.configuracion.vel_personaje;
				if (const YAML::Node *pConfigMargen = (*pConfiguracion).FindValue(tag_config_margen_scroll)){
					 (*pConfigMargen) >> conf.configuracion.margen_scroll;
					 configuracion = new Configuracion(conf.configuracion.vel_personaje, conf.configuracion.margen_scroll );
				}else{
						 //crear log no tiene margen
					configuracion = new Configuracion();
				}
			}else{
					 //crear log no tiene vel personaje
				configuracion = new Configuracion();
			}
		}else{
			//crear log falta seccion configuracion
			configuracion = new Configuracion();
		}
		if (const YAML::Node *pTipos = doc.FindValue(tag_tipos)){
			for(unsigned i=0;i< (*pTipos).size();i++) {
				 Objeto_mapa_t tipo;
				 if (const YAML::Node *pTipoNombre = ((*pTipos)[i]).FindValue(tag_tipos_nombre)){
					 (*pTipoNombre) >> tipo.nombre;

					 if (const YAML::Node *pTipoImagen = ((*pTipos)[i]).FindValue(tag_tipos_imagen)){
						 *pTipoImagen >> tipo.imagen;

						 ObjetoMapa* objeto = new ObjetoMapa(tipo.nombre, tipo.imagen);

						 if (const YAML::Node *pTipoAnchoBase = ((*pTipos)[i]).FindValue(tag_tipos_ancho_base)){
								*pTipoAnchoBase >> tipo.ancho_base;
								if (const YAML::Node *pAltoBase = ((*pTipos)[i]).FindValue(tag_tipos_alto_base)){
									*pAltoBase >> tipo.alto_base;
									objeto->baseLogica->ancho = tipo.ancho_base;
									objeto->baseLogica->alto  = tipo.alto_base;
								}else{
									 //crear log hay ancho pero no alto
								 }
						 }

						 if (const YAML::Node *pPixelRefX = ((*pTipos)[i]).FindValue(tag_tipos_pixel_ref_x)){
							 *pPixelRefX >> tipo.pixel_ref_x;
							 if (const YAML::Node *pPixelRefY = ((*pTipos)[i]).FindValue(tag_tipos_pixel_ref_y)){
								*pPixelRefY >> tipo.pixel_ref_y;
								objeto->pixelsReferencia->x = tipo.pixel_ref_x;
								objeto->pixelsReferencia->y = tipo.pixel_ref_y;
							 }else{
								 //crear log hay x pero no y
							 }
						 }
						 if (const YAML::Node *pFps = ((*pTipos)[i]).FindValue(tag_tipos_fps)){
							 *pFps >> tipo.fps;
							 objeto -> fps = tipo.fps;
						 }
						 if (const YAML::Node *pDelay = ((*pTipos)[i]).FindValue(tag_tipos_delay)){
							 *pDelay >> tipo.delay;
							 objeto -> delay = tipo.delay;
						 }
						 tipos[tipo.nombre] = objeto;
						 //conf.tipos.push_back(tipo);
					 }else{
						 //crear log falta imagen del tipo
					 }
				 }else{
					 //crear log falta nombre del tipo
				 }
			 }
		 }else{
			 // no hay tipos
		 }
		if (const YAML::Node *pEscenario = doc.FindValue(tag_escenario)){
			if (const YAML::Node *pNombre = (*pEscenario).FindValue(tag_escenario_nombre)){
				(*pNombre) >> conf.escenario.nombre;
			}else{
				// log std::map<std::string, ObjetoMapa*> no hay nombre de escenario
			}
			if (const YAML::Node *pSizeX = (*pEscenario).FindValue(tag_escenario_size_x)){
				(*pSizeX) >> conf.escenario.size_x;

				if (const YAML::Node *pSizeY = (*pEscenario).FindValue(tag_escenario_size_y)){
					(*pSizeY) >> conf.escenario.size_y;
					escenario = new Escenario(conf.escenario.nombre, conf.escenario.size_x, conf.escenario.size_y);
				}else{
					// log hay size x pero no y
					escenario = new Escenario();
				}
			}else{
				// log no hay size
				escenario = new Escenario();
			}

			if (const YAML::Node *pEntidades = (*pEscenario).FindValue(tag_escenario_entidades)){
				 for(unsigned i=0;i< (*pEntidades).size();i++) {
					 Entidad_t entidad;
					 Entidad* ent;
					 if (const YAML::Node *pX = ((*pEntidades)[i]).FindValue(tag_escenario_entidades_x)){
						(*pX) >> entidad.x;
						 if (const YAML::Node *pY = ((*pEntidades)[i]).FindValue(tag_escenario_entidades_y)){
							(*pY) >> entidad.y;
							if (const YAML::Node *pTipo = ((*pEntidades)[i]).FindValue(tag_escenario_entidades_tipo)){
								(*pTipo) >> entidad.tipo;
								 if(ObjetoMapa* obj = tipos[entidad.tipo]){
									 ent = new Entidad(obj,entidad.x, entidad.y);
									 escenario->entidades.push_back(ent);
									 //conf.escenario.entidades.push_back(entidad);
								 }else{
									 //log tipo de la entidad no existe
								 }
							 }else{
								 // log no hay tipo
							 }
						 }else{
							 // log no hay y
						 }
					 }else{
						 //log no hay x
					 }
				 }
			}else{
				// log no hay entidades
			}
			bool tieneProt = false;
			if (const YAML::Node *pPersonaje = (*pEscenario).FindValue(tag_escenario_protagonista)){
				if (const YAML::Node *pTipo = (* pPersonaje)[0].FindValue(tag_escenario_protagonista_tipo)){
					(*pTipo) >> conf.escenario.protagonista.tipo;
					if (const YAML::Node *pX = (* pPersonaje)[0].FindValue(tag_escenario_protagonista_x)){
						(*pX) >> conf.escenario.protagonista.x;
						if (const YAML::Node *pY = (* pPersonaje)[0].FindValue(tag_escenario_protagonista_y)){
							(*pY) >> conf.escenario.protagonista.y;
							 if(ObjetoMapa* obj = tipos[conf.escenario.protagonista.tipo]){
								 protagonista = new EntidadAnimada(obj,conf.escenario.protagonista.x,conf.escenario.protagonista.y);
								 escenario->protagonista = protagonista;
								 tieneProt = true;
							 }else{
								 //log el tipo no existe
							 }
						}else{
							//log no hay y del protagonista
						}
					}else{
						//log no hay x del protagonista
					}
				}else{
					//log no hay tipo del progtagonista
				}
			}else{
				//log no hay personaje principal
			}
			if(tieneProt == false){
				protagonista = new EntidadAnimada();
			}
		}else{
			escenario = new Escenario();
		}


	   juego = new Juego(pantalla, configuracion, escenario,tipos);
	   std:: cout << "Pantalla: " << juego->pantalla->getAncho() << " " << juego->pantalla->getAlto()  << "\n";
	   delete pantalla;

	   std:: cout << "Configuracion: " << juego->conf->get_vel_personaje() << " " << juego->conf->get_margen_scroll() << "\n";
	   delete configuracion;

	   ObjetoMapa*  tipo = juego->tipos["tierra"];
	   std:: cout << "Tipo" << " " << tipo->nombre << " " << tipo->imagen << tipo->baseLogica->ancho << " "<< tipo->baseLogica->alto << " "
			 << tipo->pixelsReferencia->x << " "<< tipo->pixelsReferencia->y << "\n"  ;

	   std:: cout << "Escenario:  " << conf.escenario.nombre << " " << conf.escenario.size_x << " " << conf.escenario.size_y << "\n"  ;
	   for(unsigned i=0;i< escenario->entidades.size();i++) {
			 Entidad* entidad = escenario->entidades[i];
			 std:: cout << "    Entidad" << i  << " " << entidad->posicion->x << " " << entidad->posicion->y << " " <<entidad->objetoMapa->nombre << "\n"  ;
	   }

	   std::cout << "    Protagonista: " << escenario->protagonista->objetoMapaAnimado->nombre << " " << escenario->protagonista->posicion->x << " " << escenario->protagonista->posicion->y << "\n"  ;
	   std::cout << "end\n";

	   delete escenario;

	} catch(YAML::Exception& e) {
			juego = new Juego();
		    std::cout << e.what() << "\n";//mandar al log
	}
   return 0;
}

Yaml::~Yaml() {
}

