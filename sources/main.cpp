#include "math.h"
#include "component.h"
#include "sprite.h"
#include "circle.h"
#include "actor.h"
#include "redpad.h"
#include "bluepad.h"
#include "ball.h"
#include "game.h"

int main(int argc, char** argv)
{
	game pong;
	bool success = pong.initialize();
	if (success)
	{
		pong.runLoop();
	}
	pong.shutdown();
	return 0;
}
