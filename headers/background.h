#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <vector>

#include "sprite.h"

class background : public sprite
{
public:
	// Set draw order to default to lower (so it's in the background)
	background(actor* owner, int drawOrder = 10);
	// Update/draw overriden from parent
	void update(float deltaTime) override;
	void draw(SDL_Renderer* renderer) override;
	// Set the textures used for the background
	void setBGTextures(const std::vector<SDL_Texture*>& textures);
	// Get/set screen size and scroll speed
	void setScreenSize(const vector2& size) { mScreenSize = size; }
	void setScrollSpeed(float speed) { mScrollSpeed = speed; }
	float getScrollSpeed() const { return mScrollSpeed; }
private:
	// Struct to encapsulate each bg image and its offset
	struct BGTexture
	{
		SDL_Texture* mTexture;
		vector2 mOffset;
	};
	std::vector<BGTexture> mBGTextures;
	vector2 mScreenSize;
	float mScrollSpeed;
};

#endif
