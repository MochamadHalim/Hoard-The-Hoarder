#ifndef LTEXTURE_H
#define LTEXTURE_H
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <fstream>
using namespace std;

class Player
{
private:
	//The velocity of the player
	int mVelX, mVelY;

	//player's collision box
	SDL_Rect mBox;
public:
	bool walk = true;
	//Flip type
	SDL_RendererFlip flipType = SDL_FLIP_NONE;
	double degrees = 0;

	//The dimensions of the player
	static const int player_WIDTH = 116;
	static const int player_HEIGHT = 255;

	//Maximum axis velocity of the player
	static const int player_VEL = 5;

	//Initializes the variables
	Player();

	//Takes key presses and adjusts the player's velocity
	void handleEvent(SDL_Event& e);

	//Moves the player
	void move(Tile *tiles[]);

	//Centers the camera over the player
	void setCamera(SDL_Rect& camera);

	//Shows the player on the screen
	void render(SDL_Rect& camera, int frame);

	bool loadMedia();

};

#endif
