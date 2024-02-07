//Nathan Walter
//CPSC 440
//Program 3: Pirate Drop

#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_image.h>
#include "Player.h"
#include "BirdDropping.h"
#include "Cannonballs.h"

using namespace std;

void getGameInfo(Player& player, int lives, int birdsShot, int sec, const int FPS, const int WIDTH, const int HEIGHT, ALLEGRO_BITMAP* gameover, ALLEGRO_BITMAP* gameoverBoard);

/*This is main. This is where instances of Player, BirdDropping and Cannonballs are created.
* This is where the timer is created and where the keybindings are set. This is where the game loop exists
* and where everything gets drawn on the screen.
* @param none
* @return void
*/
int main()
{
    //display game instructions and keybindings
    cout << "\n   Welcome to Pirate Drop!\n\n";
    cout << "   Shoot down the pirate parrots before they raid your island. If 5 parrots land on your shores, they take the island \n";
    cout << "   for themselves. Every 45 seconds the pirates will speed up their rate of descent.\n\n";
    cout << "   Good luck!\n\n";
    cout << "   Left Arrow:     swivel left\n";
    cout << "   Right Arrow:    swivel right\n";
    cout << "   Spacebar:       fire cannonball\n";
    cout << "   Escape:         exit\n\n";

    //primitive variables
    const int WIDTH = 1280;  //was 960
    const int HEIGHT = 720; //was 540
    const int NUM_CANNONBALLS = 10;
    const int NUM_BIRDS_DROPPING = 10;
    int ms = 0;     //time in milliseconds
    enum KEYS {LEFT, RIGHT, SPACE };
    bool keys[3] = { false, false, false };
    bool done = false;
    bool redraw = true;
    const int FPS = 60;

    //allegro variables
    ALLEGRO_DISPLAY* display = NULL;
    ALLEGRO_EVENT_QUEUE* event_queue = NULL;
    ALLEGRO_TIMER* timer = NULL;

    //initialization Functions
    if (!al_init())										//initialize Allegro
        return -1;

    display = al_create_display(WIDTH, HEIGHT);			//create our display object

    if (!display)										//test display object
        return -1;

    //initialize allegro addons
    al_init_primitives_addon();
    al_install_keyboard();
    al_init_image_addon();
    al_init_font_addon();
    al_init_ttf_addon();

    //load backgound bitmaps
    ALLEGRO_BITMAP* sky = NULL;
    sky = al_load_bitmap("sky.png");
    ALLEGRO_BITMAP* ocean = NULL;
    ocean = al_load_bitmap("ocean.png");
    ALLEGRO_BITMAP* island = NULL;
    island = al_load_bitmap("island.png");
    ALLEGRO_BITMAP* gameover = NULL;
    gameover = al_load_bitmap("gameover.png");
    ALLEGRO_BITMAP* gameoverBoard = NULL;
    gameoverBoard = al_load_bitmap("gameover_board.png");

    //create object variables
    Player myPlayer(WIDTH, HEIGHT);
    Cannonballs Cannonballs[NUM_CANNONBALLS];
    BirdDropping BirdsDropping[NUM_BIRDS_DROPPING];

    event_queue = al_create_event_queue();  //create event queue
    timer = al_create_timer(1.0 / FPS);     //create timer

    srand(time(NULL));  //set the rand() seed

    //add events to the event queue
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_display_event_source(display));

    al_start_timer(timer);
    while (!done)
        {
            ALLEGRO_EVENT ev;
            al_wait_for_event(event_queue, &ev);
            if (ev.type == ALLEGRO_EVENT_TIMER)
            {
                redraw = true;
                if (keys[LEFT])
                    myPlayer.SwivelLeft();
                if (keys[RIGHT])
                    myPlayer.SwivelRight();
                if (keys[SPACE])
                    Cannonballs->FireCannonball(myPlayer);

                for (int i = 0; i < NUM_CANNONBALLS; i++)
                    Cannonballs[i].UpdateCannonball(myPlayer);
                for (int i = 0; i < NUM_BIRDS_DROPPING; i++)
                    BirdsDropping[i].StartBird(WIDTH, HEIGHT);
                for (int i = 0; i < NUM_BIRDS_DROPPING; i++)
                    BirdsDropping[i].UpdateBird(ms, FPS);
                for (int i = 0; i < NUM_CANNONBALLS; i++)
                    Cannonballs[i].CollideCannonball(myPlayer, BirdsDropping, NUM_BIRDS_DROPPING, WIDTH, HEIGHT);
                for (int i = 0; i < NUM_BIRDS_DROPPING; i++)
                    BirdsDropping[i].CollideBird(myPlayer, WIDTH, HEIGHT);
            }
            else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            {
                done = true;
            }
            else if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
            {
                switch (ev.keyboard.keycode)
                {
                case ALLEGRO_KEY_ESCAPE:
                    done = true;
                    break;
                case ALLEGRO_KEY_LEFT:
                    keys[LEFT] = true;
                    break;
                case ALLEGRO_KEY_RIGHT:
                    keys[RIGHT] = true;
                    break;
                case ALLEGRO_KEY_SPACE:
                    keys[SPACE] = true;
                    for (int i = 0; i < NUM_CANNONBALLS; i++)
                        Cannonballs[i].FireCannonball(myPlayer);
                    break;
                }
            }
            else if (ev.type == ALLEGRO_EVENT_KEY_UP)
            {
                switch (ev.keyboard.keycode)
                {
                case ALLEGRO_KEY_ESCAPE:
                    done = true;
                    break;
                case ALLEGRO_KEY_LEFT:
                    keys[LEFT] = false;
                    break;
                case ALLEGRO_KEY_RIGHT:
                    keys[RIGHT] = false;
                    break;
                case ALLEGRO_KEY_SPACE:
                    keys[SPACE] = false;
                    break;
                }
            }
            if (redraw && al_is_event_queue_empty(event_queue))
            {
                redraw = false;

                //draw all the game elements
                al_draw_bitmap(sky, 0, 0, 0);
                al_draw_bitmap(ocean, 0, -300, 0);
                al_draw_bitmap(island, 0, 150, 0);
                myPlayer.DrawPlayer();
                for (int i = 0; i < NUM_CANNONBALLS; i++)
                    Cannonballs[i].DrawCannonballs();
                for (int i = 0; i < NUM_BIRDS_DROPPING; i++)
                    BirdsDropping[i].DrawBird();
                
                getGameInfo(myPlayer, myPlayer.getLives(), myPlayer.getBirdsShot(), ms, FPS, WIDTH, HEIGHT, gameover, gameoverBoard);   //display game stats

                al_flip_display();
                al_clear_to_color(al_map_rgb(0, 0, 0));
            }
            if (myPlayer.getLives() == 0)	//if player is out of lives, then gameover
            {
                al_set_target_bitmap(al_get_backbuffer(display));
                al_clear_to_color(al_map_rgb(0, 0, 0));
                al_rest(10.0);	//pause the screen for 10 seconds upon gameover
                done = true;
            }
            ms++;
        }
    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_destroy_event_queue(event_queue);
    al_destroy_timer(timer);
    al_destroy_display(display);						//destroy our display object
    system("Pause");
    return 0;
}
/*This function is resposible for printing the stats game information to the screen. These include the player's health bar, 
* the number of birds shot down and the seconds elapsed.
@param Player&, player
@param int, player lives remaining
@param int, number of dropping birds shot down
@param int, seconds elapsed
@param const int, FPS
@param int, width
@param int, height
@return void*/
void getGameInfo(Player& player, int lives, int birdsShot, int sec, const int FPS, const int WIDTH, const int HEIGHT, ALLEGRO_BITMAP* gameover, ALLEGRO_BITMAP* gameoverBoard)
{
    ALLEGRO_FONT* font36 = al_load_ttf_font("Pirate Jack.ttf", 36, 0);

    ALLEGRO_BITMAP* birdLanded = NULL;      //add a landed bird each time a bird reaches the island
    birdLanded = al_load_bitmap("parrot_landed.png");

    //switch statement to determine what game stats to display based on player's health level
    switch (player.getLives())
    {
    case 5:
        al_draw_filled_rectangle(20, 20, 270, 50, al_map_rgb(50, 255, 50));     //full health bar
        al_draw_textf(font36, al_map_rgb(0, 0, 0), 20, 70, ALLEGRO_ALIGN_LEFT, "Pirates shot: %d", player.getBirdsShot());
        break;
    case 4:
        al_draw_bitmap(birdLanded, 250, HEIGHT - 175, 0);

        al_draw_filled_rectangle(20, 20, 220, 50, al_map_rgb(50, 255, 50));     //health bar - 1
        al_draw_filled_rectangle(20, 45, 270, 50, al_map_rgb(50, 255, 50));
        al_draw_textf(font36, al_map_rgb(0, 0, 0), 20, 70, ALLEGRO_ALIGN_LEFT, "Pirates shot: %d", player.getBirdsShot());
        break;
    case 3:
        al_draw_bitmap(birdLanded, 250, HEIGHT - 175, 0);
        al_draw_bitmap(birdLanded, 350, HEIGHT - 225, 0);

        al_draw_filled_rectangle(20, 20, 170, 50, al_map_rgb(255, 255, 50));    //health bar - 2
        al_draw_filled_rectangle(20, 45, 270, 50, al_map_rgb(255, 255, 50));
        al_draw_textf(font36, al_map_rgb(0, 0, 0), 20, 70, ALLEGRO_ALIGN_LEFT, "Pirates shot: %d", player.getBirdsShot());
        break;
    case 2:
        al_draw_bitmap(birdLanded, 250, HEIGHT - 175, 0);
        al_draw_bitmap(birdLanded, 350, HEIGHT - 225, 0);
        al_draw_bitmap(birdLanded, 425, HEIGHT - 150, 0);

        al_draw_filled_rectangle(20, 20, 120, 50, al_map_rgb(255, 255, 50));    //health bar - 3
        al_draw_filled_rectangle(20, 45, 270, 50, al_map_rgb(255, 255, 50));
        al_draw_textf(font36, al_map_rgb(0, 0, 0), 20, 70, ALLEGRO_ALIGN_LEFT, "Pirates shot: %d", player.getBirdsShot());
        break;
    case 1:
        al_draw_bitmap(birdLanded, 250, HEIGHT - 175, 0);
        al_draw_bitmap(birdLanded, 350, HEIGHT - 225, 0);
        al_draw_bitmap(birdLanded, 425, HEIGHT - 150, 0);
        al_draw_bitmap(birdLanded, 600, HEIGHT - 225, 0);

        al_draw_filled_rectangle(20, 20, 70, 50, al_map_rgb(255, 50, 50));      //health bar - 4
        al_draw_filled_rectangle(20, 45, 270, 50, al_map_rgb(255, 50, 50));
        al_draw_textf(font36, al_map_rgb(0, 0, 0), 20, 70, ALLEGRO_ALIGN_LEFT, "Pirates shot: %d", player.getBirdsShot());
        break;
    case 0:
        al_draw_bitmap(birdLanded, 250, HEIGHT - 175, 0);
        al_draw_bitmap(birdLanded, 350, HEIGHT - 225, 0);
        al_draw_bitmap(birdLanded, 425, HEIGHT - 150, 0);
        al_draw_bitmap(birdLanded, 600, HEIGHT - 225, 0);
        al_draw_bitmap(birdLanded, 675, HEIGHT - 150, 0);

        //display the gameover board
        al_draw_bitmap(gameover, WIDTH / 4, 25, 0);
        al_draw_bitmap(gameoverBoard, WIDTH / 2 - (al_get_bitmap_width(gameoverBoard) / 2), HEIGHT / 2, 0);
        al_draw_textf(font36, al_map_rgb(255, 255, 255), WIDTH / 2, HEIGHT / 2 + 30, ALLEGRO_ALIGN_CENTER, "Pirates Shot: %d", player.getBirdsShot());     //print number of birds shot down
        al_draw_textf(font36, al_map_rgb(255, 255, 255), WIDTH / 2, HEIGHT / 2 + 85, ALLEGRO_ALIGN_CENTER, "Survived: %d sec", sec / FPS);	//print seconds elapsed
        break;
    }
    al_destroy_font(font36);
}
