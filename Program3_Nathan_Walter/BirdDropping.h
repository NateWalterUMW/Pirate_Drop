//Nathan Walter
//CPSC 440
//Program 3: Bird Drop

#ifndef	BIRDDROPPINGH
#define BIRDDROPPINGH
#include "Player.h"

class BirdDropping
{
public:
	BirdDropping();		//constructor
	~BirdDropping();		//deconstructor
	/*Draws a dropping bird on the screen.
	@param none
	@return void*/
	void DrawBird();
	/*Spawns a new bird.
	@param int, width
	@param int, height
	@return void*/
	void StartBird(int WIDTH, int HEIGHT);
	/*Updates bird's x,y location with each new frame based on the seconds elapsed.
	@param int, ms
	@param const int, FPS
	@return void*/
	void UpdateBird(int ms, const int FPS);
	/*Collision detection between dropping bird and iceberg.
	@param Player&, player
	@param const int, WIDTH
	@param const int, HEIGHT
	@return void*/
	void CollideBird(Player& player, const int WIDTH, const int HEIGHT);
	/*Gets boundx of dropping bird.
	@param none
	@return int, boundx*/
	int getBoundX() { return boundx; }
	/*Gets boundy of dropping bird.
	@param none
	@return int, boundy*/
	int getBoundY() { return boundy; }
	/*Gets x position of dropping bird.
	@param none
	@return int, x position*/
	int getX() { return x; }
	/*Gets y position of dropping bird.
	@param none
	@return int, y position*/
	int getY() { return y; }
	/*Checks if a dropping bird is alive.
	@param none
	@return bool, true if dropping bird is alive, else false*/
	bool getLive() { return live; }
	/*Sets the live status of a dropping bird to true.
	@param bool, l
	@return void*/
	void setLive(bool l) { live = l; }
private:
	int x;
	int y;
	bool live;
	float speed;
	int boundx;
	int boundy;
	float angle;
	ALLEGRO_BITMAP* birdDropping;
};
#endif

