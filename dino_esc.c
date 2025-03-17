/*******************************************************************************
 AUTHORS: Anna Running Rabbit, Jordan Senko, Joseph Mills
 COURSE: COMP2659-001
 INSTRUCTOR: Tim Reimer
 DATE: Mar.21, 2025

 FILE: dino_esc.c
 SUMMARY: Contains the main game module for Dino Escape
*******************************************************************************/
#include "render.h"
#include "events.h"
#include "model.h"
#include "raster.h"
#include "input.h"
#include "bitmaps.h"
#include "clock.h"
#include <stdio.h>
#include <osbind.h>
#include <linea.h>


int main()
{
    char key;
    int i;
    UINT32 curr_time, prev_time, time_elapsed;
    bool game_over = FALSE;
    
    /* INITIALIZE MODEL */
    void *base = Physbase();
    
    Model new_game = {
        {{32, 184}, {63, 184}, {32, 215}, {63, 215}, {32, 184}, 0, 0, 0}, /* Dino */
        {
            {{{640, 50}, {671, 50}, {640, 200}, {671, 200}},    /* Wall 1 - top */
            {{640, 250 /*251*/}, {671, 250 /*251*/}, {640, 350 /*351*/}, {671, 350 /*351*/}},   /* Wall 1 - bottom */
            TRUE, FALSE, 200, OBS_START_SPEED},
            {{{640, 50}, {671, 50}, {640, 200}, {671, 200}},    /* Wall 2 - top */
            {{640, 250 /*251*/}, {671, 250 /*251*/}, {640, 350 /*351*/}, {671, 350 /*351*/}},   /* Wall 2 - bottom */
            FALSE, FALSE, 200, OBS_START_SPEED},
            {{{640, 50}, {671, 50}, {640, 200}, {671, 200}},    /* Wall 3 - top */
            {{640, 250 /*251*/}, {671, 250 /*251*/}, {640, 350 /*351*/}, {671, 350 /*351*/}},   /* Wall 3 - bottom */
            FALSE, FALSE, 200, OBS_START_SPEED},
        },
        {{{{505, 359}, {536, 359}, {505, 390}, {536, 390}, 0},  /* Ones digit */
          {{537, 359}, {568, 359}, {537, 390}, {568, 390}, 0},  /* Tens digit */
          {{569, 359}, {600, 359}, {568, 390}, {600, 390}, 0},  /* Hundreds digit */
          {{601, 359}, {632, 359}, {601, 390}, {632, 390}, 0}}, /* Thousands digit */
         5000,                                                  /* Max score */
         0},                                                    /* Current score */
        {FALSE, FALSE, FALSE},                                  /* Game state */
    };
    linea0();
    /*disable_cursor(); Not needed here, already called in init_screen() */

    /* RENDER FIRST FRAME OF MODEL */
    init_screen(&new_game, (UINT16 *)base);
    render_objs(&new_game, (UINT32 *)base);

     /* RUN GAME UNTIL GAME OVER 
     while (game_over == FALSE){
        move_walls(&new_game);
        read_input(&new_game);
        check_collisions(&new_game);
        check_score(&new_game);

        if (new_game.game_state.lost_flag == TRUE){
            game_over = TRUE;
        }
     }*/

     /* RUN GAME UNTIL GAME OVER*/ 
    while (game_over == FALSE) {
        /* Checks for input pending*/ 
        /*read_input(&new_game);*/
        if (Cconis()) {
            key = (char)Cnecin();
            /*while (Cconis()) {
                Cnecin();
            }*/
        }

        /* Checks for clock tick */
        curr_time = get_time();
        time_elapsed = curr_time - prev_time;
        if (time_elapsed > 0) {
            /* Process synchronous events */
            process_input(&new_game, key);
            key = NULL; /* Reset input key */

            move_walls(&new_game);
            check_collisions(&new_game);
                
            /* Render model (next frame)*/ 
            render_objs(&new_game, (UINT32 *)base);
             
            /*if (!new_game.game_state.dead_flag) {
                move_walls(&new_game);
                check_collisions(&new_game);
                
                /* Render model (next frame)*/ 
                /*render_objs(&new_game, (UINT32 *)base);
            }
            else {
                reflect_dino_death(&new_game);

                 /*Render model (next frame) */
                /*render_objs(&new_game, (UINT32 *)base);
            }*/

            prev_time = curr_time;
        }
         if (new_game.game_state.lost_flag == TRUE) {
             game_over = TRUE;
        }
    } 
    return 0;
}