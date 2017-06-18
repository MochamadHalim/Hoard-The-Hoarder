#include "Player.h"
#include "Tile.h"
#include "LTexture.h"
//The dimensions of the level
const int LEVEL_WIDTH = 1280;
const int LEVEL_HEIGHT = 960;
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
int grav = 0;
const int IDLE_ANIMATION_FRAMES = 2;
const int WALKING_ANIMATION_FRAMES = 6;

class Player
{
public:
	//Animation
	SDL_Rect gSpriteIdleClips[IDLE_ANIMATION_FRAMES];
	SDL_Rect gSpriteWalkingClips[WALKING_ANIMATION_FRAMES];
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

private:
	//The X and Y offsets of the player
	//int mPosX, mPosY;

	//The velocity of the player
	int mVelX, mVelY;

	//player's collision box
	SDL_Rect mBox;
};

Player::Player()
{
	mBox.x = 0;
	mBox.y = 0;
	mBox.w = player_WIDTH;
	mBox.h = player_HEIGHT;

	//Initialize the velocity
	mVelX = 0;
	mVelY = 0;
}

void Player::handleEvent(SDL_Event& e)
{
	//If a key was pressed
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
	{
		//Adjust the velocity
		switch (e.key.keysym.sym)
		{
		case SDLK_DOWN: mVelY += player_VEL; walk = true; break;
		case SDLK_UP: mVelY -= player_VEL; walk = true; break;
		case SDLK_LEFT: mVelX -= player_VEL;
			flipType = SDL_FLIP_HORIZONTAL;
			walk = true;
			break;
		case SDLK_RIGHT: mVelX += player_VEL;
			flipType = SDL_FLIP_NONE;
			walk = true;
			break;
		}
	}
	//If a key was released
	else if (e.type == SDL_KEYUP && e.key.repeat == 0)
	{
		//Adjust the velocity
		switch (e.key.keysym.sym)
		{
		case SDLK_UP: mVelY += player_VEL; walk = false; break;
		case SDLK_DOWN: mVelY -= player_VEL; walk = false; break;
		case SDLK_LEFT: mVelX += player_VEL; walk = false; break;
		case SDLK_RIGHT: mVelX -= player_VEL; walk = false; break;
		}
	}
}

void Player::move(Tile *tiles[])
{

	//Move the player left or right
	mBox.x += mVelX;

	//If the player went too far to the left or right or touched a wall
	if ((mBox.x < 0) || (mBox.x + player_WIDTH > LEVEL_WIDTH) || touchesWall(mBox, tiles))
	{
		//move back
		mBox.x -= mVelX;
	}

	//Move the player up or down
	mBox.y += mVelY;
	//If the player went too far up or down or touched a wall
	if ((mBox.y < 0) || (mBox.y + player_HEIGHT > LEVEL_HEIGHT) || touchesWall(mBox, tiles))
	{
		//move back
		mBox.y -= mVelY;
	}
	else {
		mVelY += grav;
	}

}

void Player::setCamera(SDL_Rect& camera)
{
	//Center the camera over the player
	camera.x = (mBox.x + player_WIDTH / 2) - SCREEN_WIDTH / 2;
	camera.y = (mBox.y + player_HEIGHT / 2) - SCREEN_HEIGHT / 2;

	//Keep the camera in bounds
	if (camera.x < 0)
	{
		camera.x = 0;
	}
	if (camera.y < 0)
	{
		camera.y = 0;
	}
	if (camera.x > LEVEL_WIDTH - camera.w)
	{
		camera.x = LEVEL_WIDTH - camera.w;
	}
	if (camera.y > LEVEL_HEIGHT - camera.h)
	{
		camera.y = LEVEL_HEIGHT - camera.h;
	}
}

bool touchesWall(SDL_Rect box, Tile* tiles[])
{
	//Go through the tiles
	for (int i = 0; i < TOTAL_TILES; ++i)
	{
		//If the tile is a wall type tile
		if ((tiles[i]->getType() >= TILE_CENTER) && (tiles[i]->getType() <= TILE_TOPLEFT))
		{
			//If the collision box touches the wall tile
			if (checkCollision(box, tiles[i]->getBox()))
			{
				return true;
			}
		}
	}

	//If no wall tiles were touched
	return false;
}

bool checkCollision(SDL_Rect a, SDL_Rect b) {
	//The sides of the rectangles
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	//Calculate the sides of rect A
	leftA = a.x;
	rightA = a.x + a.w;
	topA = a.y;
	bottomA = a.y + a.h;

	//Calculate the sides of rect B
	leftB = b.x;
	rightB = b.x + b.w;
	topB = b.y;
	bottomB = b.y + b.h;

	//If any of the sides from A are outside of B
	if (bottomA <= topB)
	{
		return false;
	}

	if (topA >= bottomB)
	{
		return false;
	}

	if (rightA <= leftB)
	{
		return false;
	}

	if (leftA >= rightB)
	{
		return false;
	}

	//If none of the sides from A are outside B
	return true;
}

void Player::render(SDL_Rect& camera, int frame)
{
	LTexture gSpriteSheetTexture;
	setCamera(camera);
	SDL_Rect* currentClip;
	if (walk == false) {
		currentClip = &gSpriteIdleClips[frame / 2];
	}
	else {
		currentClip = &gSpriteWalkingClips[frame / 6];
	}
	gSpriteSheetTexture.render(mBox.x - camera.x, mBox.y - camera.y, currentClip, degrees, NULL, flipType);
}

bool Player::loadMedia() {
	if (!gSpriteSheetTexture.loadFromFile("14_animated_sprites_and_vsync/Sprite.png"))
	{
		printf("Failed to load walking animation texture!\n");
		success = false;
	}
	else
	{
		//Set sprite clips
		gSpriteIdleClips[0].x = 0;
		gSpriteIdleClips[0].y = 0;
		gSpriteIdleClips[0].w = 116;
		gSpriteIdleClips[0].h = 255;

		gSpriteIdleClips[1].x = 255;
		gSpriteIdleClips[1].y = 0;
		gSpriteIdleClips[1].w = 116;
		gSpriteIdleClips[1].h = 255;

		gSpriteWalkingClips[0].x = 497;
		gSpriteWalkingClips[0].y = 0;
		gSpriteWalkingClips[0].w = 140;
		gSpriteWalkingClips[0].h = 255;

		gSpriteWalkingClips[1].x = 754;
		gSpriteWalkingClips[1].y = 0;
		gSpriteWalkingClips[1].w = 140;
		gSpriteWalkingClips[1].h = 255;

		gSpriteWalkingClips[2].x = 1004;
		gSpriteWalkingClips[2].y = 0;
		gSpriteWalkingClips[2].w = 140;
		gSpriteWalkingClips[2].h = 255;

		gSpriteWalkingClips[3].x = 1257;
		gSpriteWalkingClips[3].y = 0;
		gSpriteWalkingClips[3].w = 140;
		gSpriteWalkingClips[3].h = 255;

		gSpriteWalkingClips[4].x = 1522;
		gSpriteWalkingClips[4].y = 0;
		gSpriteWalkingClips[4].w = 140;
		gSpriteWalkingClips[4].h = 255;

		gSpriteWalkingClips[5].x = 1767;
		gSpriteWalkingClips[5].y = 0;
		gSpriteWalkingClips[5].w = 140;
		gSpriteWalkingClips[5].h = 255;
	}


	return success;
}