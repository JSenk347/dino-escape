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
void move_dino(Dino *dino) {
	/* Store previous top left y vertex coordinates */
	dino -> prev_top_lt = dino -> top_left;

	dino -> top_left.y += (dino->vert_velocity*dino->vert_direction);
	dino -> top_right.y += (dino->vert_velocity*dino->vert_direction);
	dino -> bot_left.y += (dino->vert_velocity*dino->vert_direction);
	dino -> bot_right.y += (dino->vert_velocity*dino->vert_direction);

	/* Limits dino movement to top border of gamescreen */
	if (dino->top_left.y <= T_BORDER_Y && dino->vert_direction == -1) {
		dino->vert_velocity = 0;
		dino->top_left.y = T_BORDER_Y + 1;
		dino->top_right.y = T_BORDER_Y + 1;
		dino->bot_left.y = T_BORDER_Y + (DINO_HEIGHT + 1);
		dino->bot_right.y = T_BORDER_Y + (DINO_HEIGHT + 1);
	}
	/* Limits dino movement to bottom border of gamescreen */
	if (dino->bot_left.y >= B_BORDER_Y && dino->vert_direction == 1){
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
	/* Store previous top left y vertex coordinates */
	wall -> bottom.prev_top_lt = wall -> bottom.top_left;
	wall -> top.prev_top_lt = wall -> top.top_left;

	/* Bottom Obstacle */
	wall -> bottom.top_left.x = R_BORDER_X;
	wall -> bottom.top_left.y = gap_y + HALF_GAP;
	wall -> bottom.top_right.x = R_BORDER_X + 31;
	wall -> bottom.top_right.y = gap_y + HALF_GAP;

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
	wall -> top.bot_left.y = gap_y - HALF_GAP;
	wall -> top.bot_right.x = R_BORDER_X + 31;
	wall -> top.bot_right.y = gap_y - HALF_GAP;
	wall -> been_passed = FALSE;
	wall -> gap_y = gap_y;
}

/*******************************************************************************
	PURPOSE: 
	INPUT: 	
	OUTPUT: N/A
*******************************************************************************/
unsigned int gap_y(){
	srand(time(0));
	/* returning a random int from 50 - 291 (inclusive)*/
	return rand() % 242 + 50;
}

/*******************************************************************************
	PURPOSE: 
	INPUT: 	
	OUTPUT: N/A
*******************************************************************************/
void move_obstacles(Model *game){

	game -> wall.bottom.bot_left.x -= game -> wall.hor_velocity;
	game -> wall.bottom.bot_right.x -= game -> wall.hor_velocity;
	game -> wall.bottom.top_left.x -= game -> wall.hor_velocity;
	game -> wall.bottom.top_right.x -= game -> wall.hor_velocity;
	
	game -> wall.top.bot_left.x -= game -> wall.hor_velocity;
	game -> wall.top.bot_right.x -= game -> wall.hor_velocity;
	game -> wall.top.top_left.x -= game -> wall.hor_velocity;
	game -> wall.top.top_right.x -= game -> wall.hor_velocity;

	/* Checks if reset is needed */
	if (game -> wall.bottom.bot_right.x < L_BORDER_X && game -> wall.top.top_right.x < L_BORDER_X){
		reset_obs(game);
		return;
	}
}

void reset_obs(Model *game){
	/* Resets obstacle to right side of screen */
	init_obs_wall(&game -> wall, gap_y());

	/* Increase obstacle velocity if next level reached */
	if (game -> score.value % 50 == 0){
		game -> wall.hor_velocity += 1;
	}
}

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
        (score -> digits)[0].value = value % 10;			/* ones digit */
    }
}