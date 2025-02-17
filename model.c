/*******************************************************************************
 AUTHORS: Anna Running Rabbit, Jordan Senko, Joseph Mills
 COURSE: COMP2659-001
 INSTRUCTOR: Tim Reimer
 DATE: Feb.10, 2025
*******************************************************************************/
#include "model.h"

#include <stdio.h>

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