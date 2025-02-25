#include "math.h"
#include "sprite.h"
#include "font.h"
#include "anim.h"
#include "circle.h"
#include "actor.h"
#include "redpad.h"
#include "bluepad.h"
#include "ball.h"
#include "game.h"
#include "score.h"

score::score(game* game)
:actor(game),mVx{0.0f},mVy{0.0f},
mAnimSpeed{0.01f}
{
//	setColor(0xff,0xff,0xff);


	// Create an animated sprite component
	anim* asc = new anim(this);
	std::vector<SDL_Texture*> anims = {
		game->getTextureFont("resources/scoreFonts.ttf","00"),
		game->getTextureFont("resources/scoreFonts.ttf","01"),
		game->getTextureFont("resources/scoreFonts.ttf","02"),
		game->getTextureFont("resources/scoreFonts.ttf","03"),
		game->getTextureFont("resources/scoreFonts.ttf","04"),
	};
	asc->setAnimTextures(anims);

}

void score::updateActor(float deltaTime)
{
	actor::updateActor(deltaTime);
	// Update score point based behaviour of players

	float load=getFrameNum();
	load += mAnimSpeed;
	if (load < 0.0f)
	{
		load = 4.0f;
	}
	if (load >= 5.0f)
	{
		load = 0.0f;
	}
	setFrameNum(load);
}

void score::setPow(float pow)
{
	mVx = std::sqrt(pow) * 10;
	mVy = std::sqrt(pow) * -10;
}

