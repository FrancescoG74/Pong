#ifndef ACTOR_H
#define ACTOR_H

#include <vector>

class game;

class actor
{
public:
	enum state
	{
		EActive,
		EPaused,
		EDead
	};

	actor(game* game);
	virtual ~actor();

	// Update function called from game (not overridable)
	void update(float deltaTime);
	// Updates all the components attached to the actor (not overridable)
	void updateComponents(float deltaTime);
	// Any actor-specific update code (overridable)
	virtual void updateActor(float deltaTime);
	virtual void processKeyboard(const Uint8* state){};
	// Getters/setters
	const vector2& getPosition() const { return mPosition; }
	void setPosition(const vector2& pos) { mPosition = pos; }
	float getScale() const { return mScale; }
	void setScale(float scale) { mScale = scale; }
	float getRotation() const { return mRotation; }
	void setRotation(float rotation) { mRotation = rotation; }
	float getFrameNum() const { return mFrameNum; }
	void setFrameNum(float frameNum) { mFrameNum = frameNum; }

	state getState() const { return mState; }
	void setState(state state) { mState = state; }

	game* getGame() { return mGame; }


	// Add/remove components
	void addComponent(component* component);
	void removeComponent(component* component);
protected:
	std::vector<component*> mComponents;
private:
	// Actor's state
	state mState;

	// Transform
	vector2 mPosition;
	float mScale;
	float mRotation;
	float mFrameNum;

	game* mGame;
};

#endif
