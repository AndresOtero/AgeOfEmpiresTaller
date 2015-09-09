/*
 * LTexture.h
 *
 *  Created on: 9 de set. de 2015
 *      Author: andres
 */

#ifndef LTEXTURE_H_
#define LTEXTURE_H_

#include <string>
#include<SDL2/SDL.h>
#include <SDL2/SDL_image.h>
using namespace std;

class LTexture
{
	public:
		//Initializes variables
		LTexture();

		//Deallocates memory
		~LTexture();

		//Loads image at specified path
		bool loadFromFile( std::string path ,SDL_Renderer* gRenderer );

		//Deallocates texture
		void free();

		//Set color modulation
		void setColor( Uint8 red, Uint8 green, Uint8 blue );

		//Set blending
		void setBlendMode( SDL_BlendMode blending );

		//Set alpha modulation
		void setAlpha( Uint8 alpha );

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
#endif /* LTEXTURE_H_ */
