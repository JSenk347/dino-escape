/*******************************************************************************
 AUTHORS: Anna Running Rabbit, Jordan Senko, Joseph Mills
 COURSE: COMP2659-001
 INSTRUCTOR: Tim Reimer
 DATE: Feb.10, 2025
*******************************************************************************/
#include "model.h"
#include <stdio.h>

#define HALF_GAP 25
#define TOP_BORDER 50
#define BOTTOM_BORDER 350
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
	if (dino->top_left.y <= TOP_BORDER) {
		dino->vert_velocity = 0;
		dino->top_left.y = TOP_BORDER + 1;
		dino->top_right.y = TOP_BORDER + 1;
		dino->bot_left.y = TOP_BORDER + (DINO_HEIGHT + 1);
		dino->bot_right.y = TOP_BORDER + (DINO_HEIGHT + 1);
	}
	/* Limits dino movement to bottom border of gamescreen */
	if (dino->bot_left.y >= BOTTOM_BORDER){
		dino->vert_velocity = 0;
		dino->top_left.y = BOTTOM_BORDER - (DINO_HEIGHT + 1);
		dino->top_right.y = BOTTOM_BORDER - (DINO_HEIGHT + 1);
		dino->bot_left.y = BOTTOM_BORDER - 1;
		dino->bot_right.y = BOTTOM_BORDER - 1;
	}
}

/*******************************************************************************
	PURPOSE:
	INPUT: 	
	OUTPUT: N/A
*******************************************************************************/
void init_obs_wall(Obs_wall *wall, unsigned int x, unsigned int gap_y) {
	/* Bottom Obstacle */
	wall -> bottom.top_left.x = x;
	wall -> bottom.top_left.y = gap_y - HALF_GAP;
	wall -> bottom.top_right.x = x + 31;
	wall -> bottom.top_right.y = gap_y - HALF_GAP;

	wall -> bottom.bot_left.x = 
	wall -> bottom.bot_left.y = 
	wall -> bottom.bot_right.x = 
	wall -> bottom.bot_right.y =   
	
	/* Top Obstacle */
	wall -> top.top_left.x =
	wall -> top.top_left.y =
	wall -> top.top_right.x =
	wall -> top.top_right.y = 

	wall -> top.bot_left.x = x;
	wall -> top.bot_left.y = gap_y + HALF_GAP;
	wall -> top.bot_right.x = x + 31;
	wall -> top.bot_right.y = gap_y + HALF_GAP;
}