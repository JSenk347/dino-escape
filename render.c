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
    render_dino(new_game, base);
    render_obs(new_game,base);
    render_score(new_game,base);
}

void render_screen(UINT16 *base){
    clear_screen((UINT16 *)base, 0);
    plot_borders();
    plot_bitmap_32((UINT32 *)base, 503, 359, black, HEIGHT_32, 1);
    plot_bitmap_32((UINT32 *)base, 535, 359, black, HEIGHT_32, 1);
    plot_bitmap_32((UINT32 *)base, 567, 359, black, HEIGHT_32, 1);
}
void render_dino(const Model *game, UINT32 *base) {
    UINT32 *bitmap;
    Dino *dino = &(game->dino);
    /* Select new Dino sprite */
    UINT32 *bitmap;
    if (dino->frame_counter % 2 == 0) {
        bitmap = dino_wdown_bitmap; 
    } else {
        bitmap = dino_wup_bitmap;  
    }
    /* Draw new Dino frame */
    plot_bitmap_32(base, dino->top_left.x, dino->top_left.y, bitmap, HEIGHT_32, 1); /* 1 = draw mode */
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
void render_score(const Model *model , UINT32 *base){
    UINT32 *digit_bitmaps[] = {
        zero_bitmap, one_bitmap, two_bitmap, three_bitmap, four_bitmap,
        five_bitmap, six_bitmap, seven_bitmap, eight_bitmap, nine_bitmap
    };
        int ones_digit = model->score.value % 10;
        /*plot_bitmap_32((UINT32 *)base, 599, 359, empty_bitmap, HEIGHT_32, 0);*/
        plot_bitmap_32((UINT32 *)base, 599, 359, digit_bitmaps[ones_digit], HEIGHT_32, 1);
    }
void render_start(const Model *model , UINT32 *base){
    plot_top_start_button((UINT32 *)base, lt_top_start_bitmap, mid_lt_top_start_bitmap, mid_rt_top_start_bitmap, rt_top_start_bitmap);
	plot_bottom_start_button((UINT32 *)base, lt_bottom_start_bitmap, mid_lt_bottom_start_bitmap, mid_rt_bottom_start_bitmap, rt_bottom_start_bitmap);
}
void render_obs(const Model *model , UINT32 *base){
    plot_obstacles(base, model->wall.top.top_left.x, model->wall.gap_y, 1);
    /*plot_top_obs(base, model->wall.top.top_left.x, model->wall.gap_y);
    plot_bottom_obs(base, model->wall.bottom.top_left.x, model->wall.gap_y); */
}
