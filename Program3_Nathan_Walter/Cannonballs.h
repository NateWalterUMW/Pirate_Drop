//Nathan Walter
//CPSC 440
//Program 3: Penguin Drop

#include "Player.h"
#include "BirdDropping.h"

class Cannonballs
{
public:
	Cannonballs();	//constructor
	~Cannonballs();	//deconstructor
	/*Draws a cannonball on the screen.
	@param none
	@return void*/
	void DrawCannonballs();
	/*Spawns a new cannonball out of the player's canon.
	@param Player&, player
	@return void*/
	void FireCannonball(Player& player);
	/*Updates the cannonball's x,y location with each new frame.
	@param Player&, player
	@return void*/
	void UpdateCannonball(Player& player);
	/*Collision detection between cannonball and dropping birds.
	@param Player&, player
	@param bD[], array of dropping birds
	@param int, number of dropping birds
	@param const int, WIDTH
	@param const int, HEIGHT
	@return void*/
	void CollideCannonball(Player& player, BirdDropping bD[], int cSize, const int WIDTH, const int HEIGHT);
	/*Gets boundx of cannonball.
	@param none
	@return int, boundx*/
	int getBoundX() { return boundx; }
	/*Gets boundy of cannonball.
	@param none
	@return int, boundy*/
	int getBoundY() { return boundy; }
	/*Gets x position of cannonball.
	@param none
	@return int, x position*/
	int getX() { return x; }
	/*Gets y position of cannonball.
	@param none
	@return int, y position*/
	int getY() { return y; }
private:
	int x;
	int y;
	int boundx;
	int boundy;
	bool live;
	int speed;
	float angle;
	ALLEGRO_BITMAP* cannonball;
};
