#include "Tile.h"
#include "LTexture.h"
//Tile constants
const int TILE_WIDTH = 80;
const int TILE_HEIGHT = 80;
const int TOTAL_TILES = 248 + 28;
const int TOTAL_TILE_SPRITES = 12;

//The different tile sprites
const int TILE_RED = 0;
const int TILE_GREEN = 1;
const int TILE_BLUE = 2;
const int TILE_CENTER = 3;
const int TILE_TOP = 4;
const int TILE_TOPRIGHT = 5;
const int TILE_RIGHT = 6;
const int TILE_BOTTOMRIGHT = 7;
const int TILE_BOTTOM = 8;
const int TILE_BOTTOMLEFT = 9;
const int TILE_LEFT = 10;
const int TILE_TOPLEFT = 11;

//Scene textures
LTexture gTileTexture;
SDL_Rect gTileClips[TOTAL_TILE_SPRITES];
//The tile
class Tile
{
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

private:
	//The attributes of the tile
	SDL_Rect mBox;
	//The tile type
	int mType;
};


Tile::Tile(int x, int y, int tileType)
{
	//Get the offsets
	mBox.x = x;
	mBox.y = y;

	//Set the collision box
	mBox.w = TILE_WIDTH;
	mBox.h = TILE_HEIGHT;

	//Get the tile type
	mType = tileType;
}

void Tile::render(SDL_Rect& camera)
{
	//If the tile is on screen
	if (checkCollision(camera, mBox))
	{
		//Show the tile
		gTileTexture.render(mBox.x - camera.x, mBox.y - camera.y, &gTileClips[mType]);
	}
}

int Tile::getType()
{
	return mType;
}

SDL_Rect Tile::getBox()
{
	return mBox;
}

bool Tile::setTiles(Tile* tiles[])
{
	//Success flag
	bool tilesLoaded = true;

	//The tile offsets
	int x = 0, y = 0;

	//Open the map
	std::ifstream map("39_tiling/lazy.map");
	//Initialize the tiles
	for (int i = 0; i < TOTAL_TILES; ++i)
	{
		//Determines what kind of tile will be made
		int tileType = -1;

		//Read tile from map file
		map >> tileType;

		//If the was a problem in reading the map
		if (map.fail())
		{
			//Stop loading map
			printf("Error loading map: Unexpected end of file!\n");
			tilesLoaded = false;
			break;
		}

		//If the number is a valid tile number
		if ((tileType >= 0) && (tileType < TOTAL_TILE_SPRITES))
		{
			tiles[i] = new Tile(x, y, tileType);
		}
		//If we don't recognize the tile type
		else
		{
			//Stop loading map
			printf("Error loading map: Invalid tile type at %d!\n", i);
			tilesLoaded = false;
			break;
		}
		//Move to next tile spot
		x += TILE_WIDTH;

		//If we've gone too far
		if (x >= LEVEL_WIDTH)
		{
			//Move back
			x = 0;

			//Move to the next row
			y += TILE_HEIGHT;
		}
	}
	//Move to next tile spot
	x += TILE_WIDTH;

	//If we've gone too far
	if (x >= LEVEL_WIDTH)
	{
		//Move back
		x = 0;

		//Move to the next row
		y += TILE_HEIGHT;
	}
	//Clip the sprite sheet
	if (tilesLoaded)
	{
		gTileClips[TILE_RED].x = 0;
		gTileClips[TILE_RED].y = 0;
		gTileClips[TILE_RED].w = TILE_WIDTH;
		gTileClips[TILE_RED].h = TILE_HEIGHT;

		gTileClips[TILE_GREEN].x = 0;
		gTileClips[TILE_GREEN].y = 80;
		gTileClips[TILE_GREEN].w = TILE_WIDTH;
		gTileClips[TILE_GREEN].h = TILE_HEIGHT;

		gTileClips[TILE_BLUE].x = 0;
		gTileClips[TILE_BLUE].y = 160;
		gTileClips[TILE_BLUE].w = TILE_WIDTH;
		gTileClips[TILE_BLUE].h = TILE_HEIGHT;

		gTileClips[TILE_TOPLEFT].x = 80;
		gTileClips[TILE_TOPLEFT].y = 0;
		gTileClips[TILE_TOPLEFT].w = TILE_WIDTH;
		gTileClips[TILE_TOPLEFT].h = TILE_HEIGHT;

		gTileClips[TILE_LEFT].x = 80;
		gTileClips[TILE_LEFT].y = 80;
		gTileClips[TILE_LEFT].w = TILE_WIDTH;
		gTileClips[TILE_LEFT].h = TILE_HEIGHT;

		gTileClips[TILE_BOTTOMLEFT].x = 80;
		gTileClips[TILE_BOTTOMLEFT].y = 160;
		gTileClips[TILE_BOTTOMLEFT].w = TILE_WIDTH;
		gTileClips[TILE_BOTTOMLEFT].h = TILE_HEIGHT;

		gTileClips[TILE_TOP].x = 160;
		gTileClips[TILE_TOP].y = 0;
		gTileClips[TILE_TOP].w = TILE_WIDTH;
		gTileClips[TILE_TOP].h = TILE_HEIGHT;

		gTileClips[TILE_CENTER].x = 160;
		gTileClips[TILE_CENTER].y = 80;
		gTileClips[TILE_CENTER].w = TILE_WIDTH;
		gTileClips[TILE_CENTER].h = TILE_HEIGHT;

		gTileClips[TILE_BOTTOM].x = 160;
		gTileClips[TILE_BOTTOM].y = 160;
		gTileClips[TILE_BOTTOM].w = TILE_WIDTH;
		gTileClips[TILE_BOTTOM].h = TILE_HEIGHT;

		gTileClips[TILE_TOPRIGHT].x = 240;
		gTileClips[TILE_TOPRIGHT].y = 0;
		gTileClips[TILE_TOPRIGHT].w = TILE_WIDTH;
		gTileClips[TILE_TOPRIGHT].h = TILE_HEIGHT;

		gTileClips[TILE_RIGHT].x = 240;
		gTileClips[TILE_RIGHT].y = 80;
		gTileClips[TILE_RIGHT].w = TILE_WIDTH;
		gTileClips[TILE_RIGHT].h = TILE_HEIGHT;

		gTileClips[TILE_BOTTOMRIGHT].x = 240;
		gTileClips[TILE_BOTTOMRIGHT].y = 160;
		gTileClips[TILE_BOTTOMRIGHT].w = TILE_WIDTH;
		gTileClips[TILE_BOTTOMRIGHT].h = TILE_HEIGHT;
	}
	//Close the file
	map.close();

	//If the map was loaded fine
	return tilesLoaded;
}

