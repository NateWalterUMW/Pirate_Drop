//Nathan Walter
//CPSC 440
//Program 3: Bird Drop

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include "BirdDropping.h"

BirdDropping::BirdDropping()
{
	birdDropping = al_load_bitmap("parrot.png");

	live = false;
	speed = 1;
	boundx = al_get_bitmap_width(birdDropping);
	boundy = al_get_bitmap_height(birdDropping);
	angle = 0;
}
BirdDropping::~BirdDropping()
{
	al_destroy_bitmap(birdDropping);
}
void BirdDropping::DrawBird()
{
	if (live)
	{
		al_draw_bitmap(birdDropping, x, y, 0);		//draw a new alive bird
	}
	else if (!live)
	{
		al_draw_rotated_bitmap(birdDropping, boundx / 2, boundy / 2, x, y, angle, 0);	//if a bird is hit, they spin on the way down
		angle += 0.05;
	}
}
void BirdDropping::StartBird(int WIDTH, int HEIGHT)
{
	int prevX = x;
	if (!live)
	{
		if (rand() % 500 == 0 && rand() % 500 != prevX)
		{
			live = true;
			x = rand() % (WIDTH - boundx);
			y = 0 - boundy;		//spawn above the screen, then float down
		}
	}
}
void BirdDropping::UpdateBird(int ms, const int FPS)
{
	int secElapsed = ms / FPS;
	if (live)
	{
		//increase the speed of dropping birds every 45 seconds
		if (secElapsed >= 0 && secElapsed < 45)
		{
			speed = 1;
		}
		else if (secElapsed >= 45 && secElapsed < 90)
		{
			speed = 2;
		}
		else if (secElapsed >= 90)
		{
			speed = 3;
		}
		y += speed;
	}
	else if (!live)
	{
		y += (speed + 5);
	}
}
void BirdDropping::CollideBird(Player& player, const int WIDTH, const int HEIGHT)
{
	if (live)
	{
		if (x >= 50 && x <= WIDTH - 50 && y >= HEIGHT - 150)	//if bird lands on the island
		{
			x = 0 - boundx;
			player.removeLives();
			live = false;
		}
		else if (x < 0)
		{
			live = false;
		}
	}
}
