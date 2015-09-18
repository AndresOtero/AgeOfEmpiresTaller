/*
 * Yaml.cpp
 *
 *  Created on: 12 de set. de 2015
 *      Author: andres
 */

#include "Yaml.h"
#include "../ModeloSrc/ObjetoMapa.h"

Yaml::Yaml() {
}
const std::string tag_pantalla = "pantalla";
const std::string tag_pantalla_ancho = "ancho";
const std::string tag_pantalla_alto = "alto";

const std::string tag_config = "configuracion";
const std::string tag_config_vel_personaje = "vel_personaje";
const std::string tag_config_margen_scroll = "margen_scroll";

const std::string tag_tipos = "tipos";
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
	std::vector <Entidad_t> entidades;
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
} Objeto_mapa_t;

typedef struct  {
  Objeto_mapa_t objetoMapa;
  int fps;
  int delay;
} Objeto_mapa_animado_t;

void operator >> (const YAML::Node& node, Protagonista_t& entidad) {
   node[ tag_escenario_protagonista_tipo ] >> entidad.tipo;
   node[ tag_escenario_protagonista_x] >> entidad.x;
   node[ tag_escenario_protagonista_y] >> entidad.y;
}
void operator >> (const YAML::Node& node, Entidad_t entidad){
	 node[0] >> entidad.x;
	 node[1] >> entidad.y;
	 node[2] >> entidad.tipo;
}

int Yaml::read()
{
   std::ifstream fin("YAML/config.yaml");
   YAML::Parser parser(fin);
   YAML::Node doc;
   parser.GetNextDocument(doc);

   for(unsigned i=0;i<doc.size();i++) {
//        Objeto_mapa objeto;
//        doc[i] >> objeto;
//        ObjetoMapa* objetoMapa= new ObjetoMapa(objeto.objeto, objeto.origen, objeto.base_logica.ancho, objeto.base_logica.alto);
//        //std::cout << objeto.objeto <<  " " << objeto.base_logica.ancho << "\n";
//        std::cout << objetoMapa->objeto <<"\n";
//        delete objetoMapa;
     }
   std::cout << "end\n";
   return 0;
}

Yaml::~Yaml() {
}
//
//const YAML::Node& powers = node["powers"];
//   for(unsigned i=0;i<powers.size();i++) {
//      Power power;
//      powers[i] >> power;
//      Objeto_mapa.powers.push_back(power);
//   }

