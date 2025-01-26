#ifndef FONTCOMP_H
#define FONTCOMP_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

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
protected:
	SDL_Texture* mTexture;
	int mDrawOrder;
	int mTexWidth;
	int mTexHeight;
};

#endif
