#ifndef BALL_H
#define BALL_H

class circle;

class ball : public actor
{
public:
	ball(game* game);
	void updateActor(float deltaTime) override;
	void processKeyboard(const Uint8* state);
	float getVx() const { return mVx; }
	float getVy() const { return mVy; }
	void setPow(float pow);
private:
	const float g = 9.80665; // gravity acceleration in m/s^2
	float mVx,mVy;
	float mAnimSpeed;
	circle* mCircleColl;

};

#endif // BALL_H
