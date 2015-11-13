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

Barra::Barra(Modelo * modelo,double * x, double *y) {
	shared_ptr<Minimapa> mapa(new Minimapa(modelo));
	this->mapa= mapa;
	shared_ptr<Textura> text(new Textura());
	this->texto = text;
	shared_ptr<RecursoVista> oro(new RecursoVista());
	shared_ptr<RecursoVista> madera(new RecursoVista());
	shared_ptr<RecursoVista> piedra(new RecursoVista());
	this->oro=oro;
	this->madera=madera;
	this->piedra=piedra;
	this->x_ref=x;
	this->y_ref=y;
	this->referencia_y = modelo->juego->pantalla->getAlto()-mapa->altoMapa();
	this->font=NULL;
	this->tamFont = 20;
	this->celda_mini = this->mapa->altoMapa()/ (modelo->mapa->getLargo()); //HARCODE
	int sobrante = this->mapa->altoMapa() % (modelo->mapa->getLargo());
	this->desfasaje = (double)sobrante/(double)(modelo->mapa->getLargo());
	shared_ptr<CambioDeCoordendas> trans(new CambioDeCoordendas(celda_mini,celda_mini));
	this->transformador = trans;
	shared_ptr<Textura> text2(new Textura());
	this->nombreJugador = text2;
	this->nombre = modelo->nombreJugador();
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
	if (!this->mapa->inicializar(renderer))
		LOG_WARNING << "Atencion no pudo inicializar Minimapa\n";
	font = TTF_OpenFont( path.c_str(), 25 );
		if( font == NULL ){
			LOG_WARNING << "Failed to load font!%s\n" , TTF_GetError();
		}
	this->ancho_por_celda = ancho_por_celda;
	this->alto_por_celda = alto_por_celda;

}

void Barra::setDisplay(string display){
	this->display= display;
}
void  Barra::actualizar(Jugador * jugador,vector<Personaje *> personajes){
	oro->cambiarCant(jugador->recursosJugador()->cantOro());
	madera->cambiarCant(jugador->recursosJugador()->cantMadera());
	piedra->cambiarCant(jugador->recursosJugador()->cantPiedra());
	if (personajes.size()==1){
		if (personajes[0]->puedeCrear()){
			this->setListaCreables(jugador->devolverEdificiosCreables());
		}
	}else{
		//no existe
		this->seleccionable= false;
	}
}
//tengo q hacer actualizar de jugador no de personaje
void Barra::setListaCreables(map<string,ObjetoMapa*> tipos){
	this->seleccionable= true;
	this->listaCreables = tipos;
}

void Barra::renderTexto(SDL_Renderer*renderer){
	if (!this->display.empty()){
		SDL_Color color = this->mapa->paleta(NEGRO);
		if (cargarTexto(renderer,color,this->texto, this->display)){
			imprimirTexto(this->mapa->anchoPantalla()/4,referencia_y+this->mapa->altoMapa()/2,
							renderer,this->texto);
		}

	}

	int x_oro,x_piedra,x_madera;
	x_oro = this->mapa->anchoPantalla()/4;
	x_piedra =imprimirNumeroDeRecurso(renderer,this->oro,x_oro);
	x_madera =imprimirNumeroDeRecurso(renderer,this->piedra,x_piedra);
	imprimirNumeroDeRecurso(renderer,this->madera,x_madera);

	SDL_Color color = this->mapa->paleta(BLANCO);
	if (cargarTexto(renderer,color,this->nombreJugador,this->nombre)){
		imprimirTexto(0,0,renderer,this->nombreJugador);
	}

	//TODO
	this->imprimirLista(renderer);
}
void Barra::imprimirLista(SDL_Renderer* renderer){
	std::map<string,ObjetoMapa*>::iterator it;
	//int x = 0;
	if (seleccionable){
		int y = this->referencia_y + TTF_FontHeight(font);
		for (it = this->listaCreables.begin(); it != this->listaCreables.end();
				++it) {
			//ver si imprime esto
			shared_ptr<Textura> creable(new Textura());
			if (cargarTexto(renderer, this->mapa->paleta(NEGRO), creable,
					it->first)){
				imprimirTexto(0,y,renderer,creable);
			}
			y+=TTF_FontHeight(font);
		}
	}
}

string Barra::seleccionar(int pixel_x, int pixel_y){
	if (pixel_x < PIXELESDIGITOS){
		int seleccion = (pixel_y-this->referencia_y)/TTF_FontHeight(font) - 1;
		//si es un indice positivo y dentro del rango
		if (seleccion>=0 && ((this->listaCreables.size())>(seleccion))){
			std::map<string,ObjetoMapa*>::iterator it;
			int x = 0;
			for (it =listaCreables.begin(); it != this->listaCreables.end();++it){
				if (x==(seleccion)){
					return it->first;
				}
				x++;
			}
		}
	}
	return "";
}
int Barra::obtenerYDondeSeDibuja(){
	return this->referencia_y;
}
int Barra::imprimirNumeroDeRecurso(SDL_Renderer* renderer, shared_ptr<RecursoVista> recurso, int x_ref){
	int largo = TTF_FontHeight(font);
	int ancho=largo;//cuadrado
	SDL_Color color = this->mapa->paleta(BLANCO);
	SDL_Rect rect= {x_ref,referencia_y,ancho,largo};
	if (cargarTexto(renderer,color,texto,to_string(recurso->cantidad()))){
		imprimirTexto(x_ref-texto->getWidth(),referencia_y,renderer,texto);
	}
	recurso->imagen()->renderEx(0,NULL,&rect,renderer,NULL);
	return x_ref+ancho+PIXELESDIGITOS;
}
bool Barra::cargarTexto(SDL_Renderer* renderer,SDL_Color color, shared_ptr<Textura> textura, string display){
	plog::init(plog::warning, "Log.txt" );
	bool success = true;
	if( !textura->loadFromRenderedText( display.c_str(), color,this->font,renderer ) ){
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
	this->mapa->render(renderer);
	this->dibujarDondeMiro(renderer);

}

void Barra::dibujarDondeMiro(SDL_Renderer * renderer){
	int x;
	int y;
	this->transformador->transformar_isometrica_pantalla(*x_ref, *y_ref, x, y);
	//SUPER HARCODE funciona en parte del mapa
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
}
Barra::~Barra() {

}

