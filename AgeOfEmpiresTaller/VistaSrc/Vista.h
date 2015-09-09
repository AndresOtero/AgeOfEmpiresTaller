/*
 * Vista.h
 *
 *  Created on: 9 de set. de 2015
 *      Author: andres
 */
#include "stdlib.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "../VistaSrc/LTexture.h"
#ifndef VISTA_H_
#define VISTA_H_

class Vista {
	//The window we'll be rendering to
	SDL_Window* gWindow = NULL;
	//The window renderer
	SDL_Renderer* gRenderer = NULL;
	//Walking animation
	//int WALKING_ANIMATION_FRAMES = 4;
	SDL_Rect gSpriteClips[ 4 ];
	LTexture gSpriteSheetTexture;
public:
	Vista();
	bool init();
	bool loadMedia();
	int run();
	virtual ~Vista();
};

#endif /* VISTA_H_ */
