#include <iostream>

#include "math.h"
#include "sprite.h"
#include "fonts.h"
#include "circle.h"
#include "actor.h"
#include "redpad.h"
#include "bluepad.h"
#include "ball.h"
#include "game.h"

font::font(actor* owner, int drawOrder)
:component(owner),mTexture(nullptr),mDrawOrder(drawOrder)
,mTexWidth(0),mTexHeight(0)
{
	//mOwner->getGame()->addSprite(this);
}

font::~font()
{
	std::cout << "remove font" << std::endl;
	//mOwner->getGame()->removeSprite(this);
}

void font::draw(SDL_Renderer* renderer)
{
	if (mTexture)
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
 }

void font::setTexture(SDL_Texture* texture)
{
	mTexture = texture;
	// Set width/height
	SDL_QueryTexture(texture, nullptr, nullptr, &mTexWidth, &mTexHeight);
}

bool font::loadFromFile( std::string path )
{
	//Get rid of preexisting texture
//	free();

	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == NULL )
	{
		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
	}
	else
	{
		//Color key image
		SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );

		//Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
		if( newTexture == NULL )
		{
			printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		}
		else
		{
			//Get image dimensions
			mTexWidth = loadedSurface->w;
			mTexHeight = loadedSurface->h;
		}

		//Get rid of old loaded surface
		SDL_FreeSurface( loadedSurface );
	}

	//Return success
	mTexture = newTexture;
	return mTexture != NULL;
}

bool font::loadFromRenderedText( std::string textureText, SDL_Color textColor )
{
	//Get rid of preexisting texture
//	free();

	//Render text surface
	SDL_Surface* textSurface = TTF_RenderText_Solid( gFont, textureText.c_str(), textColor );
	if( textSurface == NULL )
	{
		printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
	}
	else
	{
		//Create texture from surface pixels
        mTexture = SDL_CreateTextureFromSurface( gRenderer, textSurface );
		if( mTexture == NULL )
		{
			printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
		}
		else
		{
			//Get image dimensions
			mTexWidth = textSurface->w;
			mTexHeight = textSurface->h;
		}

		//Get rid of old surface
		SDL_FreeSurface( textSurface );
	}
	
	//Return success
	return mTexture != NULL;
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
