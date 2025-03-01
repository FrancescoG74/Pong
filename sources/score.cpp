#include "math.h"
#include "sprite.h"
#include "font.h"
#include "anim.h"
#include "circle.h"
#include "actor.h"
#include "redpad.h"
#include "bluepad.h"
#include "ball.h"
#include "score.h"
#include "game.h"
#include "score.h"

scorePlayer1::scorePlayer1(game* game)
:actor(game),mAnimSpeed{0.01f}
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

void scorePlayer1::updateActor(float deltaTime)
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

scorePlayer2::scorePlayer2(game* game)
:actor(game),mAnimSpeed{0.01f}
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

void scorePlayer2::updateActor(float deltaTime)
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
