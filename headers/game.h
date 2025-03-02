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

	void addFont(font* font);
	void removeFont(font* font);

	SDL_Texture* getTexture(const std::string& fileName);
	SDL_Texture* getTextureFont(const std::string& fileNameTTF, std::string textureText);

	void setUpdatingActors(bool setUA){ mUpdatingActors = setUA; }

	bluepad* getBluepad();
	redpad* getRedpad();

	scorePlayer* getScorePlayer(scorePlayer::playerType player);

private:
	void processInput();
	void updateGame();
	void generateOutput();
	void loadData();
	void unloadData();
	TTF_Font* getTrueTypeFont(const std::string& fontFileName, int ptsize);
	// Map of textures loaded
	std::unordered_map<std::string, SDL_Texture*> mTextures;
	// Map of fonts true type loaded
	std::unordered_map<std::string, TTF_Font*> mTrueTypeFonts;

	// All the actors in the game
	std::vector<actor*> mActors;
	// Any pending actors
	std::vector<actor*> mPendingActors;
	// All the sprite components drawn
	std::vector<sprite*> mSprites;
	// All the font components drawn
	std::vector<font*> mFonts;

	SDL_Window* mWindow;
	SDL_Renderer* mRenderer;
	Uint32 mTicksCount;
	bool mIsRunning;
	// Track if we're updating actors right now
	bool mUpdatingActors;
	int	 mNbullet;
	bool mToBeReleased;

	//Globally used font
//	TTF_Font* mFont = NULL;


};

bool collision(circle& objA, circle& objB);
bool collisionPad(vector2 pad, circle& ball);

#endif
