#include <iostream>

#include "math.h"
#include "sprite.h"
#include "anim.h"
#include "circle.h"
#include "actor.h"
#include "ball.h"
#include "redpad.h"
#include "bluepad.h"
#include "game.h"

ball::ball(game* game)
:actor(game),mVx{100.0f},mVy{-20.0f},
mAnimSpeed{0.1f}//,mOnceExplosion{false}
{
	// Create an animated sprite component
	anim* asc = new anim(this);
	std::vector<SDL_Texture*> anims = {
		game->getTexture("resources/bullet1.png"),
		game->getTexture("resources/bullet2.png"),
		game->getTexture("resources/bullet3.png"),
	};
	asc->setAnimTextures(anims);

	// Create a collision detect
	mCircleColl = new circle(this);
	mCircleColl->setRadius(36.0f);

}

void ball::updateActor(float deltaTime)
{
	actor::updateActor(deltaTime);
	// Update position based on speeds and delta time
	vector2 pos = getPosition();
	pos.x += 3 * mVx * deltaTime;
	mVy += 3 * ( 0.5 * g ) * deltaTime ;
	pos.y += 3 * mVy * deltaTime ;
	// Restrict position on the screen
	if (pos.y < 0.0f || pos.y > 657.0f)
	{
		mVy = -mVy;
	}
	else if (pos.x < 0.0f || pos.x > 864.0f)
	{
		this->setState(EDead);
	}
	setPosition(pos);

	float load=getFrameNum();
	load += mAnimSpeed;
	if (load < 0.0f)
	{
		load = 2.0f;
	}
	if (load > 2.0f)
	{
		load = 0.0f;
	}
	setFrameNum(load);


	bluepad* bluepadItem = getGame()->getBluepad();
	if(collisionPad(bluepadItem->getPosition(),*mCircleColl)){
		mVx = -mVx;
	}
	redpad* redpadItem = getGame()->getRedpad();
	if(collisionPad(redpadItem->getPosition(),*mCircleColl)){
		mVx = -mVx;
	}

}

void ball::setPow(float pow)
{
	mVx = std::sqrt(pow) * 10;
	mVy = std::sqrt(pow) * -10;
}

void ball::processKeyboard(const uint8_t* state)
{
}
