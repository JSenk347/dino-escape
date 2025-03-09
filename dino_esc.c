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
#include "tst_mod.h"
#include "bitmaps.h"
#include <stdio.h>
#include <osbind.h>
#include <linea.h>
int main()
{
    /* INITIALIZE MODEL */
    void *base = Physbase();
    unsigned int game_over = FALSE;
    
    Model new_game = {
        {{16, 184}, {47, 184}, {16, 215}, {47, 215}, {16, 184}, 0, 0, 0}, /* Dino variables */
        {
            {{{640, 50}, {672, 50}, {640, 200}, {672, 200}}, {{640, 251}, {672, 251}, {640, 351}, {672, 351}}, TRUE, FALSE, 200, OBS_START_SPEED},  /* wall 1 */
            {{{640, 50}, {672, 50}, {640, 200}, {672, 200}}, {{640, 251}, {672, 251}, {640, 351}, {672, 351}}, FALSE, FALSE, 200, OBS_START_SPEED}, /* wall 2 */
            {{{640, 50}, {672, 50}, {640, 200}, {672, 200}}, {{640, 251}, {672, 251}, {640, 351}, {672, 351}}, FALSE, FALSE, 200, OBS_START_SPEED}, /* wall 3 */
        },
        {{{{505, 359}, {536, 359}, {505, 390}, {536, 390}, 0},  /* ones digit */
          {{537, 359}, {568, 359}, {537, 390}, {568, 390}, 0},  /* tens digit */
          {{569, 359}, {600, 359}, {568, 390}, {600, 390}, 0},  /* hundreds digit */
          {{601, 359}, {632, 359}, {601, 390}, {632, 390}, 0}}, /* thousands digit */
         5000,                                                  /* max score value */
         0},                                                    /* current score value */
        {FALSE, FALSE, FALSE}, /* Context variables */
    };
    linea0();
    disable_cursor();

    /* RENDER FIRST FRAME OF MODEL */
        init_screen((UINT16 *)base);
        render_game(&new_game, (UINT32 *)base);
        render_start(&new_game, (UINT32 *)base);
        wait_for_game_start(&new_game);
        init_screen((UINT16 *)base);
        render_game(&new_game, (UINT32 *)base);

        
        /* RUN GAME UNTIL GAME OVER */
        while (game_over == FALSE) {
            read_input(&new_game);
            check_score(&new_game); 
            check_conditions(&new_game); 
            /*if input is pending
                process async event
            if clock has ticked
                process sync events
                render model (next frame)*/
            
            if (new_game.game_state.dead_flag == TRUE || new_game.game_state.lost_flag == TRUE) {
                game_over = TRUE;
                while(!(dino->bot_left.y >= B_BORDER_Y)){
                    reflect_dino_death(Model *new_game);
                    render_dino_dead(&new_game, (UINT32 *)base);
                }
                /* Restarting game maybe needs a new function
                render_start(&new_game, (UINT32 *)base);
                wait_for_game_start(&new_game); */
                
                
            }
            
        }
    }
    return 0;
}