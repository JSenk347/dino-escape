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

UINT8 pre_buffer[32255]; /* 32255 = 320 * 200 + 15 */
UINT8 pre_buffer1[32255]; 


int main()
{
    char key;
    int x;  
    int i;
    UINT32 curr_time, prev_time, time_elapsed;
    bool game_over = FALSE;
    
    /* INITIALIZE MODEL */
    void *base = Physbase();  
    void *back_buffer = base;  
    void *back1_buffer = (void *)(((UINT32)pre_buffer + 255) & 0xFFFFFF00L); 
    void *back2_buffer = base; 
    
    Model new_game = {
        {{32, 184}, {63, 184}, {32, 215}, {63, 215}, {32, 184}, 0, 0, 0}, /* Dino */
        {
            {{{640, 50}, {671, 50}, {640, 200}, {671, 200}},    /* Wall 1 - top */
            {{640, 249 /*250*/}, {671, 249 /*250*/}, {640, 349 /*350*/}, {671, 349 /*350*/}},   /* Wall 1 - bottom */
            TRUE, FALSE, 200, OBS_START_SPEED},
            {{{640, 50}, {671, 50}, {640, 200}, {671, 200}},    /* Wall 2 - top */
            {{640, 249 /*250*/}, {671, 249 /*250*/}, {640, 349 /*350*/}, {671, 349 /*350*/}},   /* Wall 2 - bottom */
            FALSE, FALSE, 200, OBS_START_SPEED},
            {{{640, 50}, {671, 50}, {640, 200}, {671, 200}},    /* Wall 3 - top */
            {{640, 249 /*250*/}, {671, 249 /*250*/}, {640, 349 /*350*/}, {671, 349 /*350*/}},   /* Wall 3 - bottom */
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
    init_screen(&new_game, (UINT16 *)back2_buffer);
    init_screen(&new_game, (UINT16 *)back1_buffer);
    render_objs(&new_game, (UINT32 *)back2_buffer);
    render_objs(&new_game, (UINT32 *)back1_buffer);
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
        /* CHECKS FOR PENDING INPUT */ 
        /*read_input(&new_game);*/
        if (new_game.game_state.dead_flag && x != TRUE){
            render_objs(&new_game, (UINT32 *)back2_buffer);
            render_objs(&new_game, (UINT32 *)back1_buffer);
            x = TRUE;
        }
        if (Cconis()) {
            key = (char)Cnecin();
            /*while (Cconis()) {
                Cnecin();
            }*/
        }

        /* CHECKS FOR CLOCK TICK */
        curr_time = get_time();
        time_elapsed = curr_time - prev_time;
        if (time_elapsed > 0) {
            /* PROCESS SYNCHRONOUS EVENTS */
            if (!new_game.game_state.dead_flag) {
                process_input(&new_game, key);  /* Moves dino */
                key = NULL;                     /* Resets input key */
            }

            move_walls(&new_game);
            check_collisions(&new_game);
                
            /* RENDER MODEL (NEXT FRAME) */ 
            render_objs(&new_game, (UINT32 *)back2_buffer);
            swap_buffer(&back1_buffer, &back2_buffer); 
            clear_cave_region((UINT32 *)back2_buffer);
            /*clear_cave_region((UINT32 *)back2_buffer); */
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
    Setscreen(-1, base, -1);
    return 0;
}