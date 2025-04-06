
/*******************************************************************************
 AUTHORS: Anna Running Rabbit, Jordan Senko, Joseph Mills
 COURSE: COMP2659-001
 INSTRUCTOR: Tim Reimer
 DATE: Mar.21, 2025

 FILE: dino_esc.c
 SUMMARY: Contains the main game module for Dino Escape
*******************************************************************************/
#include "base.h"
#include "screen.h"
#include "render.h"
#include "events.h"
#include "model.h"
#include "raster.h"
#include "input.h"
#include "bitmaps.h"
#include "clock.h"
#include "types.h"
#include "music.h"
#include "psg.h"
#include "vbl.h"
#include "isr.h"
#include <stdio.h>
#include <osbind.h>
#include <linea.h>

    UINT8 pre_buffer[32255]; /* 32255 = 320 * 200 + 15 */
    extern UINT8 IKBD_buffer[256];     
    extern void install_vectors();
    extern void remove_vectors();
    extern long kbd_read_char(bool update_head);
    extern bool kbd_is_waiting();
    extern void clear_kbd_buffer();
    int seconds = 0;
int main()
{    
    int x;
    extern UINT8 head, tail;           
    char key = 0;
    extern int render_request;
    extern int key_update_ticks;
    extern bool key_repeat;
    char key;
    bool has_run_once = FALSE;  /* loop control variable */
    UINT32 curr_time, prev_time, time_elapsed;
    Scale scale;
    Song song;
    bool game_over = FALSE;
    int input;
    char ascii_key;


    /* INITIALIZE MODEL */
    UINT8 *base = get_video_base();
    void *front_buffer = base;
    void *back_buffer = (void *)(((UINT32)pre_buffer + 255) & 0xFFFFFF00L); 

    Model new_game = {
        {{32, 184}, {63, 184}, {32, 215}, {63, 215}, {32, 184}, 0, 0, 0}, /* Dino */
        {
            {{{640, 50}, {671, 50}, {640, 200}, {671, 200}},    /* Wall 1 - top */
            {{640, 249}, {671, 249}, {640, 349}, {671, 349}},   /* Wall 1 - bottom */
            TRUE, FALSE, 200, OBS_START_SPEED},
            {{{640, 50}, {671, 50}, {640, 200}, {671, 200}},    /* Wall 2 - top */
            {{640, 249}, {671, 249}, {640, 349}, {671, 349}},   /* Wall 2 - bottom */
            FALSE, FALSE, 200, OBS_START_SPEED},
            {{{640, 50}, {671, 50}, {640, 200}, {671, 200}},    /* Wall 3 - top */
            {{640, 249}, {671, 249}, {640, 349}, {671, 349}},   /* Wall 3 - bottom */
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

    /* SPLASH SCREEN */
    render_request = TRUE; /* Set render request flag */
    
    init_screen(&new_game, (UINT16 *)front_buffer);
    init_screen(&new_game, (UINT16 *)back_buffer);
    render_objs(&new_game, (UINT32 *)back_buffer);
    render_objs(&new_game, (UINT32 *)front_buffer);
    
    install_vectors();
     /*Waiting for enter or quit */
    clear_kbd_buffer(); /* Clear buffer at start */

    ascii_key = 0;
    /* Wait for user to press 'w' key (ASCII) */
    while (ascii_key != 'w') {
        while (!kbd_is_waiting()); /* Wait here */

        ascii_key = kbd_read_char(1) & 0xFF; /* ASCII */
    } 
    key = (char)ascii_key; 
    start_or_quit(&new_game, key);

    if (new_game.game_state.start_flag) {
        clr_start((UINT32 *)back_buffer);
        clr_start((UINT32 *)front_buffer);
    }

    /*scale = init_scale();
    init_song(&song, scale); */ 
    
     /* RUN GAME UNTIL GAME OVER*/ 
    prev_time = seconds;
    start_music(song); 
    while (game_over == FALSE) {
        render_request = 1; /* Set render request flag */
        /* CHECKS FOR PENDING INPUT  */
        if (kbd_is_waiting()) { key = kbd_read_char(1) & 0xFF;} /* ASCII */
        time_elapsed = curr_time - prev_time;
        /* CHECKS FOR CLOCK TICK */
        curr_time = get_time();
        time_elapsed = curr_time - prev_time; 
        if (time_elapsed > 0) {
            /* PROCESS SYNCHRONOUS EVENTS */

            /* Moves dino */
            if (!new_game.game_state.dead_flag) {
                process_input(&new_game, key);
                key = NULL;                     /* Resets input key */
            }
            /* Moves walls */
            move_walls(&new_game);
            /* Checks for collsion */
            check_collisions(&new_game);
            /* Checks score */
            check_score(&new_game);

            update_music(time_elapsed, &song); 
                
            /* RENDER MODEL (NEXT FRAME) */ 
            render_objs(&new_game, (UINT32 *)back_buffer);
            swap_buffer(&front_buffer, &back_buffer);
            clear_cave_region((UINT32 *)back_buffer);
        }
         if (new_game.game_state.lost_flag == TRUE) {
             game_over = TRUE;
        }

        /* Syncs both buffers once collision has occured */
        if (new_game.game_state.dead_flag && /* lcv */ has_run_once != TRUE){
            render_objs(&new_game, (UINT32 *)back_buffer);
            /* lcv */ has_run_once = TRUE;
        }
    }
    stop_sound();
    init_screen(&new_game, (UINT16 *)base);
    set_video_base((UINT16*)base); 
    remove_vectors();
    return 0;
}