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

#define SCREEN_WIDTH 640
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
        {0,0,0},                                                            /* Context variables */
    }; 

    wait_for_game_start(&init_all);
    init_obs_wall(&init_all.wall, gap_y());
    while (!init_all.game_state.dead_flag) {
        handle_events(&init_all);  
        move_obstacle(&init_all);

        printf("Dino Y: %u | Bottom Obstacle Top-Left Y: %u "
            "| Top Obstacle Top-Left Y: %u | Score: %u\n",
            init_all.dino.top_right.y,
            init_all.wall.bottom.top_left.y,
            init_all.wall.top.bot_left.y,
            init_all.score.value);
     
     
        if (init_all.game_state.dead_flag) {
            printf("Game Over!\n");
        }
    }
    return 0;
}
