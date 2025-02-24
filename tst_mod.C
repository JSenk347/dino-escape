/*******************************************************************************
 AUTHORS: Anna Running Rabbit, Jordan Senko, Joseph Mills
 COURSE: COMP2659-001
 INSTRUCTOR: Tim Reimer
 DATE: Feb.24, 2025

 SUMMARY: Tests all functions in model.c (incomplete, only initializes Models
            dino, obs_wall, and score variables for now)
*******************************************************************************/
#include <stdio.h>
#include "model.h"
#include "events.h"

#define SCREEN_WIDTH 680
#define GAP_CENTER   200
#define OBSTACLE_SPEED 3
#define TRUE 1
#define FALSE 0
#define X 1

int main() {
    int i;
    /* Initialize Model with Dino at (16, 184) */
    Model init_all = {
        {{16,184},{47,184},{16,215},{47,215},0,0},                    /* Dino variables */
        {{{0,0},{0,0},{0,0},{0,0}}, {{0,0},{0,0},{0,0},{0,0}}, 278},  /* Obs_wall variables */
        {{505,359},{632,359},{505,390},{632,390},                     /* Score variables */
            {{{505,359},{536,359},{505,390},{536,390},0},
            {{537,359},{568,359},{537,390},{568,390},0},
            {{569,359},{600,359},{568,390},{600,390},0},
            {{601,359},{632,359},{601,390},{632,390},0}},5000,0},
        {}                                                            /* Context variables */
    }; 

    printf("Initial Dino Position: Top-Left Y = %d\n", init_all.dino.top_left.y);

    /* Move Dino UP by setting negative velocity */
    init_all.dino.vert_velocity = 5;
    init_all.dino.vert_direction = -1;
    move_dino(&init_all.dino, init_all.dino.vert_direction);
    printf("Dino Position after moving UP: Top-Left Y = %d\n", init_all.dino.top_left.y);

    /* Move Dino DOWN by setting positive velocity */
    init_all.dino.vert_velocity = 5;
    init_all.dino.vert_direction = 1;
    move_dino(&init_all.dino, init_all.dino.vert_direction);
    printf("Dino Position after moving DOWN: Top-Left Y = %d\n", init_all.dino.top_left.y);

    /* Test Top Border Limit */
    init_all.dino.top_left.y = 49;  /* Just above top border (50) */
    init_all.dino.vert_velocity = 5;
    init_all.dino.vert_direction = -1;
    move_dino(&init_all.dino, init_all.dino.vert_direction);
    printf("Dino Position after hitting TOP border: Top-Left Y = %d\n", init_all.dino.top_left.y);

        /* Test Bottom Border Limit */
    init_all.dino.top_left.y = 351;
    init_all.dino.top_right.y = 351;
    init_all.dino.bot_left.y = 351 + DINO_HEIGHT - 1;   /* Ensure bottom matches top + height */
    init_all.dino.bot_right.y = 351 + DINO_HEIGHT - 1;

    init_all.dino.vert_velocity = 5;
    init_all.dino.vert_direction = 1;
    move_dino(&init_all.dino, init_all.dino.vert_direction);

    printf("Dino Position after hitting BOTTOM border: Top-Left Y = %d\n", init_all.dino.top_left.y);

    /* Place obstacle at the right side of the screen */
    move_obstacle(&init_all);
    
    return 0;
}
