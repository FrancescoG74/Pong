#ifndef SPRITE_H
#define SPRITE_H

#include <vector>

#include "sprite.h"

class anim : public sprite
{
public:
	anim(actor* owner, int drawOrder = 100);
	// Update animation every frame (overriden from component)
	void update(float deltaTime) override;
	// Set the textures used for animation
	void setAnimTextures(const std::vector<SDL_Texture*>& textures);
	// Set/get the animation FPS
	float getAnimFPS() const { return mAnimFPS; }
	void setAnimFPS(float fps) { mAnimFPS = fps; }
private:
	// All textures in the animation
	std::vector<SDL_Texture*> mAnimTextures;
	// Current frame displayed
	float mCurrFrame;
	// Animation frame rate
	float mAnimFPS;
};

#endif
