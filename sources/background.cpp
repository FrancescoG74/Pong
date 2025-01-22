#include "math.h"
#include "sprite.h"
#include "circle.h"
#include "actor.h"
#include "redpad.h"
#include "bluepad.h"
#include "ball.h"
#include "game.h"
#include "background.h"

background::background(actor* owner, int drawOrder)
:sprite(owner, drawOrder),mScrollSpeed(0.0f)
{}

void background::update(float deltaTime)
{
	sprite::update(deltaTime);
	for (auto& bg : mBGTextures) {
		// Update the x offset
		bg.mOffset.x += mScrollSpeed * deltaTime;
		// If this is completely off the screen, reset offset to
		// the right of the last bg texture
		if (bg.mOffset.x < -mScreenSize.x) {
			bg.mOffset.x = (mBGTextures.size() - 1) * mScreenSize.x - 1;
		}
	}
}

void background::draw(SDL_Renderer* renderer)
{
	// Draw each background texture
	for (auto& bg : mBGTextures) {
		SDL_Rect r;
		// Assume screen size dimensions
		r.w = static_cast<int>(mScreenSize.x);
		r.h = static_cast<int>(mScreenSize.y);
		// Center the rectangle around the position of the owner
		r.x = static_cast<int>(bg.mOffset.x);
		r.y = static_cast<int>(bg.mOffset.y);

		// Draw this background
		SDL_RenderCopy(renderer, bg.mTexture, nullptr, &r);
	}
}

void background::setBGTextures(const std::vector<SDL_Texture*>& textures)
{
	int count = 0;
	for (auto tex : textures) {
		BGTexture temp;
		temp.mTexture = tex;
		// Each texture is screen width in offset
		temp.mOffset.x = count * mScreenSize.x;
		temp.mOffset.y = 0;
		mBGTextures.emplace_back(temp);
		count++;
	}
}
