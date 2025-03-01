#ifndef SCORE_H
#define SCORE_H

#include <vector>

#include "font.h"

class scorePlayer1 : public actor
{
public:
	scorePlayer1(game* game);
	void updateActor(float deltaTime) override;
	void processKeyboard(const Uint8* state){};
private:
	float mAnimSpeed;
};

class scorePlayer2 : public actor
{
public:
	scorePlayer2(game* game);
	void updateActor(float deltaTime) override;
	void processKeyboard(const Uint8* state){};
private:
	float mAnimSpeed;
};

#endif
