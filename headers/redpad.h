#ifndef REDPAD_H
#define REDPAD_H

class game;

class redpad : public actor
{
public:
	redpad(game* game);
	void updateActor(float deltaTime) override;
	void processKeyboard(const Uint8* state);
	float getRightSpeed() const { return mRightSpeed; }
	float getDownSpeed() const { return mDownSpeed; }
	circle* getCircle() const { return mCircleColl;}

private:
	float mRightSpeed;
	float mDownSpeed;
	float mLoadSpeed;
	circle* mCircleColl;
};

#endif
