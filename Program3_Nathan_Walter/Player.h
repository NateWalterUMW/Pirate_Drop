//Nathan Walter
//CPSC 440
//Program 3: Penguin Drop

#ifndef PLAYERH
#define PLAYERH

class Player
{
public:
	Player(int WIDTH, int HEIGHT);	//constructor
	~Player();	//deconstructor
	/*Draws the player on the screen.
	@param none
	@return void*/
	void DrawPlayer();
	/*Swivels the player's canon to the left.
	@param none
	@return void*/
	void SwivelLeft();
	/*Swivels the player's canon to the right.
	@param none
	@return void*/
	void SwivelRight();
	/*Gets boundx of player.
	@param none
	@return int, boundx*/
	int getBoundX() { return boundx; }
	/*Gets boundy of player.
	@param none
	@return int, boundy*/
	int getBoundY() { return boundy; }
	/*Gets x postion of player.
	@param none
	@return int, x postition*/
	int getX() { return x; }
	/*Gets y position of player.
	@param none
	@return int, y position*/
	int getY() { return y; }
	/*Gets the angle that the player's cannon is currently aiming at.
	@param none
	@return float, angle*/
	float getAngle() { return angle; }
	/*Removes 1 life from the player.
	@param none
	@return void*/
	void removeLives() { lives--; }
	/*Gets the number of player lives remaining.
	@param none
	@return int, player lives remaining*/
	int getLives() { return lives; }
	/*Gets the number of birds the player has shot down.
	@param none
	@return int, number of birds shot down*/
	int getBirdsShot() { return birdsShot; }
	/*Increments by 1 the number of birds shot down.
	@param none
	@return void*/
	void addBirdsShot() { birdsShot++; }
private:
	float angle;
	int x;
	int y;
	int lives;
	int birdsShot;
	int boundx;
	int boundy;
	ALLEGRO_BITMAP* playerCannon;
	ALLEGRO_BITMAP* playerOctopus;
};
#endif

