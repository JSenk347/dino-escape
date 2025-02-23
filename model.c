/*******************************************************************************
 AUTHORS: Anna Running Rabbit, Jordan Senko, Joseph Mills
 COURSE: COMP2659-001
 INSTRUCTOR: Tim Reimer
 DATE: Feb.10, 2025
*******************************************************************************/
#include "model.h"
#include <stdio.h>
#include <ctime>
#include <cstdlib>

#define HALF_GAP 25
#define T_BORDER_Y 49
#define B_BORDER_Y 349
#define R_BORDER_X 639
#define L_BORDER_X 0
#define DINO_HEIGHT 32

/*******************************************************************************
	PURPOSE: To move the dino vertically up or down the screen, while staying
				within the gameplay borders.
	INPUT: 	- dino: pointer to the Dino object to be moved
			- direction: integer set as either -1 or +1 used to determine up or
				down movement
	OUTPUT: N/A
*******************************************************************************/
void move_dino(Dino *dino, int direction)
{
	dino->top_left.y += (dino->vert_velocity*dino->vert_direction);
	dino->top_right.y += (dino->vert_velocity*dino->vert_direction);
	dino->bot_left.y += (dino->vert_velocity*dino->vert_direction);
	dino->bot_right.y += (dino->vert_velocity*dino->vert_direction);

	/* Limits dino movement to top border of gamescreen */
	if (dino->top_left.y <= T_BORDER_Y) {
		dino->vert_velocity = 0;
		dino->top_left.y = T_BORDER_Y + 1;
		dino->top_right.y = T_BORDER_Y + 1;
		dino->bot_left.y = T_BORDER_Y + (DINO_HEIGHT + 1);
		dino->bot_right.y = T_BORDER_Y + (DINO_HEIGHT + 1);
	}
	/* Limits dino movement to bottom border of gamescreen */
	if (dino->bot_left.y >= B_BORDER_Y){
		dino->vert_velocity = 0;
		dino->top_left.y = B_BORDER_Y - (DINO_HEIGHT + 1);
		dino->top_right.y = B_BORDER_Y - (DINO_HEIGHT + 1);
		dino->bot_left.y = B_BORDER_Y - 1;
		dino->bot_right.y = B_BORDER_Y - 1;
	}
}

/*******************************************************************************
	PURPOSE: 
	INPUT: 	
	OUTPUT: N/A
*******************************************************************************/
void init_obs_wall(Obs_wall *wall, unsigned int gap_y) {
	/* Bottom Obstacle */
	wall -> bottom.top_left.x = R_BORDER_X;
	wall -> bottom.top_left.y = gap_y - HALF_GAP;
	wall -> bottom.top_right.x = R_BORDER_X + 31;
	wall -> bottom.top_right.y = gap_y - HALF_GAP;

	wall -> bottom.bot_left.x = R_BORDER_X;
	wall -> bottom.bot_left.y = B_BORDER_Y - 1;
	wall -> bottom.bot_right.x = R_BORDER_X + 31;
	wall -> bottom.bot_right.y = B_BORDER_Y -1;  
	
	/* Top Obstacle */
	wall -> top.top_left.x = R_BORDER_X;
	wall -> top.top_left.y = T_BORDER_Y + 1;
	wall -> top.top_right.x = R_BORDER_X + 31;
	wall -> top.top_right.y = T_BORDER_Y + 1;

	wall -> top.bot_left.x = R_BORDER_X;
	wall -> top.bot_left.y = gap_y + HALF_GAP;
	wall -> top.bot_right.x = R_BORDER_X + 31;
	wall -> top.bot_right.y = gap_y + HALF_GAP;
}

unsigned int gap_y(){
	srand(time(0));
	/* returning a random int from 50 - 291 (inclusive)*/
	return rand() % 242 + 50;
}

void move_obstacles(Obs_wall *wall, unsigned int velocity){
	if (wall -> bottom.bot_right.x < L_BORDER_X && wall -> top.top_right.x < L_BORDER_X){
		init_obs_wall(wall, gap_y());
		return;
	}
	
	wall -> bottom.bot_left.x = wall -> bottom.bot_left.x - velocity;
	wall -> bottom.bot_right.x = wall -> bottom.bot_right.x - velocity;
	wall -> bottom.top_left.x = wall -> bottom.top_left.x - velocity;
	wall -> bottom.top_right.x = wall -> bottom.top_right.x - velocity;
	
	wall -> top.bot_left.x = wall -> top.bot_left.x - velocity;
	wall -> top.bot_right.x = wall -> top.bot_right.x - velocity;
	wall -> top.top_left.x = wall -> top.top_left.x - velocity;
	wall -> top.top_right.x = wall -> top.top_right.x - velocity;
}