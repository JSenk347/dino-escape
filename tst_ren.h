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
    UINT32 *front_buffer = Physbase();  /* Current screen buffer */
    UINT32 *back_buffer = Logbase();    /* Off-screen buffer */
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
    plot_bitmap_32((UINT32 *)base, 599, 359, nine_bitmap, HEIGHT_32, 1);
    render_start(&new_game, (UINT32 *)base);
    wait_for_game_start(&new_game);
    /* Render the initial screen */
    render_screen((UINT16 *)front_buffer); /* Clear screen */
    plot_borders(); /* Draw borders */


    
    /* Draw the initial numbers */
    plot_bitmap_32((UINT32 *)front_buffer, 311, 359, zero_bitmap, HEIGHT_32, 1);
    plot_bitmap_32((UINT32 *)front_buffer, 343, 359, one_bitmap, HEIGHT_32, 1);
    plot_bitmap_32((UINT32 *)front_buffer, 375, 359, two_bitmap, HEIGHT_32, 1);
    plot_bitmap_32((UINT32 *)front_buffer, 407, 359, three_bitmap, HEIGHT_32, 1);
    plot_bitmap_32((UINT32 *)front_buffer, 439, 359, four_bitmap, HEIGHT_32, 1);
    plot_bitmap_32((UINT32 *)front_buffer, 471, 359, five_bitmap, HEIGHT_32, 1);
    plot_bitmap_32((UINT32 *)front_buffer, 503, 359, six_bitmap, HEIGHT_32, 1);
    plot_bitmap_32((UINT32 *)front_buffer, 535, 359, seven_bitmap, HEIGHT_32, 1);
    plot_bitmap_32((UINT32 *)front_buffer, 567, 359, eight_bitmap, HEIGHT_32, 1);
    plot_bitmap_32((UINT32 *)front_buffer, 599, 359, nine_bitmap, HEIGHT_32, 1);
    /* Initialize obstacles */
    init_obs_wall(&new_game.wall, gap_y());


    render_screen((UINT16 *)front_buffer); /* Clear screen */
    plot_borders(); /* Draw borders */

    /* Draw initial numbers */
    plot_bitmap_32((UINT32 *)front_buffer, 311, 359, zero_bitmap, HEIGHT_32, 1);
    plot_bitmap_32((UINT32 *)front_buffer, 343, 359, one_bitmap, HEIGHT_32, 1);
    plot_bitmap_32((UINT32 *)front_buffer, 375, 359, two_bitmap, HEIGHT_32, 1);
    plot_bitmap_32((UINT32 *)front_buffer, 407, 359, three_bitmap, HEIGHT_32, 1);
    plot_bitmap_32((UINT32 *)front_buffer, 439, 359, four_bitmap, HEIGHT_32, 1);
    plot_bitmap_32((UINT32 *)front_buffer, 471, 359, five_bitmap, HEIGHT_32, 1);
    plot_bitmap_32((UINT32 *)front_buffer, 503, 359, zero_bitmap HEIGHT_32, 1);
    plot_bitmap_32((UINT32 *)front_buffer, 535, 359, zero_bitmap HEIGHT_32, 1);
    plot_bitmap_32((UINT32 *)front_buffer, 567, 359, zero_bitmap, HEIGHT_32, 1);
    plot_bitmap_32((UINT32 *)front_buffer, 599, 359, zero_bitmap, HEIGHT_32, 1);

    /* Initialize obstacles */
    init_obs_wall(&new_game.wall, gap_y());

    while (!new_game.game_state.dead_flag) {
        /* Safely get the back buffer */
        back_buffer = Logbase();
        if (back_buffer == NULL) {
            printf("Error: Logbase() returned NULL!\n");
            break; /* Prevent crash */
        }

        /* Clear only the inside borders */
        clear_inside_borders((UINT32 *)back_buffer);
    /* clear_inside_borders((UINT32 *)back_buffer); */
        /* Read input & update game state */
        read_input(&new_game);
        render_dino(&new_game, (UINT32 *)back_buffer);
        check_score(&new_game); 
        render_score(&new_game, (UINT32 *)back_buffer);
        check_conditions(&new_game); 
        move_obstacle(&new_game);
        render_obs(&new_game, (UINT32 *)back_buffer);

        /* Wait for Vsync AFTER rendering */
        Vsync();
    }
    if(new_game.game.score)

   /* render_sceen((UINT16 *)base);
    render_game(&new_game, base); */
    return 0;
}
