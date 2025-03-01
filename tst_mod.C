/*******************************************************************************
 AUTHORS:      Anna Running Rabbit, Jordan Senko, Joseph Mills
 COURSE:       COMP2659-001
 INSTRUCTOR:   Tim Reimer
 DATE:         Mar.2, 2025

 FILE: tst_mod.c
 SUMMARY: Tests all functions in model.c (incomplete, only initializes Models
            dino, obs_wall, and score variables for now)
*******************************************************************************/
#include <stdio.h>
#include "tst_mod.h"
#include "model.h"
#include "events.h"

int main() {
    int i;
    /* Initialize Model with Dino at (16, 184) */
    Model new_game = {
        {{16,184},{47,184},{16,215},{47,215},0,0},                                              /* Dino variables */
        {{{0,0},{0,0},{0,0},{0,0}}, {{0,0},{0,0},{0,0},{0,0}}, FALSE, 278, OBS_START_SPEED},    /* Obs variables */
        {{505,359},{632,359},{505,390},{632,390},                                               /* Score variables */
            {{{505,359},{536,359},{505,390},{536,390},0},
            {{537,359},{568,359},{537,390},{568,390},0},
            {{569,359},{600,359},{568,390},{600,390},0},
            {{601,359},{632,359},{601,390},{632,390},0}},5000,0},
        {0,FALSE,FALSE},                                                                        /* Context variables */
    }; 

    wait_for_game_start(&new_game);
    /* init_obs_wall(&new_game.wall, gap_y()); already initialized above and at beginning of move_obstacles*/
    while (!new_game.game_state.dead_flag) {
        move_obstacle(&new_game); /* Happens first to prevent obstacle from moving after collision has occured */
        handle_events(&new_game); 
        check_score(&new_game); 
        printf("Been Passed: %u\n", (int) new_game.wall.been_passed);
        printf("Score: %u\n", (int) new_game.score.value);
        printf("Dino Top Lt Y: %u | ", new_game.dino.top_left.y);
        printf("Dino Top Rt X: %u\n", new_game.dino.top_right.x);
        printf("Top Obs Bot Lt X: %u | ", new_game.wall.top.bot_left.x);
        printf("Top Obs Bot Rt X: %u | ", new_game.wall.top.bot_right.x);
        printf("Top Obs Bot Lt Y: %u\n", new_game.wall.top.bot_left.y);
        if (new_game.game_state.lost_flag) {
            printf("Game Over!\n");
        }
    }
    return 0;
}
