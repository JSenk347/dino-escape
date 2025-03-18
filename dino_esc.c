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

int main()
{
    char key;
    int i;
    UINT32 curr_time, prev_time, time_elapsed;
    bool game_over = FALSE;
    
    /* INITIALIZE MODEL */
    void *base = Physbase();  
    void *front_buffer = base;  
    void *back_buffer = (void *)(((UINT32)pre_buffer + 255) & 0xFFFFFF00L);
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
     /* CLEAR SCREEN BUFFERS 
     clear_screen((UINT16 *)front_buffer, 0);
     clear_screen((UINT16 *)back_buffer, 0); */
     init_screen(&new_game, (UINT16 *)back_buffer);
     init_screen(&new_game, (UINT16 *)front_buffer);
     render_objs(&new_game, (UINT32 *)back_buffer);
     render_objs(&new_game, (UINT32 *)front_buffer);

     /* RUN GAME UNTIL GAME OVER*/ 
    
    while (!game_over) { 
        /* CHECKS FOR PENDING INPUT */
        if (Cconis()) {
            key = (char)Cnecin();
        }
    
        /* CHECK TIME */
        curr_time = get_time();
        time_elapsed = curr_time - prev_time;
        if (time_elapsed > 0) {
            prev_time = curr_time;
    
            /* PROCESS INPUT */
            process_input(&new_game, key);
            key = 0;
    
            move_walls(&new_game);
            check_collisions(&new_game);
            
            /* RENDER TO BACK BUFFER */
            render_objs(&new_game, (UINT32 *)back_buffer);
    
            /* SWAP BUFFERS (Vsync is already in swap_buffer) */
            swap_buffer(&front_buffer, &back_buffer);
            
        }
        if (new_game.game_state.lost_flag) {
            game_over = TRUE;
        }
    }

    Setscreen(-1, base, -1);
    return 0;
}

