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
	r = 0;
	g= 0;
	b = 0;
}

Textura::~Textura() {
	free();
}

bool Textura::loadFromFile(std::string path, SDL_Renderer* gRenderer) {
	free();

	SDL_Texture* newTexture = NULL;
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL) {
		//LOG_WARNING << "No se pudo cargar: %s. SDL_image Error: %s\n", path.c_str(),
				//IMG_GetError();
	} else {
		//SDL_SetColorKey(loadedSurface, SDL_TRUE,						SDL_MapRGB(loadedSurface->format, 0xFF, 0xFF, 0xFF));

		newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
		if (newTexture == NULL) {
			//LOG_WARNING << "No se pudo cargar la textura: %s. SDL Error: %s\n",
					//path.c_str(), SDL_GetError();
		} else {
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}

		SDL_FreeSurface(loadedSurface);
	}
	SDL_GetTextureColorMod(newTexture,&r,&g,&b);
    SDL_SetTextureBlendMode( mTexture, SDL_BLENDMODE_BLEND );
	mTexture = newTexture;
	return mTexture != NULL;
}
void Textura::oscurecer(){
	SDL_SetTextureColorMod(this->mTexture,100,100,100);
}

void Textura::reiniciar(){

	SDL_SetTextureColorMod(this->mTexture,r,g,b);
}
void Textura::congelar(){
	unsigned char a =r+g+b/3;
	SDL_SetTextureColorMod(this->mTexture,a,a,a);

}

void Textura::setColor(Uint8 r,Uint8 g,Uint8 b){
	SDL_SetTextureColorMod(this->mTexture,r,g,b);
}
void Textura::descongelar(){
	SDL_SetTextureColorMod(this->mTexture,r,g,b);

}
;
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
void Textura::setBlendMode( SDL_BlendMode blending )
{
    SDL_SetTextureBlendMode( mTexture, blending );
}

void Textura::setAlpha( Uint8 alpha )
{	 SDL_SetTextureAlphaMod( mTexture, alpha );
}

void Textura::render(int x, int y, SDL_Rect* clip, SDL_Renderer* gRenderer) {
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };

	if (clip != NULL) {
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	SDL_RenderCopy(gRenderer, mTexture, clip, &renderQuad);
}

void Textura::renderEx(double angle, SDL_Rect* srcrect, SDL_Rect* dsrect,SDL_Renderer* renderer,SDL_Point *point){

	SDL_RenderCopyEx(renderer,this->mTexture,srcrect,dsrect,angle,point,SDL_FLIP_NONE);
}
bool Textura::loadFromRenderedText( string textureText, SDL_Color textColor, TTF_Font *gFont, SDL_Renderer* renderer)
{
	plog::init(plog::warning, "Log.txt" );
	//Get rid of preexisting texture
	free();
    //Render text surface
    SDL_Surface* textSurface = TTF_RenderText_Solid( gFont, textureText.c_str(), textColor );
    if( textSurface == NULL )
    {
		LOG_WARNING << "Unable to render text surface! SDL_ttf\n";
    }
    else
    {
        //Create texture from surface pixels
        mTexture = SDL_CreateTextureFromSurface( renderer, textSurface );
        if( mTexture == NULL )
        {
            LOG_WARNING << "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() ;
        }
        else
        {
            //Get image dimensions
            mWidth = textSurface->w;
            mHeight = textSurface->h;
        }

        //Get rid of old surface
        SDL_FreeSurface( textSurface );
    }

    //Return success
    return mTexture != NULL;
}


bool Textura::createBlank( int width, int height, SDL_TextureAccess access,SDL_Renderer *renderer)
{
    //Create uninitialized texture
    mTexture = SDL_CreateTexture( renderer, SDL_PIXELFORMAT_RGBA8888, access, width, height );
    if( mTexture == NULL )
    {
    	 LOG_WARNING << "Unable to create blank texture! SDL Error: %s\n", SDL_GetError() ;
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
