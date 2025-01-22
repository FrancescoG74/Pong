#include <iostream>

#include "math.h"
#include "circle.h"
#include "sprite.h"
#include "actor.h"
#include "redpad.h"
#include "bluepad.h"
#include "ball.h"
#include "game.h"

circle::circle(actor* owner)
:component(owner)
{
//	mOwner->getGame()->addSprite(this);
}

const vector2 circle::getCenter() const
{
    vector2 pos = mOwner->getPosition();

    return pos;
}
