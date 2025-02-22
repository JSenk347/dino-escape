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

/*******************************************************************************
    PURPOSE: Moves the dino vertically up or down the screen, while staying
             within the gameplay borders.
    INPUT:
      - dino: pointer to the Dino object to be moved
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
    PURPOSE: Initializes one obstacle wall (both top and bottom rectangles),
             placing it at a specified X position and with a specified gap.
    INPUT:
      - wall: pointer to the Obs_wall struct to initialize
      - x: initial X position for the obstacle
      - gap_y: the vertical center of the gap between top and bottom rectangles
    OUTPUT: N/A
*******************************************************************************/
void init_obs_wall(Obs_wall *wall, unsigned int x, unsigned int gap_y)
{
    /* Bottom Obstacle Rectangle */
    wall->bottom.top_left.x     = x;
    wall->bottom.top_left.y     = gap_y - HALF_GAP;
    wall->bottom.top_right.x    = x + (OBSTACLE_WIDTH - 1);
    wall->bottom.top_right.y    = gap_y - HALF_GAP;

    wall->bottom.bot_left.x     = x;
    wall->bottom.bot_left.y     = gap_y - HALF_GAP + 32;
    wall->bottom.bot_right.x    = x + (OBSTACLE_WIDTH - 1);
    wall->bottom.bot_right.y    = gap_y - HALF_GAP + 32;

    /* Top Obstacle Rectangle */
    wall->top.top_left.x        = x;
    wall->top.top_left.y        = gap_y + HALF_GAP - 32;
    wall->top.top_right.x       = x + (OBSTACLE_WIDTH - 1);
    wall->top.top_right.y       = gap_y + HALF_GAP - 32;

    wall->top.bot_left.x        = x;
    wall->top.bot_left.y        = gap_y + HALF_GAP;
    wall->top.bot_right.x       = x + (OBSTACLE_WIDTH - 1);
    wall->top.bot_right.y       = gap_y + HALF_GAP;
}

/*******************************************************************************
    PURPOSE: Moves obstacle walls horizontally to the left. If the obstacle moves
             off the left side of the screen, it is reset to the right.
    INPUT:
      - wall: pointer to the Obs_wall struct to move
      - speed: integer speed by which the obstacle moves left each frame
    OUTPUT: N/A
*******************************************************************************/
void move_obstacles(Obs_wall *wall, int speed) {
    /* Move bottom obstacle to the left */
    wall->bottom.top_left.x   -= speed;
    wall->bottom.top_right.x  -= speed;
    wall->bottom.bot_left.x   -= speed;
    wall->bottom.bot_right.x  -= speed;

    /* Move top obstacle to the left */
    wall->top.top_left.x      -= speed;
    wall->top.top_right.x     -= speed;
    wall->top.bot_left.x      -= speed;
    wall->top.bot_right.x     -= speed;

    /* ✅ Fix: Check if obstacle has moved fully off the left edge */
    if (wall->bottom.top_right.x <= 0) {
        unsigned int reset_x = SCREEN_WIDTH;  /* Reset to right side of the screen */

        /* Reset bottom obstacle's X coordinates */
        wall->bottom.top_left.x    = reset_x;
        wall->bottom.top_right.x   = reset_x + (OBSTACLE_WIDTH - 1);
        wall->bottom.bot_left.x    = reset_x;
        wall->bottom.bot_right.x   = reset_x + (OBSTACLE_WIDTH - 1);

        /* Reset top obstacle's X coordinates */
        wall->top.top_left.x       = reset_x;
        wall->top.top_right.x      = reset_x + (OBSTACLE_WIDTH - 1);
        wall->top.bot_left.x       = reset_x;
        wall->top.bot_right.x      = reset_x + (OBSTACLE_WIDTH - 1);
    }
}

