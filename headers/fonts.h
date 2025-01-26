#ifndef FONTCOMP_H
#define FONTCOMP_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "component.h"

class font : public component
{
public:
	// (Lower draw order corresponds with further back)
	font(actor* owner, int drawOrder = 100);
	~font();

	virtual void draw(SDL_Renderer* renderer);
	virtual void setTexture(SDL_Texture* texture);

	int getDrawOrder() const { return mDrawOrder; }
//	void setDrawOrder(int drawOrder) { mDrawOrder = drawOrder; }

	int getTexHeight() const { return mTexHeight; }
	int getTexWidth() const { return mTexWidth; }

	//Loads image at specified path
	bool loadFromFile( std::string path );
		
	//Creates image from font string
	bool loadFromRenderedText( std::string textureText, SDL_Color textColor );

	//Set color modulation
	void setColor( Uint8 red, Uint8 green, Uint8 blue );

	//Set blending
	void setBlendMode( SDL_BlendMode blending );

	//Set alpha modulation
	void setAlpha( Uint8 alpha );
		
	//Renders texture at given point
	void render( int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE );

protected:
	SDL_Texture* mTexture;
	int mDrawOrder;
	int mTexWidth;
	int mTexHeight;

private:
	//The window renderer
	//SDL_Renderer* gRenderer = NULL;

	//Globally used font
	//TTF_Font* gFont = NULL;

};

#endif
