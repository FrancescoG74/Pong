#ifndef SCORE_H
#define SCORE_H

#include <vector>

#include "font.h"

class score : public actor
{
public:
	score(game* game);
	void updateActor(float deltaTime) override;
	void processKeyboard(const Uint8* state){};
	float getVx() const { return mVx; }
	float getVy() const { return mVy; }
	void setPow(float pow);
private:
	const float g = 9.80665; // gravity acceleration in m/s^2
	float mVx,mVy;
	float mAnimSpeed;


};

#endif
