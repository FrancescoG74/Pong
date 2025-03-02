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

scorePlayer::scorePlayer(game* game, playerType player)
:actor(game),maxPoint{5},mPoint{0},mPlayer{player}
{
//	setColor(0xff,0xff,0xff);

// Create an animated sprite component
	anim* asc = new anim(this);
	std::vector<SDL_Texture*> anims (5);
	for(int i=0;i<5;i++){
		anims[i] = game->getTextureFont("resources/scoreFonts.ttf",std::to_string(i));
	}
	asc->setAnimTextures(anims);

}

void scorePlayer::updateActor(float deltaTime)
{
	actor::updateActor(deltaTime);
	// Update score point based behaviour of players

	float load=getFrameNum();
	load += mPoint;
	if(load<maxPoint)
		setFrameNum(load);
	mPoint = 0;
}
