/*******************************************************************************
 AUTHORS: Anna Running Rabbit, Jordan Senko, Joseph Mills
 COURSE: COMP2659-001
 INSTRUCTOR: Tim Reimer
 DATE: Feb.24, 2025

 SUMMARY: Tests all functions in model.c (incomplete, only initializes Models
            dino, obs_wall, and score variables for now)
*******************************************************************************/
#include <stdio.h>
#include "tst_mod.h"
#include "model.h"
#include "events.h"

int main()
{
    int i;
    /* Initialize Model with Dino at (16, 184) */

    Model new_game = {
        {{16, 184}, {47, 184}, {16, 215}, {47, 215}, 0, 0}, /* Dino variables */
        {
            {{{640, 50}, {672, 50}, {640, 200}, {672, 200}}, {{640, 251}, {672, 251}, {640, 351}, {672, 351}}, TRUE, FALSE, 200, OBS_START_SPEED},  /* wall 1 */
            {{{640, 50}, {672, 50}, {640, 200}, {672, 200}}, {{640, 251}, {672, 251}, {640, 351}, {672, 351}}, FALSE, FALSE, 200, OBS_START_SPEED}, /* wall 2 */
            {{{640, 50}, {672, 50}, {640, 200}, {672, 200}}, {{640, 251}, {672, 251}, {640, 351}, {672, 351}}, FALSE, FALSE, 200, OBS_START_SPEED}/*,
            {{{640, 50}, {672, 50}, {640, 200}, {672, 200}}, {{640, 251}, {672, 251}, {640, 351}, {672, 351}}, FALSE, FALSE, 200, OBS_START_SPEED}*/  /* wall 4 */
        },
        {{505, 359}, {632, 359}, {505, 390}, {632, 390}, {{{505, 359}, {536, 359}, {505, 390}, {536, 390}, 0}, {{537, 359}, {568, 359}, {537, 390}, {568, 390}, 0}, {{569, 359}, {600, 359}, {568, 390}, {600, 390}, 0}, {{601, 359}, {632, 359}, {601, 390}, {632, 390}, 0}}, 5000, 0},
        {FALSE, FALSE, FALSE}, /* Context variables */
    };

    wait_for_game_start(&new_game);
    /* init_obs_wall(&new_game.wall, gap_y()); already initialized above and at beginning of move_obstacles*/

    /* \033E clears the screen */
    printf("\033E");
    fflush(stdout);

    while (!new_game.game_state.dead_flag)
    {
        move_walls(&new_game); /* Happens first to prevent obstacle from moving after collision has occured */
        read_input(&new_game);
        check_collisions(&new_game);
        check_score(&new_game);

        /* moves the cursor to the top left of the page*/
        printf("\033H");

        printf("Score: %u\n", (int)new_game.score.value);
        printf("Dino Top Left (x,y): %3u,%3u\n",
               new_game.dino.top_left.x, new_game.dino.top_left.y);
        printf("WALL 1:\n");
        printf("Top Obs Bottom Right (x,y): %3i,%3i\n",
               new_game.walls[0].top.bot_right.x, new_game.walls[0].top.bot_right.y);
        printf("Bottom Obs Top Right (x,y): %3i,%3i\n",
               new_game.walls[0].bottom.top_right.x, new_game.walls[0].bottom.top_right.y);

        printf("WALL 2:\n");
        printf("Top Obs Bottom Right (x,y): %3i,%3i\n",
               new_game.walls[1].top.bot_right.x, new_game.walls[1].top.bot_right.y);
        printf("Bottom Obs Top Right (x,y): %3i,%3i\n",
               new_game.walls[1].bottom.top_right.x, new_game.walls[1].bottom.top_right.y);

        printf("WALL 3:\n");
        printf("Top Obs Bottom Right (x,y): %3i,%3i\n",
               new_game.walls[2].top.bot_right.x, new_game.walls[2].top.bot_right.y);
        printf("Bottom Obs Top Right (x,y): %3i,%3i\n",
               new_game.walls[2].top.top_right.x, new_game.walls[2].top.top_right.y);
        
        printf("NUM WALLS: %1i\n", NUM_WALLS);

        fflush(stdout);

        if (new_game.game_state.lost_flag)
        {
            printf("Game Over!\n");
        }
    }

    return 0;
}
