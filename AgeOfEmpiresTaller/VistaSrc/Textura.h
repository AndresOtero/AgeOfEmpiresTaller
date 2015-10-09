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

		void setAsRenderTarget(SDL_Renderer * renderer);
		//Renders texture at given point
		void render( int x, int y, SDL_Rect* clip ,SDL_Renderer* gRenderer );
		void renderEx(double angle, SDL_Rect* srcrect, SDL_Rect* dsrect,SDL_Renderer* renderer);
		bool createBlank(int width, int height, SDL_TextureAccess access,SDL_Renderer *renderer);
		//Gets image dimensions
		int getWidth();
		int getHeight();

	private:
		//The actual hardware texture
		SDL_Texture* mTexture;

		//Image dimensions
		int mWidth;
		int mHeight;
};
#endif /* Textura_H_ */
