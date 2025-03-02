#include <iostream>

#include "math.h"
#include "sprite.h"
#include "font.h"
#include "circle.h"
#include "actor.h"
#include "redpad.h"
#include "bluepad.h"
#include "ball.h"
#include "score.h"
#include "game.h"

font::font(actor* owner, int drawOrder)
:component(owner),mTexture(nullptr),mDrawOrder(drawOrder)
,mTexWidth(0),mTexHeight(0)
{
	mOwner->getGame()->addFont(this);
}

font::~font()
{
	std::cout << "remove font" << std::endl;
	mOwner->getGame()->removeFont(this);
}

void font::draw(SDL_Renderer* renderer)
{
/*	if (mTexture)
	{
		SDL_Rect r;
		// Scale the width/height by owner's scale
		r.w = static_cast<int>(mTexWidth * mOwner->getScale());
		r.h = static_cast<int>(mTexHeight * mOwner->getScale());
		// Center the rectangle around the position of the owner
		r.x = static_cast<int>(mOwner->getPosition().x - r.w / 2);
		r.y = static_cast<int>(mOwner->getPosition().y - r.h / 2);

		// Draw (have to convert angle from radians to degrees, and clockwise to counter)
		SDL_RenderCopyEx(renderer,mTexture,nullptr,&r,
			-Math::ToDegrees(mOwner->getRotation()),nullptr,SDL_FLIP_NONE);
	}
*/
}

void font::setTexture(SDL_Texture* texture)
{
	mTexture = texture;
	// Set width/height
	SDL_QueryTexture(texture, nullptr, nullptr, &mTexWidth, &mTexHeight);
}

void font::setColor( Uint8 red, Uint8 green, Uint8 blue )
{
	//Modulate texture rgb
	SDL_SetTextureColorMod( mTexture, red, green, blue );
}

void font::setBlendMode( SDL_BlendMode blending )
{
	//Set blending function
	SDL_SetTextureBlendMode( mTexture, blending );
}
		
void font::setAlpha( Uint8 alpha )
{
	//Modulate texture alpha
	SDL_SetTextureAlphaMod( mTexture, alpha );
}
/*
void font::render( int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip )
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, mTexWidth, mTexHeight };

	//Set clip rendering dimensions
	if( clip != NULL )
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	//Render to screen
	SDL_RenderCopyEx( gRenderer, mTexture, clip, &renderQuad, angle, center, flip );
}
*/