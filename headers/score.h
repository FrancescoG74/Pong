#ifndef SCORE_H
#define SCORE_H

#include <vector>

#include "font.h"

class scorePlayer : public actor
{
public:
	enum playerType {PLAYER1, PLAYER2};

	scorePlayer(game* game,playerType player);
	void updateActor(float deltaTime) override;
	void processKeyboard(const Uint8* state){};
	void setPoint(){mPoint=1;};
	playerType getPlayer(){return mPlayer;};
private:
	const int maxPoint;
	int mPoint;
	playerType mPlayer;
};

#endif
