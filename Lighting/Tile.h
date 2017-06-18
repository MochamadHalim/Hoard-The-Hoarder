#ifndef TILE_H
#define TILE_H
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <fstream>
using namespace std;

class Tile
{
private:
	//The attributes of the tile
	SDL_Rect mBox;
	//The tile type
	int mType;
public:
	//Initializes position and type
	Tile(int x, int y, int tileType);

	//Shows the tile
	void render(SDL_Rect& camera);

	//Get the tile type
	int getType();

	//Get the collision box
	SDL_Rect getBox();

	bool setTiles(Tile * tiles[]);

	bool touchesWall(SDL_Rect box, Tile * tiles[]);

	bool checkCollision(SDL_Rect a, SDL_Rect b);
};

#endif
