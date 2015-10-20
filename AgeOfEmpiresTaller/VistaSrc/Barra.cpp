/*
 * BarraStatus.cpp
 *
 *  Created on: Oct 8, 2015
 *      Author: tobias
 */

#include "Barra.h"
#define PIXELESDIGITOS 200

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
	shared_ptr<CambioDeCoordendas> trans(new CambioDeCoordendas(celda_mini,celda_mini));
	this->transformador = trans;

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

}

void Barra::setDisplay(string display){
	this->display= display;
}
void  Barra::actualizar(Personaje * jugador){
	oro->cambiarCant(jugador->recursosJugador()->cantOro());
	madera->cambiarCant(jugador->recursosJugador()->cantMadera());
	piedra->cambiarCant(jugador->recursosJugador()->cantPiedra());
}

void Barra::renderTexto(SDL_Renderer*renderer){
	if (!this->display.empty()){
		SDL_Color color = this->mapa->paleta(NEGRO);
		cargarTexto(this->mapa->anchoPantalla()/4,referencia_y+this->mapa->altoMapa()/2,
				renderer,color,this->texto, this->display);
	}

	int x_oro,x_piedra,x_madera;
	x_oro = this->mapa->anchoPantalla()/4;
	x_piedra =imprimirNumeroDeRecurso(renderer,this->oro,x_oro);
	x_madera =imprimirNumeroDeRecurso(renderer,this->piedra,x_piedra);
	imprimirNumeroDeRecurso(renderer,this->madera,x_madera);
}

int Barra::imprimirNumeroDeRecurso(SDL_Renderer* renderer, shared_ptr<RecursoVista> recurso, int x_ref){
	int largo = TTF_FontHeight(font);
	int ancho=largo;//cuadrado
	SDL_Color color = this->mapa->paleta(BLANCO);
	SDL_Rect rect= {x_ref,referencia_y,ancho,largo};
	cargarTexto(x_ref, referencia_y,renderer,color,texto,to_string(recurso->cantidad()));
	recurso->imagen()->renderEx(0,NULL,&rect,renderer);
	return x_ref+ancho+PIXELESDIGITOS;
}
bool Barra::cargarTexto(int x,int y,SDL_Renderer* renderer,SDL_Color color, shared_ptr<Textura> textura, string display){
	plog::init(plog::warning, "Log.txt" );
	bool success = true;
	if( !textura->loadFromRenderedText( display.c_str(), color,this->font,renderer ) ){
			LOG_WARNING << "Atencion no pudo escribir texto\n";
			success = false;
		}
	else{
		textura->render(x-textura->getWidth(),y,NULL,renderer);
	}
	return success;
}

void Barra::render(SDL_Renderer*renderer){
	SDL_Rect rect = {0,this->referencia_y,this->mapa->anchoPantalla(),this->mapa->altoMapa()};
	this->textura->renderEx(0,NULL,&rect,renderer);
	this->renderTexto(renderer);
	this->mapa->render(renderer);
	this->dibujarDondeMiro(renderer);
}

void Barra::dibujarDondeMiro(SDL_Renderer * renderer){
	//5 a lo ancho
	//4 a lo alto
	int x;
	int y;
	this->transformador->transformar_isometrica_pantalla(*x_ref,*y_ref,x,y);
	x+=this->mapa->anchoPantalla()-this->mapa->altoMapa()/2+celda_mini/2;
	y+=this->referencia_y+celda_mini;
	SDL_Rect rect = {x,y,6*celda_mini,5*celda_mini};
	SDL_SetRenderDrawColor(renderer,0xFF,0xFF,0xFF,0xFF);
	SDL_RenderDrawRect(renderer,&rect);
}
void Barra::closeFont(){
	TTF_CloseFont(this->font);
	this->font = NULL;
}
Barra::~Barra() {

}

