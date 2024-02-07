//Nathan Walter
//CPSC 440
//Program 3: Bird Drop

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include "Cannonballs.h"

Cannonballs::Cannonballs()
{
	cannonball = al_load_bitmap("cannonball.png");
	speed = 10;
	live = false;
	angle = 0;
	boundx = al_get_bitmap_width(cannonball);
	boundy = al_get_bitmap_height(cannonball);
	x = 0;
	y = 0;
}
Cannonballs::~Cannonballs()
{
	al_destroy_bitmap(cannonball);
}
void Cannonballs::DrawCannonballs()
{
	if (live)
		al_draw_rotated_bitmap(cannonball, al_get_bitmap_width(cannonball) / 2, al_get_bitmap_height(cannonball) / 2, x, y, angle, 0);		//make the cannonball spin when fired
		angle += 0.1;
}
void Cannonballs::FireCannonball(Player& player)
{
	if (!live)
	{
		//fire cannonball from center of player's cannon and at the end of the cannon
		x = player.getX() - (player.getBoundX() / 2);
		y = player.getY();
		live = true;
	}
}
void Cannonballs::UpdateCannonball(Player& player)
{
	if (live)
	{
		x += player.getAngle() * speed;		//update x position of cannonball to account for angle of cannon
		y -= speed;
	}
}
void Cannonballs::CollideCannonball(Player& player, BirdDropping bD[], int cSize, const int WIDTH, const int HEIGHT)
{
	if (live)
	{
		for (int j = 0; j < cSize; j++)
		{
			if (bD[j].getLive())
			{
				//if cannonball hits a dropping penguin
				if (x > (bD[j].getX() - bD[j].getBoundX()) &&
					x < (bD[j].getX() + bD[j].getBoundX()) &&
					y > (bD[j].getY() - bD[j].getBoundY() + 25) &&		//+,- 25 pixels to tighten up the hit boxes when hitting penguins on far left or right,
					y < (bD[j].getY() + bD[j].getBoundY() - 25))		//because I was getting some false collisions
				{
					live = false;
					bD[j].setLive(false);
					player.addBirdsShot();
					
				}
				else if (x < -40 || x > WIDTH + 40 || y < -40)	//if cannonball goes goes out of bounds
				{
					live = false;
				}
			}
		}
	}
}
