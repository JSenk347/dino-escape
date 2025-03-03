/*******************************************************************************
 AUTHORS:      Anna Running Rabbit, Jordan Senko, Joseph Mills
 COURSE:       COMP2659-001
 INSTRUCTOR:   Tim Reimer
 DATE:         Feb.10, 2025

 FILE:          events.c
 PURPOSE:
*******************************************************************************/
#include <stdio.h>
#include <osbind.h>
#include <time.h>
#include "events.h"
#include "model.h"

/* SYNCHRONUS EVENTS */
/*******************************************************************************
    PURPOSE: Updates the x position of each of the game's walls, moving them 
             the left each time.
    INPUT:  - gameModel: pointer to the Model object, aka the current game
                instance
    OUTPUT: N/A
*******************************************************************************/
void move_walls(Model *game){
	int i;
	unsigned int h_vel;

	Obs_wall *walls = game->walls;
	for (i = 0; i < NUM_WALLS; i++){
		Obs_wall *wall = &walls[i];

		if (i + 1 < NUM_WALLS){
			Obs_wall *next_wall = &walls[i + 1];
			if (next_wall -> is_moving != TRUE && 
				wall -> bottom.bot_left.x <= WIN_WIDTH - (WIN_WIDTH/NUM_WALLS))
			{
				next_wall -> is_moving = TRUE;
				init_wall(next_wall, gap_y());
			}
		}
	
		if (wall -> is_moving == TRUE){
			Obs *top = &(wall->top);
			Obs *bottom = &(wall->bottom);
			h_vel = wall -> hor_velocity;
		
			bottom->bot_left.x -= h_vel;
			bottom->bot_right.x -= h_vel;
			bottom->top_left.x -= h_vel;
			bottom->top_right.x -= h_vel;
		
			top->bot_left.x -= h_vel;
			top->bot_right.x -= h_vel;
			top->top_left.x -= h_vel;
			top->top_right.x -= h_vel;
		
			/* Checks if reset is needed */

			if (bottom->bot_right.x < L_BORDER_X && top->top_right.x < L_BORDER_X)
			{
				reset_wall(game, wall);
				return;
			}
		}
	}
}

/*******************************************************************************
    PURPOSE: Checks to see if the dino has collided with any of the barriers.
             If so, reflect_dino_death(Model *game) will be called to show the
             dino falling to the ground, and the game will then end.
    INPUT:  - gameModel: pointer to the Model object, aka the current game
    OUTPUT: N/A
*******************************************************************************/
void check_collisions(Model *game)
{
    int i;
    Dino *dino = &game -> dino;
    Obs_wall *walls = game->walls;

    for (i = 0; i < NUM_WALLS; i++)
    {
        Obs_wall *wall = &walls[i];
        Obs *top = &wall->top;
        Obs *bottom = &wall->bottom;

        /*Collision with TOP obstacle*/
        if (dino->top_left.x < top->top_right.x &&
            dino -> top_right.x > top->top_left.x &&
            dino -> top_left.y < top->bot_left.y &&
            dino -> bot_left.y > top->top_left.y)
        {
            printf("Collision with top obstacle!, WALL %u\n",
            i + 1);
            reflect_dino_death(game);
            game->game_state.dead_flag = TRUE;
            game->game_state.start_flag = FALSE;
            return;
        }

        /*Collision with BOTTOM obstacle*/
        if (dino -> top_left.x < bottom->top_right.x &&
            dino -> top_right.x > bottom->top_left.x &&
            dino -> top_left.y < bottom->bot_left.y &&
            dino -> bot_left.y > bottom->top_left.y)
        {
            printf("Collision with bottom obstacle!, WALL %u\n",
            i + 1);
            reflect_dino_death(game);
            game->game_state.dead_flag = TRUE;
            game->game_state.start_flag = FALSE;
            return;
        }
    }
}

/* ASYNCHRONUS EVENTS */
/*******************************************************************************
    PURPOSE: Waits for the user to enter "enter" on the keyboard and then updates
             the start_flag to trigger the start of the game.
    INPUT:  - gameModel: pointer to the Model object, aka the current game
                instance
    OUTPUT: N/A
*******************************************************************************/
void wait_for_game_start(Model *gameModel)
{
    printf("Press ENTER to start the game...\n");

    while (!gameModel->game_state.start_flag)
    {
        if (Cconis())
        {
            char key = Cnecin();

            if (key == '\r')
            {
              gameModel->game_state.start_flag = TRUE;
              printf("Game started by user!\n");
            }
        }
    }
}

/*******************************************************************************
    PURPOSE: To read the user's keyboard input and call the appropriate functions
             such as read_dino_input(Model *gameModel, char key) and 
             read_quit_req(Model *gameModel, char key)
    INPUT:  - gameModel: pointer to the Model object, aka the current game
                instance
    OUTPUT: N/A
*******************************************************************************/
void read_input(Model *gameModel)
{
    if (Cconis())
    {
        char key = Cnecin();
        while (Cconis())
        {
            Cnecin();
        }

        if (key == 'w' || key == 's')
        {
            read_dino_input(gameModel, key);
        }

        if (key == 'q')
        {
            read_quit_req(gameModel, key);
        }
    }
}

/*******************************************************************************
    PURPOSE: To update the direction and velocity of the dino according to the
             user's input. Pressing 'w' will result in the dino going up, and
             pressing 's' will result in the dino going down.
    INPUT:  - gameModel: pointer to the Model object, aka the current game
                instance
            - key: the character the user has entered.
    OUTPUT: N/A
*******************************************************************************/
void read_dino_input(Model *gameModel, char key)
{
    /* Moves dino up */
    if (key == 'w')
    {
        gameModel->dino.vert_velocity = 5;
        gameModel->dino.vert_direction = UP; /* Changes dino direction to up */
        move_dino(&gameModel->dino);
    }
    /* Moves dino down */
    else if (key == 's')
    {
        gameModel->dino.vert_velocity = 5;
        gameModel->dino.vert_direction = DOWN;
        move_dino(&gameModel->dino);
      }
}

/*******************************************************************************
    PURPOSE: Updates the game's dead_flag, triggereing a sequence of loop ending
             to ensure the game stops.
    INPUT:  - gameModel: pointer to the Model object, aka the current game
                instance
            - key: the key the user has pressed.
    OUTPUT: N/A
*******************************************************************************/
void read_quit_req(Model *gameModel, char key)
{
    if (key == 'q')
    {
        gameModel -> game_state.dead_flag = TRUE;
        printf("Game ended by user.\n");

    }
}

/******************************** CONDITION BASED EVENTS *********************************/

/******************************************************************************************
    PURPOSE: To check whether the dino has passed a barrier or not, and then update the
             score with update_score(Model *model)
    INPUT:  - game The model of the game
    OUTPUT: N/A
******************************************************************************************/
  void check_score(Model *game) {
    int i;
    Dino *dino = &(game->dino);
    Obs_wall *walls = game -> walls;
    for (i = 0; i < NUM_WALLS; i++) {
        Obs_wall *wall = &walls[i];

        if ((wall->bottom.bot_right.x < dino->bot_left.x) && !wall->been_passed)
        {
            update_score(game);
            wall->been_passed = TRUE;
        }
      }
}

/******************************************************************************************
    PURPOSE: To update both the value of the Score object as well as the value of the 
             Digit objects in the Digit array of the Score object.
    INPUT:  - game: The model of the game
    OUTPUT: N/A
******************************************************************************************/
void update_score(Model *game){	
	int value;

    Score *score = &(game -> score);
	score -> prev_value = score -> value;

    if (score -> value < score -> max_value){
        (score -> value)++;
        value = score -> value;
        (score -> digits)[3].value = (value / 1000) % 10; 	/* thousands digit */
        (score -> digits)[2].value = (value / 100) % 10;  	/* hundreds digit */
        (score -> digits)[1].value = (value / 10) % 10;   	/* tens digit */
        (score -> digits)[0].value = value % 10;			      /* ones digit */
    }
}

/* play_point_sound() */

/*******************************************************************************
    PURPOSE: Reflects the death of the given Model's dino by moving the dino
                down, stopping at the lower border, at double the dino's initial
                velocity.
    INPUT:  - gameModel: pointer to the Model object, aka the current game
                instance
    OUTPUT: N/A
*******************************************************************************/
void reflect_dino_death(Model *gameModel)
  {
    /* Will need to add dino bitmap update to dino_dead_bitmap() */

    /* gameModel -> dino.vert_direction = 1; /* Changes dino direction to down
    gameModel -> dino.vert_velocity = gameModel -> dino.vert_velocity*2; */

    printf("Dino has died.\n");

    while (gameModel->dino.bot_left.y < B_BORDER_Y - 1)
    {
        gameModel->dino.vert_direction = DOWN;
        gameModel->dino.vert_velocity = DEAD_VELOCITY;
        move_dino(&gameModel->dino);
        printf("Top Lt Y: %u | ", gameModel->dino.top_left.y);
        printf("Top Rt Y: %u | ", gameModel->dino.top_right.y);
        printf("Bot Lt Y: %u | ", gameModel->dino.bot_left.y);
        printf("Bot Rt Y: %u\n", gameModel->dino.bot_right.y);
        /* printf("Dino direction: %u | ", gameModel -> dino.vert_direction);
        printf("Dino velocity: %u\n", gameModel -> dino.vert_velocity); */
    }

    gameModel->game_state.lost_flag = TRUE;
}