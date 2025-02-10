#include "math.h"
#include "sprite.h"
#include "font.h"
#include "circle.h"
#include "actor.h"
#include "redpad.h"
#include "bluepad.h"
#include "ball.h"
#include "game.h"
#include "score.h"

score::score(actor* owner, int drawOrder)
:font(owner, drawOrder),mScrollSpeed(0.0f)
{
	setColor(0xff,0xff,0xff);
}

void score::update(float deltaTime)
{
/*	font::update(deltaTime);
	for (auto& bg : mBGTextures) {
		// Update the x offset
		bg.mOffset.x += mScrollSpeed * deltaTime;
		// If this is completely off the screen, reset offset to
		// the right of the last bg texture
		if (bg.mOffset.x < -mScreenSize.x) {
			bg.mOffset.x = (mBGTextures.size() - 1) * mScreenSize.x - 1;
		}
	}
*/
}

void score::draw(SDL_Renderer* renderer)
{
	// Draw each background texture
	for (auto& sctex : mScoreTextures) {
		SDL_Rect r;
		// Assume screen size dimensions
		r.w = static_cast<int>(100);
		r.h = static_cast<int>(100);
		// Center the rectangle around the position of the owner
		r.x = static_cast<int>(20);
		r.y = static_cast<int>(20);

		// Draw this background
		SDL_RenderCopy(renderer, sctex.mTexture, nullptr, &r);

//		SDL_Log("dest rect w=%u h=%u x=%u y=%u",mScreenSize.x, mScreenSize.y, sctex.mOffset.x, sctex.mOffset.y);
	}
}

void score::setScoreTextures(const std::vector<SDL_Texture*>& textures)
{
	int count = 0;
	for (auto tex : textures) {
		ScoreTexture temp;
		temp.mTexture = tex;
		// Each texture is screen width in offset
		temp.mOffset.x = count * mScreenSize.x;
		temp.mOffset.y = 0;
		mScoreTextures.emplace_back(temp);
		count++;
	}
}
