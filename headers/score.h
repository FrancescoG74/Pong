#ifndef SCORE_H
#define SCORE_H

#include <vector>

#include "font.h"

class score : public font
{
public:
	// Set draw order to default to higher (so it's in the score)
	score(actor* owner, int drawOrder = 100);
	// Update/draw overriden from parent
	void update(float deltaTime) override;
	void draw(SDL_Renderer* renderer) override;
	// Set the textures used for the background
	void setScoreTextures(const std::vector<SDL_Texture*>& textures);
	// Get/set screen size and scroll speed
	void setScreenSize(const vector2& size) { mScreenSize = size; }
	void setScrollSpeed(float speed) { mScrollSpeed = speed; }
	float getScrollSpeed() const { return mScrollSpeed; }
private:
	// Struct to encapsulate each bg image and its offset
	struct ScoreTexture
	{
		SDL_Texture* mTexture;
		vector2 mOffset;
	};
	std::vector<ScoreTexture> mScoreTextures;
	vector2 mScreenSize;
	float mScrollSpeed;
};

#endif
