#ifndef CIRCLECOMP_H
#define CIRCLECOMP_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "component.h"

class circle : public component
{
public:
	// (Lower draw order corresponds with further back)
	circle(actor* owner);
	void setRadius(float radius){ mRadius = radius; }
	float getRadius() const { return mRadius; }

	const vector2 getCenter() const;

private:
	float mRadius;
};

#endif
