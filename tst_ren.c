/*******************************************************************************
 AUTHORS: Anna Running Rabbit, Jordan Senko, Joseph Mills
 COURSE: COMP2659-001
 INSTRUCTOR: Tim Reimer
 DATE: Mar. 2, 2025

 FILE: tst_ren.c
 SUMMARY: Source file for the test driver program.
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
    int i;
	void *base = Physbase();
    Model new_game = {
        {{16,184},{47,184},{16,215},{47,215},0,0,0},                    /* Dino variables */
        {{{0,0},{0,0},{0,0},{0,0}}, {{0,0},{0,0},{0,0},{0,0}}, FALSE, 278, OBS_START_SPEED},  /* Obs variables */
        {{505,359},{632,359},{505,390},{632,390},                     /* Score variables */
            {{{505,359},{536,359},{505,390},{536,390},0},
            {{537,359},{568,359},{537,390},{568,390},0},
            {{569,359},{600,359},{568,390},{600,390},0},
            {{601,359},{632,359},{601,390},{632,390},0}},5000,0},
        {0,0,0},                                                            /* Context variables */
    };
    
    

    linea0(); /*needed to call any plot line functions*/
	disable_cursor();
    /* 1. Show screen for ststtart page */
    render_screen((UINT16 *)base);
    plot_borders();
    render_dino(&new_game, (UINT32 *)base);
    plot_bitmap_32((UINT32 *)base, 311, 359, zero_bitmap, HEIGHT_32, 1);
    plot_bitmap_32((UINT32 *)base, 343, 359, one_bitmap, HEIGHT_32, 1);
    plot_bitmap_32((UINT32 *)base, 375, 359, two_bitmap, HEIGHT_32, 1);
    plot_bitmap_32((UINT32 *)base, 407, 359, three_bitmap, HEIGHT_32, 1);
    plot_bitmap_32((UINT32 *)base, 439, 359, four_bitmap, HEIGHT_32, 1);
    plot_bitmap_32((UINT32 *)base, 471, 359, five_bitmap, HEIGHT_32, 1);
    plot_bitmap_32((UINT32 *)base, 503, 359, six_bitmap, HEIGHT_32, 1);
    plot_bitmap_32((UINT32 *)base, 535, 359, seven_bitmap, HEIGHT_32, 1);
    plot_bitmap_32((UINT32 *)base, 567, 359, eight_bitmap, HEIGHT_32, 1);
    plot_bitmap_32((UINT32 *)base, 599, 359, white, HEIGHT_32, 1);
    

    render_start(&new_game, (UINT32 *)base);
    wait_for_game_start(&new_game);
/* 2. Game has been started rerender without start */
    render_screen((UINT16 *)base);
    plot_borders();
    plot_bitmap_32((UINT32 *)base, 311, 359, black, HEIGHT_32, 1);
    plot_bitmap_32((UINT32 *)base, 343, 359, black, HEIGHT_32, 1);
    plot_bitmap_32((UINT32 *)base, 375, 359, black, HEIGHT_32, 1);
    plot_bitmap_32((UINT32 *)base, 407, 359, black, HEIGHT_32, 1);
    plot_bitmap_32((UINT32 *)base, 439, 359, black, HEIGHT_32, 1);
    plot_bitmap_32((UINT32 *)base, 471, 359, black, HEIGHT_32, 1);
    plot_bitmap_32((UINT32 *)base, 503, 359, black, HEIGHT_32, 1);
    plot_bitmap_32((UINT32 *)base, 535, 359, black, HEIGHT_32, 1);
    plot_bitmap_32((UINT32 *)base, 567, 359, black, HEIGHT_32, 1);
    plot_bitmap_32((UINT32 *)base, 599, 359, white, HEIGHT_32, 1);
    init_obs_wall(&new_game.wall, gap_y());
    while (!new_game.game_state.dead_flag) {
        render_game(&new_game, (UINT32 *)base);
        read_input(&new_game);
        check_score(&new_game); 
        check_conditions(&new_game); 
        move_obstacle(&new_game);
        
        clear_rect((UINT16 *)base, 0, 50, 640, 300); 
        Vsync();
        if (new_game.game_state.dead_flag) {
            printf("Game Over!\n");
        }
    }
    
   /* render_sceen((UINT16 *)base);
    render_game(&new_game, base); */
    return 0;
}


