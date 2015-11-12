/*
 * Textura.h
 *
 *  Created on: 9 de set. de 2015
 *      Author: andres
 */

#ifndef TEXTURA_H_
#define TEXTURA_H_

#include <string>
#include<SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
using namespace std;

class Textura
{
	public:
		Textura();
		~Textura();
		bool loadFromFile( std::string path ,SDL_Renderer* gRenderer );
		bool loadFromRenderedText( string textureText, SDL_Color textColor, TTF_Font *gFont, SDL_Renderer* renderer);
		void free();
        void setBlendMode( SDL_BlendMode blending );
        void setAlpha( Uint8 alpha );
        void setColor(Uint8 r , Uint8 g ,Uint8 b);
		void setAsRenderTarget(SDL_Renderer * renderer);
		//Renders texture at given point
		void render( int x, int y, SDL_Rect* clip ,SDL_Renderer* gRenderer );
		void renderEx(double angle, SDL_Rect* srcrect, SDL_Rect* dsrect,SDL_Renderer* renderer,SDL_Point *point);
		bool createBlank(int width, int height, SDL_TextureAccess access,SDL_Renderer *renderer);
		//Gets image dimensions
		int getWidth();
		int getHeight();
		//Para fog war
		void oscurecer();
		void reiniciar();
		//Para congelar un jugador
		void congelar();
		void descongelar();

	private:
		//The actual hardware texture
		SDL_Texture* mTexture;
		//Image dimensions
		int mWidth;
		int mHeight;
		unsigned char r,g,b;
};
#endif /* Textura_H_ */
