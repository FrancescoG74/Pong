#ifndef GAME_H
#define GAME_H

#include "SDL2/SDL.h"
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <unordered_map>
#include <string>
#include <vector>

class game
{
public:
	game();
	bool initialize();
	void runLoop();
	void shutdown();

	void addActor(actor* actor);
	void removeActor(actor* actor);

	void addSprite(sprite* sprite);
	void removeSprite(sprite* sprite);

	SDL_Texture* getTexture(const std::string& fileName);

	void setUpdatingActors(bool setUA){ mUpdatingActors = setUA; }

	bluepad* getBluepad();
	redpad* getRedpad();

private:
	void processInput();
	void updateGame();
	void generateOutput();
	void loadData();
	void unloadData();
	bool loadScore();
	// Map of textures loaded
	std::unordered_map<std::string, SDL_Texture*> mTextures;

	// All the actors in the game
	std::vector<actor*> mActors;
	// Any pending actors
	std::vector<actor*> mPendingActors;
	// All the sprite components drawn
	std::vector<sprite*> mSprites;

	SDL_Window* mWindow;
	SDL_Renderer* mRenderer;
	Uint32 mTicksCount;
	bool mIsRunning;
	// Track if we're updating actors right now
	bool mUpdatingActors;
	int	 mNbullet;
	bool mToBeReleased;

	//Globally used font
	TTF_Font* mFont = NULL;


};

bool collision(circle& objA, circle& objB);
bool collisionPad(vector2 pad, circle& ball);

#endif
