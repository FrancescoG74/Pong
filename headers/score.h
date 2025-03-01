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
//	float getVx() const { return mVx; }
//	float getVy() const { return mVy; }
//	void setPow(float pow);

private:
//	const float g = 9.80665; // gravity acceleration in m/s^2
//	float mVx,mVy;
	float mAnimSpeed;

};

class scorePlayer2 : public actor
{
public:
	scorePlayer2(game* game);
	void updateActor(float deltaTime) override;
	void processKeyboard(const Uint8* state){};
//	float getVx() const { return mVx; }
//	float getVy() const { return mVy; }
//	void setPow(float pow);

private:
//	const float g = 9.80665; // gravity acceleration in m/s^2
//	float mVx,mVy;
	float mAnimSpeed;

};

#endif
