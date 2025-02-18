/*******************************************************************************
 AUTHORS: Anna Running Rabbit, Jordan Senko, Joseph Mills
 COURSE: COMP2659-001
 INSTRUCTOR: Tim Reimer
 DATE: Feb.10, 2025
*******************************************************************************/
#include "model.h"

#include <stdio.h>

#define HALF_GAP 25
/*******************************************************************************
	PURPOSE: To move the dino vertically up or down the screen, while staying
		within the gameplay borders.
	INPUT: 	- pointer to the Dino object to be moved
			- 
	OUTPUT: N/A
*******************************************************************************/

void move_dino(Dino *dino, int direction)
{
	dino->y += (dino->vert_velocity*dino->vert_direction);

	unsigned int top_border = 57;
	unsigned int bottom_border = 83;
	unsigned int dino_height = 32;

	/* Limits dino movement to top border of gamescreen */
	if (dino->y <= top_border) {
		dino->vert_velocity = 0;
		dino->y = top_border + 1;
	}
	/* Limits dino movement to bottom border of gamescreen */
	if (dino->y >= 115){
		dino->vert_velocity = 0;
		dino->y = bottom_border - (dino_height + 1);
	}
}

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