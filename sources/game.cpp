#include <algorithm>
#include <iostream>

#include "math.h"
#include "component.h"
#include "circle.h"
#include "sprite.h"
#include "actor.h"
#include "redpad.h"
#include "bluepad.h"
#include "ball.h"
#include "game.h"
#include "background.h"

game::game()
:mWindow{nullptr},mRenderer{nullptr},mIsRunning{true}
,mUpdatingActors{false},mNbullet{0},mToBeReleased{false}
{}

bool game::initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) != 0) {
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return false;
	}

	mWindow = SDL_CreateWindow("PONG", 100, 100, 862, 657, 0);
	if (!mWindow) {
		SDL_Log("Failed to create window: %s", SDL_GetError());
		return false;
	}

	mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!mRenderer) {
		SDL_Log("Failed to create renderer: %s", SDL_GetError());
		return false;
	}

	if (IMG_Init(IMG_INIT_PNG) == 0) {
		SDL_Log("Unable to initialize SDL_image: %s", SDL_GetError());
		return false;
	}

	loadData();

	mTicksCount = SDL_GetTicks();

	return true;
}

void game::runLoop()
{
	while (mIsRunning) {
		processInput();
		updateGame();
		generateOutput();
	}
}

void game::shutdown()
{
	unloadData();
	IMG_Quit();
	SDL_DestroyRenderer(mRenderer);
	SDL_DestroyWindow(mWindow);
	SDL_Quit();
}

void game::loadData()
{
	// **** BACKGROUNDS ****
	// Create actor for the background (this doesn't need a subclass)
	actor* temp = new actor(this);
	temp->setPosition(vector2(431.0f, 328.0f));

	// Create the "far back" background
	background* bg = new background(temp);
	bg->setScreenSize(vector2(862.0f, 657.0f));
	std::vector<SDL_Texture*> bgtexs = {
		getTexture("resources/background_star.png"),
		getTexture("resources/background_star.png")
	};
	bg->setBGTextures(bgtexs);
	bg->setScrollSpeed(-25.0f);

	// **** ACTORS ****
	// Create player's redpad
	actor* mRedpad = new redpad(this);
	mRedpad->setPosition(vector2(128.0f, 495.0f));
	mRedpad->setScale(1.0f);

	// Create player's bluepad
	actor* mBluepad = new bluepad(this);
	mBluepad->setPosition(vector2(760.0f, 495.0f));
	mBluepad->setScale(1.0f);

	// Create player's ball
	actor* mBall = new ball(this);
	mBall->setPosition(vector2(428.0f, 295.0f));
	mBall->setScale(1.0f);
	mBall->setState(actor::EActive);

	// Create Score
	this->loadScore();


}

bool game::loadScore()
{
	//Loading success flag
	bool success = true;

	//Open the font
	mFont = TTF_OpenFont( "TheConfessionFullRegular-8qGz.ttf",56 );
	if( mFont == NULL )
	{
		printf( "Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError() );
		success = false;
	}
	else
	{
		//Render text
		SDL_Color textColor = { 0, 0, 0 };
		if( !gTextTexture.loadFromRenderedText( "0 1 2 3 4 5 6 7 8 9", textColor ) )
		{
			printf( "Failed to render text texture!\n" );
			success = false;
		}
	}

	return success;
}

void game::unloadData()
{
	// Delete actors
	// Because ~Actor calls RemoveActor, have to use a different style loop
	std::cout << "actors: " << mActors.size() << std::endl;
	std::cout << "sprites: " << mSprites.size() << std::endl;

	while (!mActors.empty())
		delete mActors.back();

	// Destroy textures
	for (auto i : mTextures)
		SDL_DestroyTexture(i.second);

	mTextures.clear();
}

SDL_Texture* game::getTexture(const std::string& fileName)
{
	SDL_Texture* tex = nullptr;
	// Is the texture already in the map?
	auto iter = mTextures.find(fileName);
	if (iter != mTextures.end()) {
		tex = iter->second;
	} else {
		// Load from file
		SDL_Surface* surf = IMG_Load(fileName.c_str());
		if (!surf) {
			SDL_Log("Failed to load texture file %s", fileName.c_str());
			return nullptr;
		}

		// Create texture from surface
		tex = SDL_CreateTextureFromSurface(mRenderer, surf);
		SDL_FreeSurface(surf);
		if (!tex) {
			SDL_Log("Failed to convert surface to texture for %s", fileName.c_str());
			return nullptr;
		}
		mTextures.emplace(fileName.c_str(), tex);
	}
	return tex;
}

void game::processInput()
{
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type)
		{
			case SDL_QUIT:
				mIsRunning = false;
				break;
		}
	}

	const Uint8* state = SDL_GetKeyboardState(NULL);
	if (state[SDL_SCANCODE_ESCAPE])
		mIsRunning = false;

	if (state[SDL_SCANCODE_SPACE])
		mToBeReleased = true;

	if (mToBeReleased && !state[SDL_SCANCODE_SPACE]){
		mToBeReleased = false;
	}

	// Process catapult input
	for (auto actor : mActors)
		actor->processKeyboard(state);

}

void game::updateGame()
{
	// Compute delta time
	// Wait until 16ms has elapsed since last frame
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16))
		;

	float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;
	if (deltaTime > 0.05f)
		deltaTime = 0.05f;

	mTicksCount = SDL_GetTicks();

	// Update all actors
	mUpdatingActors = true;
	for (auto actor : mActors)
		actor->update(deltaTime);

	mUpdatingActors = false;

	// Move any pending actors to mActors
	for (auto pending : mPendingActors)
		mActors.emplace_back(pending);

	mPendingActors.clear();

	// Add any dead actors to a temp vector
	std::vector<actor*> deadActors;
	for (auto actor : mActors) {
		if (actor->getState() == actor::EDead) {
			deadActors.emplace_back(actor);
		}
	}

	// Delete dead actors (which removes them from mActors)
	for (auto actor : deadActors)
		delete actor;
}

void game::generateOutput()
{
	SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 255);
	SDL_RenderClear(mRenderer);

	// Draw all sprite components
	for (auto sprite : mSprites)
		sprite->draw(mRenderer);

	SDL_RenderPresent(mRenderer);
}

void game::addActor(actor* actor)
{
	// If we're updating actors, need to add to pending
	if (mUpdatingActors) {
		mPendingActors.emplace_back(actor);
	} else {
		mActors.emplace_back(actor);
	}
}

void game::removeActor(actor* actor)
{
	// Is it in pending actors?
	auto iter = std::find(mPendingActors.begin(), mPendingActors.end(), actor);
	if ( iter != mPendingActors.end() ) {
		// Swap to end of vector and pop off (avoid erase copies)
		std::iter_swap(iter, mPendingActors.end() - 1);
		mPendingActors.pop_back();
	}

	// Is it in actors?
	iter = std::find(mActors.begin(), mActors.end(), actor);
	if ( iter != mActors.end() ) {
		// Swap to end of vector and pop off (avoid erase copies)
		std::iter_swap(iter, mActors.end() - 1);
		mActors.pop_back();
	}
}

void game::addSprite(sprite* sprite)
{
	// Find the insertion point in the sorted vector
	// (The first element with a higher draw order than me)
	int myDrawOrder = sprite->getDrawOrder();
	auto iter = mSprites.begin();
	for ( ;
		iter != mSprites.end();
		++iter)
	{
		if (myDrawOrder < (*iter)->getDrawOrder())
		{
			break;
		}
	}

	// Inserts element before position of iterator
	mSprites.insert(iter, sprite);
}

void game::removeSprite(sprite* sprite)
{
	// (We can't swap because it ruins ordering)
	auto iter = std::find(mSprites.begin(), mSprites.end(), sprite);
	mSprites.erase(iter);
}

bluepad* game::getBluepad()
{
	bluepad* bluepadItem;
	
	for (auto actor : mActors){
		bluepadItem = dynamic_cast<bluepad*>(actor);
		if (bluepadItem != nullptr){
			return bluepadItem;
		}
	}
	return nullptr;
}

redpad* game::getRedpad()
{
	redpad* redpadItem;
	
	for (auto actor : mActors){
		redpadItem = dynamic_cast<redpad*>(actor);
		if (redpadItem != nullptr){
			return redpadItem;
		}
	}
	return nullptr;
}

bool collision(circle& objA, circle& objB)
{
	bool res = false;
	float distMinCollision = objA.getRadius() + objB.getRadius();
	distMinCollision *= distMinCollision;

	vector2 distCentre = objA.getCenter()-objB.getCenter();
	float distCentreLenght = distCentre.LengthSq();

	if ( distCentreLenght < distMinCollision )
		res = true;

	return res;
}

bool collisionPad(vector2 pad, circle& ball)
{
	bool res = false;

	vector2 ballCentre = ball.getCenter();
	float	radius = ball.getRadius();

	if(std::abs(pad.y - ballCentre.y) < 64 && std::abs(ballCentre.x - pad.x) < radius/2 ) {
		res = true;
	} 

	return res;
}