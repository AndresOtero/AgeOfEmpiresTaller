/*
 * BarraStatus.cpp
 *
 *  Created on: Oct 8, 2015
 *      Author: tobias
 */

#include "Barra.h"

Barra::Barra(Modelo * modelo) {
	shared_ptr<Minimapa> mapa(new Minimapa(modelo));
	this->mapa= mapa;
	shared_ptr<Textura> text(new Textura());
	this->texto = text;
	shared_ptr<Textura> textO(new Textura());
	shared_ptr<Textura> textM(new Textura());
	shared_ptr<Textura> textP(new Textura());
	this->textOro=textO;
	this->textMadera = textM;
	this->textPiedra = textP;
	this->oro=0;this->piedra=0;this->madera=0;
	this->referencia_y = modelo->juego->pantalla->getAlto()-mapa->altoMapa();
	this->font=NULL;
	this->tamFont = 20;

}
void Barra::load(SDL_Renderer * renderer,TTF_Font* font){
	plog::init(plog::warning, "Log.txt" );
	if (!this->cargar_archivo("img/papiro.jpg",renderer))
		LOG_WARNING << "Atencion no pudo cargar imagen de barra\n";
	if (!this->mapa->inicializar(renderer))
		LOG_WARNING << "Atencion no pudo inicializar Minimapa\n";
	this->font =font;
}

void Barra::setDisplay(string display){
	this->display= display;
}
void Barra::renderTexto(SDL_Renderer*renderer){

	if (!this->display.empty()){

		SDL_Color color = { 0xFF, 0xFF, 0xFF };
		cargarTexto(120,referencia_y+50,renderer,color,this->texto, this->display);
	}
	SDL_Color color = { 0, 0, 0 };
	cargarTexto(100,referencia_y,renderer,color,this->textOro,to_string(oro));
	cargarTexto(150,referencia_y,renderer,color,this->textPiedra,to_string(piedra));
	cargarTexto(200, referencia_y,renderer,color,this->textMadera,to_string(madera));
}

bool Barra::cargarTexto(int x,int y,SDL_Renderer* renderer,SDL_Color color, shared_ptr<Textura> textura, string display){
	bool success = true;
	if( !textura->loadFromRenderedText( display.c_str(), color,this->font,renderer ) ){
			printf( "Failed to render text texture!\n" );
			success = false;
		}
	else{
		textura->render(x,y,NULL,renderer);
	}
	return success;
}

void Barra::render(SDL_Renderer*renderer){
	//renderTexto(renderer);
	SDL_Rect rect = {0,this->referencia_y,this->mapa->anchoPantalla(),this->mapa->altoMapa()};
	this->textura->renderEx(0,NULL,&rect,renderer);
	this->renderTexto(renderer);
	this->mapa->render(renderer);

}

Barra::~Barra() {
	TTF_CloseFont(this->font);
	this->font = NULL;
}

