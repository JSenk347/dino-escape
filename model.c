/*******************************************************************************
 AUTHORS:      Anna Running Rabbit, Jordan Senko, Joseph Mills
 COURSE:       COMP2659-001
 INSTRUCTOR:   Tim Reimer
 DATE:         Feb.10, 2025

 FILE: model.c
 PURPOSE: Contains the data structures and related functions for the game model.
*******************************************************************************/
#include "model.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

/*******************************************************************************
	PURPOSE: Moves the dino vertically up or down the screen, while staying
			 within the gameplay borders.
	INPUT:	- dino: pointer to the Dino object to be moved
			- direction: integer set as either -1 to represent moving up or +1
				to represent moving down
	OUTPUT: N/A
*******************************************************************************/
void move_dino(Dino *dino)
{
	dino->top_left.y += (dino->vert_velocity * dino->vert_direction);
	dino->top_right.y += (dino->vert_velocity * dino->vert_direction);
	dino->bot_left.y += (dino->vert_velocity * dino->vert_direction);
	dino->bot_right.y += (dino->vert_velocity * dino->vert_direction);

	/* Limits dino movement to top border of gamescreen */
	if (dino->top_left.y <= T_BORDER_Y && dino->vert_direction == UP)
	{
		dino->vert_velocity = 0;
		dino->top_left.y = T_BORDER_Y + 1;
		dino->top_right.y = T_BORDER_Y + 1;
		dino->bot_left.y = T_BORDER_Y + DINO_HEIGHT;
		dino->bot_right.y = T_BORDER_Y + DINO_HEIGHT;
	}
	/* Limits dino movement to bottom border of gamescreen */
	if (dino->bot_left.y >= B_BORDER_Y && dino->vert_direction == DOWN)
	{
		dino->vert_velocity = 0;
		dino->top_left.y = B_BORDER_Y - DINO_HEIGHT;
		dino->top_right.y = B_BORDER_Y - DINO_HEIGHT;
		dino->bot_left.y = B_BORDER_Y - 1;
		dino->bot_right.y = B_BORDER_Y - 1;
	}
}

/*******************************************************************************
	PURPOSE:
	INPUT:
	OUTPUT: N/A
*******************************************************************************/
void init_wall(Obs_wall *wall, unsigned int gap_y)
{
	Obs *bottom = &(wall->bottom);
	Obs *top = &(wall->top);

	/* Bottom Obstacle */
	bottom->top_left.x = R_BORDER_X;
	bottom->top_left.y = gap_y + HALF_GAP;
	bottom->top_right.x = R_BORDER_X + 31;
	bottom->top_right.y = gap_y + HALF_GAP;

	bottom->bot_left.x = R_BORDER_X;
	bottom->bot_left.y = B_BORDER_Y - 1;
	bottom->bot_right.x = R_BORDER_X + 31;
	bottom->bot_right.y = B_BORDER_Y - 1;

	/* Top Obstacle */
	top->top_left.x = R_BORDER_X;
	top->top_left.y = T_BORDER_Y + 1;
	top->top_right.x = R_BORDER_X + 31;
	top->top_right.y = T_BORDER_Y + 1;

	top->bot_left.x = R_BORDER_X;
	top->bot_left.y = gap_y - HALF_GAP;
	top->bot_right.x = R_BORDER_X + 31;
	top->bot_right.y = gap_y - HALF_GAP;
}

void init_walls(Model *game)
{
	int i;
	unsigned int gap;
	unsigned int num_walls;

	Obs_wall (*walls)[4] = &(game->walls);
	num_walls = sizeof(game->walls) / sizeof(game->walls[0]);

	/* Initialize first wall at far right border and store its x */
	init_wall(walls[0], gap_y());
	
	/* */
	for (i = 1; i < num_walls; i++)
	{
		gap = gap_y();

		Obs_wall *wall = &walls[i - 1];
		Obs *bottom = &(wall->bottom);
		Obs *top = &(wall->top);

		Obs_wall *prev_wall = &(walls[i - 1]);
		Obs *prev_bottom = &(prev_wall->bottom);
		Obs *prev_top = &(prev_wall->top);

		/* Bottom Obstacle */
		bottom->top_left.x = (prev_bottom -> top_left.x) + (WIN_WIDTH/num_walls);
		bottom->top_left.y = gap + HALF_GAP;
		bottom->top_right.x = (prev_bottom -> top_right.x) + (WIN_WIDTH/num_walls);
		bottom->top_right.y = gap + HALF_GAP;

		bottom->bot_left.x = (prev_bottom -> bot_left.x) + (WIN_WIDTH/num_walls);
		bottom->bot_left.y = B_BORDER_Y - 1;
		bottom->bot_right.x = (prev_bottom -> bot_right.x) + (WIN_WIDTH/num_walls);
		bottom->bot_right.y = B_BORDER_Y - 1;

		
		/* Top Obstacle */
		top->top_left.x = (prev_top -> top_left.x) + (WIN_WIDTH/num_walls);
		top->top_left.y = T_BORDER_Y + 1;
		top->top_right.x = (prev_top -> top_right.x) + (WIN_WIDTH/num_walls);
		top->top_right.y = T_BORDER_Y + 1;

		top->bot_left.x = (prev_top -> bot_left.x) + (WIN_WIDTH/num_walls);
		top->bot_left.y = gap - HALF_GAP;
		top->bot_right.x = (prev_top -> bot_right.x) + (WIN_WIDTH/num_walls);
		top->bot_right.y = gap - HALF_GAP;
	}
}

/*******************************************************************************
	PURPOSE:
	INPUT:
	OUTPUT: N/A
*******************************************************************************/
unsigned int gap_y()
{
	srand(time(0));
	/* returning a random int from 74 - 326 (inclusive). 75 - HALF_GAP = 50 = T_BORDER + 1; 326 + HALF_GAP = 351 = B_BORDER - 1*/
	return rand() % 253 + 74;
}

/*******************************************************************************
	PURPOSE:
	INPUT:
	OUTPUT: N/A
*******************************************************************************/
void move_wall(Model *game)
{
	Obs_wall *wall = &(game->wall);
	Obs *top = &(wall->top);
	Obs *bottom = &(wall->bottom);

	/* Checks if first initialization needed 
	if (bottom->top_left.y >= B_BORDER_Y | top->bot_left.y <= T_BORDER_Y)
	{
		init_obs_wall(&game->wall, gap_y());
	}
	*/

	bottom->bot_left.x -= wall->hor_velocity;
	bottom->bot_right.x -= wall->hor_velocity;
	bottom->top_left.x -= wall->hor_velocity;
	bottom->top_right.x -= wall->hor_velocity;

	top->bot_left.x -= wall->hor_velocity;
	top->bot_right.x -= wall->hor_velocity;
	top->top_left.x -= wall->hor_velocity;
	top->top_right.x -= wall->hor_velocity;

	/* Checks if reset is needed */
	if (bottom->bot_right.x < L_BORDER_X && top->top_right.x < L_BORDER_X)
	{
		reset_wall(game, wall);
		return;
	}
}

void move_walls(Model *game){
	int i;
	unsigned int h_vel;

	Obs_wall (*walls)[4] = &(game->walls);

	for (i = 0; i < sizeof(walls)/sizeof(walls[0]); i++){
		Obs_wall *wall = walls[i];
		Obs *top = &(wall->top);
		Obs *bottom = &(wall->bottom);
		h_vel = wall -> hor_velocity;
	
		/* Checks if first initialization needed 
		if (bottom->top_left.y >= B_BORDER_Y | top->bot_left.y <= T_BORDER_Y)
		{
			init_obs_wall(&game->wall, gap_y());
		}
		*/
	
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

void reset_wall(Model *game, Obs_wall *wall)
{
	int i;
	/* Resets obstacle to right side of screen */
	init_wall(wall, gap_y());
	wall->been_passed = FALSE;

	/* Increase obstacle velocity if next level reached */
	
	if (game->score.value % 50 == 0)
	{
		Obs_wall (*walls)[4] = &(game->walls);
		for (i = 0; i < sizeof(walls); i++){
			walls[i] -> hor_velocity += 1;
		}
	}
}

void update_score(Model *game)
{
	int value;

	Score *score = &(game->score);

	if (score->value < score->max_value)
	{
		(score->value)++;
		value = score->value;
		(score->digits)[0].value = (value / 1000) % 10;
		(score->digits)[1].value = (value / 100) % 10;
		(score->digits)[2].value = (value / 10) % 10;
		(score->digits)[3].value = value % 10;
	}
}