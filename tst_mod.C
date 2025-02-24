/******************************************************************************* 
 AUTHORS: Anna Running Rabbit, Jordan Senko, Joseph Mills 
 COURSE: COMP2659-001 
 INSTRUCTOR: Tim Reimer 
 DATE: Feb.10, 2025 
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
        {{16,184},{16,184},{16,184},{16,184},0,0},   /* Dino variables */
        {{{0,0},{0,0},{0,0},{0,0}}, {{0,0},{0,0},{0,0},{0,0}}, 278},  /* Obs_wall variables */
        {{311,359},{407,359},{311,391},{407,391},5000,0} /* Score variables */
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
