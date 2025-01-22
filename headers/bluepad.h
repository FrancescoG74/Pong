#ifndef BLUEPAD_H
#define BLUEPAD_H

class game;

class bluepad : public actor
{
public:
	bluepad(game* game);
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
