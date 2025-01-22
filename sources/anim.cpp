#include "math.h"
#include "anim.h"
#include "actor.h"


anim::anim(actor* owner, int drawOrder)
:sprite(owner, drawOrder), mCurrFrame(0.0f), mAnimFPS(24.0f)
{
}

void anim::update(float deltaTime)
{
	sprite::update(deltaTime);

	if (mAnimTextures.size() > 0)
	{
		// Update the current frame based on frame rate
		// and delta time
		mCurrFrame += mAnimFPS * deltaTime;

		// Wrap current frame if needed
		while (mCurrFrame >= mAnimTextures.size())
		{
			mCurrFrame -= mAnimTextures.size();
		}

		// Set the current texture
		setTexture(mAnimTextures[mOwner->getFrameNum()]);
	}
}

void anim::setAnimTextures(const std::vector<SDL_Texture*>& textures)
{
	mAnimTextures = textures;
	if (mAnimTextures.size() > 0)
	{
		// Set the active texture to first frame
		mCurrFrame = 0.0f;
		setTexture(mAnimTextures[0]);
	}
}
