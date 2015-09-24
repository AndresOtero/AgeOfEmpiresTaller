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

void Textura::render(int x, int y, SDL_Rect* clip, SDL_Renderer* gRenderer) {
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };

	if (clip != NULL) {
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	SDL_RenderCopy(gRenderer, mTexture, clip, &renderQuad);
}

int Textura::getWidth() {
	return mWidth;
}

int Textura::getHeight() {
	return mHeight;
}
