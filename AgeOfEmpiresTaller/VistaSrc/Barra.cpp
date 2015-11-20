/*
 * BarraStatus.cpp
 *
 *  Created on: Oct 8, 2015
 *      Author: tobias
 */

#include "Barra.h"

#define PIXELESDIGITOS 200
#define ANCHO_BASE  249
#define ALTO_BASE  124
#define ALTO_BARRITA 10

Barra::Barra(Modelo * modelo,double * x, double *y) {
	shared_ptr<Minimapa> mapa(new Minimapa(modelo));
	this->mapa= mapa;
	shared_ptr<Textura> text(new Textura());
	this->texto = text;
	shared_ptr<RecursoVista> oro(new RecursoVista());
	shared_ptr<RecursoVista> madera(new RecursoVista());
	shared_ptr<RecursoVista> piedra(new RecursoVista());
	shared_ptr<RecursoVista> comida(new RecursoVista());
	this->oro=oro;
	this->madera=madera;
	this->piedra=piedra;
	this->comida = comida;
	this->x_ref=x;
	this->y_ref=y;
	this->referencia_y = modelo->juego->pantalla->getAlto()-mapa->altoMapa();
	this->font=NULL;
	this->font_chico = NULL;
	this->tamFont = 20;
	this->celda_mini = this->mapa->altoMapa()/ (modelo->mapa->getLargo()); //HARCODE
	int sobrante = this->mapa->altoMapa() % (modelo->mapa->getLargo());
	this->desfasaje = (double)sobrante/(double)(modelo->mapa->getLargo());
	shared_ptr<CambioDeCoordendas> trans(new CambioDeCoordendas(celda_mini,celda_mini));
	this->transformador = trans;
	shared_ptr<Textura> text2(new Textura());
	this->nombreJugador = text2;
	this->nombre = modelo->nombreJugador();
	this->x_comienzo_recurso=(this->mapa->anchoPantalla()-this->mapa->altoMapa())/5;
	this->id_edificio_creador=-1;
	this->x_datos = x_comienzo_recurso*2;
	this->x_lista = modelo->juego->conf->get_margen_scroll();
	this->seleccionable = false;
	this->lado_icono = 0;
}


void Barra::load(SDL_Renderer * renderer, string path, int ancho_por_celda,int alto_por_celda){
	plog::init(plog::warning, "Log.txt" );
	if (!this->cargar_archivo("img/papiro.jpg",renderer))
		LOG_WARNING << "Atencion no pudo cargar imagen de barra\n";
	if (!this->oro->imagen()->loadFromFile("img/oro.png",renderer))
			LOG_WARNING << "Atencion no pudo cargar imagen de barra\n";
	if (!this->piedra->imagen()->loadFromFile("img/piedra.png",renderer))
			LOG_WARNING << "Atencion no pudo cargar imagen de barra\n";
	if (!this->madera->imagen()->loadFromFile("img/madera.png",renderer))
			LOG_WARNING << "Atencion no pudo cargar imagen de barra\n";
	if (!this->comida->imagen()->loadFromFile("img/comida.gif",renderer))
				LOG_WARNING << "Atencion no pudo cargar imagen de barra\n";
	if (!this->mapa->inicializar(renderer))
		LOG_WARNING << "Atencion no pudo inicializar Minimapa\n";
	font = TTF_OpenFont( path.c_str(), 25 );
		if( font == NULL ){
			LOG_WARNING << "Failed to load font!%s\n" , TTF_GetError();
		}
	font_chico = TTF_OpenFont(path.c_str(), 15);
	if (font_chico == NULL) {
		LOG_WARNING << "Failed to load font_chcia!%s\n", TTF_GetError();
	}
	this->ancho_por_celda = ancho_por_celda;
	this->alto_por_celda = alto_por_celda;
	this->lado_icono = TTF_FontHeight(font);

}

void Barra::setDisplay(DatosSeleccionado datos){
	this->display= datos;
	this->listaCreables.clear();
}
void  Barra::actualizar(Jugador * jugador,vector<Personaje *> personajes,Entidad* entidad){
	oro->cambiarCant(jugador->recursosJugador()->cantOro());
	madera->cambiarCant(jugador->recursosJugador()->cantMadera());
	piedra->cambiarCant(jugador->recursosJugador()->cantPiedra());
	comida->cambiarCant(jugador->recursosJugador()->cantComida());
	int size = personajes.size();
	if (size !=0){
		cargarIconos(personajes);
		if (size == 1 && personajes[0]->puedeCrear()){
			if (jugador->raza == personajes[0]->get_raza()){
				this->id_edificio_creador = -1;
				this->setListaCreables(jugador->devolverEdificiosCreables());
			}
		}
		return;
	}else if(entidad){
		if (entidad->estaConstruida() && (jugador->raza==entidad->get_raza())){
			this->id_edificio_creador = entidad->getId();
			this->setListaCreables(entidad->devolverPersonajesCreables());
		}
	}else{
		this->seleccionable=false;
	}
	this->iconos.clear();


}

void Barra::cargarIconos(vector<Personaje*> personajes){
	if (this->iconos.empty()){
		vector<Personaje*>::iterator it = personajes.begin();
		for (;it!=personajes.end();it++) {
			this->iconos.push_back((*it)->objetoMapa->icono);
		}
	}

}

void Barra::dibujarIconos(SDL_Renderer* renderer){
	vector<string>::iterator it = this->iconos.begin();
	int x_inicio = this->x_datos;
	int x_acumulado = x_inicio;
	int y_escalar = (this->mapa->altoMapa()/lado_icono);
	int y = this->referencia_y + 2*this->mapa->altoMapa()/y_escalar;
	int corrimiento = lado_icono;
	int largo_total = (this->mapa->anchoPantalla() - this->mapa->altoMapa()
			- this->x_comienzo_recurso) / 2;
	SDL_Rect rect = {0,0,corrimiento,corrimiento};

	for(;it!=iconos.end();it++){
		shared_ptr<Textura> icono(new Textura());
		if (icono->loadFromFile((*it),renderer)){
			icono->render(x_acumulado,y,&rect,renderer);
			x_acumulado+=corrimiento;
			if (x_acumulado-x_inicio > largo_total){
				x_acumulado = x_inicio;
				y+= corrimiento;
			}
		}

	}

}
//tengo q hacer actualizar de jugador no de personaje
void Barra::setListaCreables(map<string,ObjetoMapa*> tipos){
	this->seleccionable= true;
	this->listaCreables = tipos;
}

void Barra::renderTexto(SDL_Renderer*renderer){

	int x_oro,x_piedra,x_madera,x_comida;
	x_oro = this->x_comienzo_recurso;
	x_piedra =imprimirNumeroDeRecurso(renderer,this->oro,x_oro);
	x_madera =imprimirNumeroDeRecurso(renderer,this->piedra,x_piedra);
	x_comida = imprimirNumeroDeRecurso(renderer,this->madera,x_madera);
	imprimirNumeroDeRecurso(renderer,this->comida,x_comida);

	SDL_Color color = this->mapa->paleta(BLANCO);
	if (cargarTexto(renderer,color,this->nombreJugador,this->nombre)){
		imprimirTexto(0,0,renderer,this->nombreJugador);
	}


	this->imprimirLista(renderer);
}
void Barra::imprimirLista(SDL_Renderer* renderer){
	std::map<string,ObjetoMapa*>::iterator it;
	if (seleccionable){
		int y = this->referencia_y + TTF_FontHeight(font);
		for (it = this->listaCreables.begin(); it != this->listaCreables.end();
				++it) {

			shared_ptr<Textura> icono(new Textura());
			if (icono->loadFromFile(it->second->icono,renderer)){
				SDL_Rect rect ={x_lista,y,lado_icono,lado_icono};
				icono->renderEx(0,NULL,&rect,renderer,NULL);

			}

			shared_ptr<Textura> creable(new Textura());
			//oss es un stream en el q cargo el precio
			std::ostringstream oss;
			oss << it->second->oro <<"/"<< it->second->piedra <<"/"<< it->second->madera <<"/"<< it->second->comida;

			if (cargarTextoChico(renderer, this->mapa->paleta(NEGRO), creable,
					oss.str())){
				imprimirTexto(x_lista+lado_icono,y,renderer,creable);
			}

			y+=TTF_FontHeight(font);
		}
	}
}
bool Barra::enIcono(int pixel_x){
	return (0 < pixel_x-x_lista && pixel_x-x_lista < lado_icono);
}
/*bool Barra::enSectorMapa(int pixel_x, int pixel_y){
	int seleccion_x = pixel_x - this->mapa->anchoPantalla()-this->mapa->altoMapa();
	int seleccion_y = pixel_y - this->referencia_y;
	if (seleccion_x > 0 && seleccion_y > 0){
		seleccion_x += this->mapa->altoMapa()/2;
		//TODO
	}
}*/
tuple<ObjetoMapa*,int> Barra::seleccionar(int pixel_x, int pixel_y){

	if ( enIcono(pixel_x) && seleccionable ){
		int seleccion = (pixel_y-this->referencia_y)/lado_icono - 1;
		//si es un indice positivo y dentro del rango
		if (seleccion>=0 && ((this->listaCreables.size())>(seleccion))){
			std::map<string,ObjetoMapa*>::iterator it;
			int x = 0;
			for (it =listaCreables.begin(); it != this->listaCreables.end();++it){
				if (x==(seleccion)){
					tuple<ObjetoMapa*,int> foo (it->second,this->id_edificio_creador);
					return foo;
				}
				x++;
			}
		}
	}
	tuple<ObjetoMapa*,int> nada (NULL,0);
	return nada;
}
int Barra::obtenerYDondeSeDibuja(){
	return this->referencia_y;
}
int Barra::imprimirNumeroDeRecurso(SDL_Renderer* renderer, shared_ptr<RecursoVista> recurso, int x_ref){
	int largo = lado_icono;
	int ancho=largo;//cuadrado
	SDL_Color color = this->mapa->paleta(BLANCO);
	SDL_Rect rect= {x_ref,referencia_y,ancho,largo};
	if (cargarTexto(renderer,color,texto,to_string(recurso->cantidad()))){
		imprimirTexto(x_ref-texto->getWidth(),referencia_y,renderer,texto);
	}
	recurso->imagen()->renderEx(0,NULL,&rect,renderer,NULL);
	return x_ref+ancho+this->x_comienzo_recurso;
}
bool Barra::cargarTexto(SDL_Renderer* renderer,SDL_Color color, shared_ptr<Textura> textura, string display){
	return this->cargarTextoConFont(renderer,color,textura,display,this->font);
}

bool Barra::cargarTextoChico(SDL_Renderer* renderer,SDL_Color color, shared_ptr<Textura> textura, string display){
	return this->cargarTextoConFont(renderer,color,textura,display,this->font_chico);
}
bool Barra::cargarTextoConFont(SDL_Renderer* renderer,SDL_Color color, shared_ptr<Textura> textura, string display,TTF_Font* font){
	plog::init(plog::warning, "Log.txt");
	bool success = true;
	if (!textura->loadFromRenderedText(display.c_str(), color, font,
			renderer)) {
		LOG_WARNING << "Atencion no pudo escribir texto\n";
		success = false;
	}
	return success;
}
void Barra::imprimirTexto(int x, int y,SDL_Renderer* renderer,shared_ptr<Textura> textura){
	textura->render(x,y,NULL,renderer);
}
void Barra::render(SDL_Renderer*renderer){
	SDL_Rect rect = {0,this->referencia_y,this->mapa->anchoPantalla(),this->mapa->altoMapa()};
	this->textura->renderEx(0,NULL,&rect,renderer,NULL);
	this->renderTexto(renderer);
	this->dibujarDatosSeleccionados(renderer);
	this->dibujarIconos(renderer);
	this->mapa->render(renderer);
	this->dibujarDondeMiro(renderer);

}
void Barra::dibujarDatosSeleccionados(SDL_Renderer* renderer){
	switch (this->display.getTipoSeleccionado()){
	case RECURSO:
		this->dibujarDatosRecurso(renderer);
		break;
	case EDIFICIO:
		this->dibujarDatosEdificio(renderer);
		break;
	case PERSONAJE:
		this->dibujarDatosPersonaje(renderer);
		break;
	default:
		break;
	}
}
void Barra::dibujarDatosRecurso(SDL_Renderer* renderer){
	shared_ptr<Textura> nombre(new Textura()),recurso(new Textura());
	int y_escalar = (this->mapa->altoMapa()/lado_icono);
	int y = this->referencia_y + 2*this->mapa->altoMapa()/y_escalar;

	if (this->cargarTexto(renderer,this->mapa->paleta(NEGRO),nombre,this->display.getNombre())){
		this->imprimirTexto(this->x_datos,y,renderer,nombre);
	}

	if (this->cargarTexto(renderer, this->mapa->paleta(NEGRO), recurso,
			to_string(this->display.getRecurso()))) {
		this->imprimirTexto(this->x_datos, y+TTF_FontHeight(font), renderer, recurso);
	}
	//terminar display
	if (this->display.getRecurso()<=0){
		DatosSeleccionado datos;
		this->display = datos;
	}
}
void Barra::dibujarDatosEdificio(SDL_Renderer* renderer){
	shared_ptr<Textura> nombre(new Textura());
	int y_escalar = (this->mapa->altoMapa() / lado_icono);
	int x, y = this->referencia_y + 2*this->mapa->altoMapa()/y_escalar;
	if (this->cargarTexto(renderer, this->mapa->paleta(NEGRO), nombre,
			this->display.getNombre())) {
		this->imprimirTexto(this->x_datos, y, renderer, nombre);
	}
	this->dibujarCargaDeBarra(this->display.getVidaActual(),
			this->display.getVidaTotal(), this->mapa->paleta(VERDE),
			this->mapa->paleta(ROJO), renderer, y + nombre->getHeight());

	if (this->display.getConstruccionActual()>0){
		this->dibujarCargaDeBarra(
				this->display.getConstruccionTotal()
						- this->display.getConstruccionActual(),
				this->display.getConstruccionTotal(),
				this->mapa->paleta(AMARILLO), this->mapa->paleta(BLANCO),
				renderer, y + nombre->getHeight() + TTF_FontHeight(font_chico));
	}

	//terminar display
	if (this->display.getVidaActual()<=0){
		DatosSeleccionado datos;
		this->display = datos;
	}


}
void Barra::dibujarDatosPersonaje(SDL_Renderer* renderer){
	shared_ptr<Textura> nombre(new Textura()), jugador(new Textura());
	int y_escalar = (this->mapa->altoMapa() / lado_icono);
	int x, y = this->referencia_y + 2*this->mapa->altoMapa()/y_escalar;

	if (this->cargarTexto(renderer, this->mapa->paleta(NEGRO), nombre,
			this->display.getNombre())) {
		this->imprimirTexto(this->x_datos+lado_icono, y, renderer, nombre);
	}

	if (this->cargarTexto(renderer, this->mapa->paleta(NEGRO), jugador,
			this->display.getJugador())) {
		this->imprimirTexto(this->x_datos+nombre->getWidth()+lado_icono*2, y, renderer, jugador);
	}

	this->dibujarCargaDeBarra(this->display.getVidaActual(),
			this->display.getVidaTotal(), this->mapa->paleta(VERDE),
			this->mapa->paleta(ROJO), renderer, y + nombre->getHeight());
	//terminar display
	if (this->display.getVidaActual()<=0){
			DatosSeleccionado datos;
			this->display = datos;
		}


}

void Barra::dibujarCargaDeBarra(int actual, int total,SDL_Color primero,SDL_Color segundo,SDL_Renderer* renderer,int y){
	if (total!=0){
		int largo_total = (this->mapa->anchoPantalla() - this->mapa->altoMapa()
				- this->x_comienzo_recurso) / 2;
		int largo_actual = (largo_total * actual) / total;
		SDL_SetRenderDrawColor(renderer, primero.r, primero.g, primero.b,
				primero.a);
		SDL_Rect rect = { this->x_datos, y, largo_actual,
				TTF_FontHeight(font_chico) };
		SDL_RenderFillRect(renderer, &rect);
		SDL_SetRenderDrawColor(renderer, segundo.r, segundo.g, segundo.b,
				segundo.a);
		SDL_Rect rect2 = { this->x_datos + largo_actual, y,
				largo_total - largo_actual, TTF_FontHeight(font_chico) };
		SDL_RenderFillRect(renderer, &rect2);
		shared_ptr<Textura> numeros(new Textura());
		std::ostringstream oss;
		oss <<actual<<"/"<<total;
		if (cargarTextoChico(renderer,this->mapa->paleta(NEGRO),numeros,oss.str())){
			this->imprimirTexto(this->x_datos+largo_total-numeros->getWidth(),y,renderer,numeros);
		}
	}

}
void Barra::dibujarDondeMiro(SDL_Renderer * renderer){
	int x;
	int y;
	this->transformador->transformar_isometrica_pantalla(*x_ref, *y_ref, x, y);

	double x_corregido, y_corregido;
	x_corregido = (double) x + (double) x / celda_mini * this->desfasaje;
	y_corregido = (double) y + (double) y / celda_mini * this->desfasaje;
	x_corregido += this->mapa->anchoPantalla() - this->mapa->altoMapa() / 2;
	y_corregido += this->referencia_y;
	double celdas_por_ancho = (double) this->mapa->anchoPantalla() / ancho_por_celda;
	double celdas_por_alto = (double) (this->mapa->altoMapa() * 2) / alto_por_celda;
	double celdas_alto_corregido = celdas_por_alto * (1 + desfasaje);
	double celdas_ancho_corregido = celdas_por_ancho * (1 + desfasaje);
	SDL_Rect rect = { x_corregido, y_corregido, (celdas_ancho_corregido)
			* celda_mini, (celdas_alto_corregido) * celda_mini };
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderDrawRect(renderer, &rect);
}
void Barra::closeFont(){
	TTF_CloseFont(this->font);
	this->font = NULL;
	TTF_CloseFont(this->font_chico);
	this->font_chico=NULL;

}
Barra::~Barra() {

}

