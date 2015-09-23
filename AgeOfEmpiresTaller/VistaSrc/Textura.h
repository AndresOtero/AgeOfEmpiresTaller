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
using namespace std;

class Textura
{
	public:
		Textura();
		~Textura();
		bool loadFromFile( std::string path ,SDL_Renderer* gRenderer );

		void free();


		//Renders texture at given point
		void render( int x, int y, SDL_Rect* clip ,SDL_Renderer* gRenderer );

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
