/*
 * Textura.cpp
 *
 *  Created on: 9 de set. de 2015
 *      Author: andres
 */

#include "Textura.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string.h>
#include <plog/Log.h>


Textura::Textura() {
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
}

Textura::~Textura() {
	free();
}

bool Textura::loadFromFile(std::string path, SDL_Renderer* gRenderer) {
	free();

	SDL_Texture* newTexture = NULL;

	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL) {
		LOG_WARNING << "No se pudo cargar: %s. SDL_image Error: %s\n", path.c_str(),
				IMG_GetError();

	} else {
		SDL_SetColorKey(loadedSurface, SDL_TRUE,
				SDL_MapRGB(loadedSurface->format, 0xFF, 0xFF, 0xFF));

		newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
		if (newTexture == NULL) {
			LOG_WARNING << "No se pudo cargar la textura: %s. SDL Error: %s\n",
					path.c_str(), SDL_GetError();
		} else {
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}

		SDL_FreeSurface(loadedSurface);
	}

	mTexture = newTexture;
	return mTexture != NULL;
}

void Textura::free() {
	if (mTexture != NULL) {
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}
void Textura::setAsRenderTarget(SDL_Renderer* renderer)
{
    //Make self render target
    SDL_SetRenderTarget( renderer, mTexture );
}
void Textura::render(int x, int y, SDL_Rect* clip, SDL_Renderer* gRenderer) {
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };

	if (clip != NULL) {
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	SDL_RenderCopy(gRenderer, mTexture, clip, &renderQuad);
}

void Textura::renderEx(double angle, SDL_Rect* srcrect, SDL_Rect* dsrect,SDL_Renderer* renderer){

	SDL_RenderCopyEx(renderer,this->mTexture,srcrect,dsrect,angle,NULL,SDL_FLIP_NONE);
}

bool Textura::createBlank( int width, int height, SDL_TextureAccess access,SDL_Renderer *renderer)
{
    //Create uninitialized texture
    mTexture = SDL_CreateTexture( renderer, SDL_PIXELFORMAT_RGBA8888, access, width, height );
    if( mTexture == NULL )
    {
        printf( "Unable to create blank texture! SDL Error: %s\n", SDL_GetError() );
    }
    else
    {
        mWidth = width;
        mHeight = height;
    }

    return mTexture != NULL;
}


int Textura::getWidth() {
	return mWidth;
}

int Textura::getHeight() {
	return mHeight;
}
