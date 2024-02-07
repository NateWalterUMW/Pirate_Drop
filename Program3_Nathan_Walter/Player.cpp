//Nathan Walter
//CPSC 440
//Program 3: Penguin Drop

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include "Player.h"

Player::Player(int WIDTH, int HEIGHT)
{
	playerCannon = al_load_bitmap("cannon.png");	//load player bitmap (the cannon that the player swivels left and right)
	playerOctopus = al_load_bitmap("octopus.png");

	x = (WIDTH / 2);
	y = HEIGHT - 90;
	lives = 5;
	birdsShot = 0;
	boundx = al_get_bitmap_width(playerCannon);
	boundy = al_get_bitmap_height(playerCannon);
	angle = 0;
}
Player::~Player()
{
	al_destroy_bitmap(playerCannon);
	al_destroy_bitmap(playerOctopus);
}
void Player::DrawPlayer()
{
	al_draw_rotated_bitmap(playerCannon, boundx / 2, boundy / 2, x - (boundx / 2), y, angle, 0);
	al_draw_rotated_bitmap(playerOctopus, boundx / 2, boundy / 2, x - (boundx / 2) + 25, y + 25, angle, 0);
}
void Player::SwivelLeft()
{
	angle -= 0.025;

	if (angle <= -1.0472)	//set the left swivel bounds to -60 degrees (-1.0472 radians)
		angle = -1.0472;
}
void Player::SwivelRight()
{
	angle += 0.025;

	if (angle >= 1.0472)	//set the right swivel bounds to 60 degrees (1.0472 radians)
		angle = 1.0472;
}
