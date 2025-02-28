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
    Model new_game = {
        {{16,184},{47,184},{16,215},{47,215},0,0},                    /* Dino variables */
        {{{0,0},{0,0},{0,0},{0,0}}, {{0,0},{0,0},{0,0},{0,0}}, FALSE, 278},  /* Obs_wall variables */
        {{505,359},{632,359},{505,390},{632,390},                     /* Score variables */
            {{{505,359},{536,359},{505,390},{536,390},0},
            {{537,359},{568,359},{537,390},{568,390},0},
            {{569,359},{600,359},{568,390},{600,390},0},
            {{601,359},{632,359},{601,390},{632,390},0}},5000,0},
        {0,0,0},                                                            /* Context variables */
    }; 

    wait_for_game_start(&new_game);
    init_obs_wall(&new_game.wall, gap_y());
    while (!new_game.game_state.dead_flag) {
        handle_events(&new_game);  
        move_obstacle(&new_game);

        printf("Dino Y: %u | Bottom Obstacle Top-Left Y: %u "
            "| Top Obstacle Top-Left Y: %u | Score: %u\n",
            new_game.dino.top_right.y,
            new_game.wall.bottom.top_left.y,
            new_game.wall.top.bot_left.y,
            new_game.score.value);
     
     
        if (new_game.game_state.dead_flag) {
            printf("Game Over!\n");
        }
    }
    return 0;
}
