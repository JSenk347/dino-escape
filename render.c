#include "render.h"
#include "events.h"
#include "model.h"
#include "raster.h"
#include "tst_mod.h"
#include "bitmaps.h"
#include <stdio.h>
#include <osbind.h>
#include <linea.h>

/*******************************************************************************
 AUTHORS: Anna Running Rabbit, Jordan Senko, Joseph Mills
 COURSE: COMP2659-001
 INSTRUCTOR: Tim Reimer
 DATE: Feb.24, 2025

 SUMMARY: Contains functions for all rendering game graphics
*******************************************************************************/

void render_game(const Model *new_game , UINT32 *base){
    render_obs(new_game,base);
    render_dino(new_game, base);
    /*render_score(new_game,base); */
    plot_bitmap_32((UINT32 )base, 0, 0, black, HEIGHT_32, 1);
}

void render_screen(UINT16 *base){
    disable_cursor();
    clear_screen((UINT16 *)base, 0);
    plot_borders();
    plot_bitmap_32((UINT32 )base, 601, 359, zero_bitmap, HEIGHT_32, 1); /* Ones digit */
    plot_bitmap_32((UINT32)base, 569, 359, zero_bitmap, HEIGHT_32, 1); /* Tens digit */
    plot_bitmap_32((UINT32)base, 537, 359, zero_bitmap, HEIGHT_32, 1); /* Hundreds digit */
    plot_bitmap_32((UINT32)base, 505, 359, zero_bitmap, HEIGHT_32, 1); /* Thousands digit */
}
void render_dino(const Model *game, UINT32 *base) {
    UINT32 *bitmap;
    Dino *dino = &(game->dino);
    
    /* Select new Dino sprite - flaps dino wings */
    UINT32 *bitmap;
    if (dino->frame_counter % 2 == 0) {
        bitmap = dino_wdown_bitmap;
        /*clear_square_32(base, dino -> prev_top_lt.x, dino -> prev_top_lt.y, 0, HEIGHT_32); /* clears previous dino bitmap */ 
        /*overwrite_bitmap_32(base, dino->top_left.x, dino->top_left.y, dino_wup_bitmap, HEIGHT_32);*/ 
    } else {
        bitmap = dino_wup_bitmap;
        /*clear_square_32(base, dino -> prev_top_lt.x, dino -> prev_top_lt.y, 0, HEIGHT_32); /* clears previous dino bitmap */   
        /*overwrite_bitmap_32(base, dino->top_left.x, dino->top_left.y, dino_wdown_bitmap, HEIGHT_32);*/
    }
    /* Draw new Dino frame */
    clear_square_32(base, dino -> prev_top_lt.x, dino -> prev_top_lt.y, 0, HEIGHT_32); /* clears previous dino bitmap */ 
    plot_bitmap_32(base, dino -> top_left.x, dino -> top_left.y, bitmap, HEIGHT_32, 1); /* 1 = draw mode */
    /* Increment frame counter */
    dino->frame_counter++;
}

void render_dino_dead(const Model *game, UINT32 *base) {
    UINT32 *bitmap;
    Dino *dino = &(game->dino);
    bitmap = dino_dead_bitmap;
    plot_bitmap_32((UINT32 *)base, dino->top_left.x, dino->top_left.y, bitmap, HEIGHT_32, 1);
    (dino->frame_counter) += 1;
}
/*******************************************************************************
    PURPOSE: 
    INPUT:	- 
    OUTPUT: 
*******************************************************************************/
void render_score(const Model *model , UINT32 *base) {
    UINT32 *digit_bitmaps[] = {
        zero_bitmap, one_bitmap, two_bitmap, three_bitmap, four_bitmap,
        five_bitmap, six_bitmap, seven_bitmap, eight_bitmap, nine_bitmap
    };
    if (model -> score.value != model -> score.prev_value) {
        /* int ones_digit = model -> score.value % 10;
        /* plot_bitmap_32((UINT32 *)base, 599, 359, digit_bitmaps[ones_digit], HEIGHT_32, 0); */
        int ones_digit = model -> score.digits[0].value;
        int tens_digit = model -> score.digits[1].value;
        int hund_digit = model -> score.digits[2].value;
        int thous_digit = model -> score.digits[3].value;

        /* One's digit */
        clear_square_32(base, model -> score.digits[0].top_left.x, model -> score.digits[0].top_left.y, 1, HEIGHT_32); /* clears previous bitmap */
        plot_bitmap_32((UINT32 *)base, model -> score.digits[0].top_left.x, model -> score.digits[0].top_left.y, digit_bitmaps[ones_digit], HEIGHT_32, 1);

        /* Tens digit */
        clear_square_32(base, model -> score.digits[1].top_left.x, model -> score.digits[1].top_left.y, 1, HEIGHT_32); /* clears previous bitmap */
        plot_bitmap_32((UINT32 *)base, model -> score.digits[1].top_left.x, model -> score.digits[1].top_left.y, digit_bitmaps[tens_digit], HEIGHT_32, 1);

        /* Hundreds digit */
        clear_square_32(base, model -> score.digits[2].top_left.x, model -> score.digits[2].top_left.y, 1, HEIGHT_32); /* clears previous bitmap */
        plot_bitmap_32((UINT32 *)base, model -> score.digits[2].top_left.x, model -> score.digits[2].top_left.y, digit_bitmaps[hund_digit], HEIGHT_32, 1);

        /* Thousands digit */
        clear_square_32(base, model -> score.digits[3].top_left.x, model -> score.digits[3].top_left.y, 1, HEIGHT_32); /* clears previous bitmap */
        plot_bitmap_32((UINT32 *)base, model -> score.digits[3].top_left.x, model -> score.digits[3].top_left.y, digit_bitmaps[thous_digit], HEIGHT_32, 1);
    }
    /* int ones_digit = model -> score.value % 10;
    plot_bitmap_32((UINT32 *)base, 599, 359, digit_bitmaps[ones_digit], HEIGHT_32, 0);
    /*clear_square_32(base, model -> score.digits[0].top_left.x, model -> score.digits[0].top_left.y, 1, HEIGHT_32); /* clears previous one's digit bitmap
    plot_bitmap_32((UINT32 *)base, 599, 359, digit_bitmaps[ones_digit], HEIGHT_32, 1); */
}

/*******************************************************************************
    PURPOSE: 
    INPUT:	- 
    OUTPUT: 
*******************************************************************************/
void render_start(const Model *model , UINT32 *base){
    plot_top_start_button((UINT32 *)base, lt_top_start_bitmap, mid_lt_top_start_bitmap, mid_rt_top_start_bitmap, rt_top_start_bitmap);
	plot_bottom_start_button((UINT32 *)base, lt_bottom_start_bitmap, mid_lt_bottom_start_bitmap, mid_rt_bottom_start_bitmap, rt_bottom_start_bitmap);
}
void render_obs(const Model *model , UINT32 *base){
/* Clears top and bottom obs before plotting new position */
    clear_square_32(base, model -> walls[0].top.prev_top_lt.x, model -> walls[0].top.prev_top_lt.y, 0, HEIGHT_32);
    clear_square_32(base, model -> walls[0].bottom.prev_top_lt.x, model -> walls[0].bottom.prev_top_lt.y, 0, HEIGHT_32); 
    
    plot_bitmap_32(base, model -> walls[0].top.top_left.x, model -> walls[0].top.top_left.y, obs_bottom_edge_bitmap, HEIGHT_32, 1);
    plot_bitmap_32(base, model -> walls[0].bottom.top_left.x, model -> walls[0].bottom.top_left.y, obs_top_edge_bitmap, HEIGHT_32, 1); 

    /* plot_obstacles(base, model->wall.top.top_left.x, model->wall.gap_y);*/
    /*plot_top_obs(base, model->wall.top.top_left.x, model->wall.gap_y);s
    plot_bottom_obs(base, model->wall.bottom.top_left.x, model->wall.gap_y); */
}
