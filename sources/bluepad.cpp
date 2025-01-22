#include <iostream>

#include "math.h"
#include "component.h"
#include "sprite.h"
#include "anim.h"
#include "circle.h"
#include "actor.h"
#include "bluepad.h"
#include "redpad.h"
#include "ball.h"
#include "game.h"

bluepad::bluepad(game* game)
:actor(game),mRightSpeed(0.0f),mDownSpeed(0.0f),
 mLoadSpeed{0.0f}
{
	// Create an animated sprite component
	anim* asc = new anim(this);
	std::vector<SDL_Texture*> anims = {
		game->getTexture("resources/pad_blue.png"),
	};
	asc->setAnimTextures(anims);

	// Create a collision detect
	mCircleColl = new circle(this);
	mCircleColl->setRadius(36.0f);

}

void bluepad::updateActor(float deltaTime)
{
	actor::updateActor(deltaTime);
	// Update position based on speeds and delta time
	vector2 pos = getPosition();
	pos.y += mDownSpeed * deltaTime;
	if (pos.y < 25.0f)
	{
		pos.y = 25.0f;
	}
	else if (pos.y > 650.0f)
	{
		pos.y = 650.0f;
	}
	setPosition(pos);
}

void bluepad::processKeyboard(const uint8_t* state)
{
	mDownSpeed = 0.0f;
	// load up/load down
	if (state[SDL_SCANCODE_O])
	{
		mDownSpeed -= 300.0f;
	}
	if (state[SDL_SCANCODE_L])
	{
		mDownSpeed += 300.0f;
	}

}

