#include <iostream>

#include "math.h"
#include "component.h"
#include "sprite.h"
#include "anim.h"
#include "circle.h"
#include "actor.h"
#include "redpad.h"
#include "bluepad.h"
#include "ball.h"
#include "game.h"

redpad::redpad(game* game)
:actor(game),mRightSpeed(0.0f),mDownSpeed(0.0f),
 mLoadSpeed{0.0f}
{
	// Create an animated sprite component
	anim* asc = new anim(this);
	std::vector<SDL_Texture*> anims = {
		game->getTexture("resources/pad_red.png"),
	};
	asc->setAnimTextures(anims);

	// Create a collision detect
	mCircleColl = new circle(this);
	mCircleColl->setRadius(36.0f);

}

void redpad::updateActor(float deltaTime)
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

void redpad::processKeyboard(const uint8_t* state)
{
	mDownSpeed = 0.0f;
	// up/down
	if (state[SDL_SCANCODE_W])
	{
		mDownSpeed -= 300.0f;
	}
	if (state[SDL_SCANCODE_S])
	{
		mDownSpeed += 300.0f;
	}
}

