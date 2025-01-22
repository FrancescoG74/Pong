#include <algorithm>

#include "math.h"
#include "component.h"
#include "sprite.h"
#include "circle.h"
#include "actor.h"
#include "redpad.h"
#include "bluepad.h"
#include "ball.h"
#include "game.h"

actor::actor(game* game)
:mState(EActive), mPosition(vector2::Zero), mScale(1.0f), mRotation(0.0f), mFrameNum(0.0f), mGame(game)
{
	mGame->addActor(this);
}

actor::~actor()
{
	mGame->removeActor(this);
	// Need to delete components
	// Because ~Component calls RemoveComponent, need a different style loop
	while (!mComponents.empty())
	{
		delete mComponents.back();
	}
}

void actor::update(float deltaTime)
{
	if (mState == EActive)
	{
		updateComponents(deltaTime);
		updateActor(deltaTime);
	}
}

void actor::updateComponents(float deltaTime)
{
	for (auto comp : mComponents)
	{
		comp->update(deltaTime);
	}
}

void actor::updateActor(float deltaTime)
{
}

void actor::addComponent(component* component)
{
	// Find the insertion point in the sorted vector
	// (The first element with a order higher than me)
	int myOrder = component->getUpdateOrder();
	auto iter = mComponents.begin();
	for (;iter != mComponents.end();++iter)
	{
		if (myOrder < (*iter)->getUpdateOrder())
		{
			break;
		}
	}

	// Inserts element before position of iterator
	mComponents.insert(iter, component);
}

void actor::removeComponent(component* component)
{
	auto iter = std::find(mComponents.begin(), mComponents.end(), component);
	if (iter != mComponents.end())
	{
		mComponents.erase(iter);
	}
}
