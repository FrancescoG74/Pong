#include "math.h"
#include "component.h"
#include "sprite.h"
#include "circle.h"
#include "actor.h"
#include "redpad.h"
#include "bluepad.h"
#include "ball.h"
#include "game.h"

component::component(actor* owner, int updateOrder)
:mOwner(owner),mUpdateOrder(updateOrder)
{
	// Add to actor's vector of components
	mOwner->addComponent(this);
}

component::~component()
{
	if(mOwner != nullptr)
		mOwner->removeComponent(this);
}

void component::update(float deltaTime)
{
}
