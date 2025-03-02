/*******************************************************************************
 AUTHORS: Anna Running Rabbit, Jordan Senko, Joseph Mills
 COURSE: COMP2659-001
 INSTRUCTOR: Tim Reimer
 DATE: Mar. 2, 2025

 FILE: render.c
 SUMMARY: Contains functions for all rendering game graphics
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

/*******************************************************************************
    PURPOSE: 
    INPUT:	- 
    OUTPUT: 
*******************************************************************************/
void render_game(const Model *model , UINT32 *base){
    render_dino(model, base);
    render_score(model, base);
    render_start(model, base);
}

/*******************************************************************************
    PURPOSE: 
    INPUT:	- 
    OUTPUT: 
*******************************************************************************/
void render_screen(UINT16 *base){
    clear_screen((UINT16 *)base, 0);
}

/*******************************************************************************
    PURPOSE: 
    INPUT:	- 
    OUTPUT: 
*******************************************************************************/
void render_dino(const Model *game, UINT32 *base) {
    UINT32 *bitmap;
    Dino *dino = &(game->dino);
    /* Select new Dino sprite */
    UINT32 *bitmap;
    if (dino->frame_counter % 2 == 0) {
        bitmap = dino_wdown_bitmap; 
        /*overwrite_bitmap_32(base, dino->top_left.x, dino->top_left.y, dino_wup_bitmap, HEIGHT_32);*/ 
    } else {
        bitmap = dino_wup_bitmap;  
        /*overwrite_bitmap_32(base, dino->top_left.x, dino->top_left.y, dino_wdown_bitmap, HEIGHT_32);*/
    }

    /* Draw new Dino frame */
    plot_bitmap_32(base, dino->top_left.x, dino->top_left.y, bitmap, HEIGHT_32, 1); /* 1 = draw mode */

    /* Increment frame counter */
    dino->frame_counter++;
}

/*******************************************************************************
    PURPOSE: 
    INPUT:	- 
    OUTPUT: 
*******************************************************************************/
void clear_inside_borders(UINT32 *base) {
    int top_border_y = 50;    /* Top border position */
    int bottom_border_y = 350; /* Bottom border position */
    int left_border_x = 0;     /* Start at the left edge */
    int right_border_x = 639;  /* End at the right edge (assuming 640px width) */

    /* Clear everything inside the borders */
    clear_rect(base, left_border_x, top_border_y, right_border_x - left_border_x, bottom_border_y - top_border_y);
}

/*******************************************************************************
    PURPOSE: 
    INPUT:	- 
    OUTPUT: 
*******************************************************************************/
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
void render_score(const Model *model , UINT32 *base){}

/*******************************************************************************
    PURPOSE: 
    INPUT:	- 
    OUTPUT: 
*******************************************************************************/
void render_start(const Model *model , UINT32 *base){
    plot_top_start_button((UINT32 *)base, lt_top_start_bitmap, mid_lt_top_start_bitmap, mid_rt_top_start_bitmap, rt_top_start_bitmap);
	plot_bottom_start_button((UINT32 *)base, lt_bottom_start_bitmap, mid_lt_bottom_start_bitmap, mid_rt_bottom_start_bitmap, rt_bottom_start_bitmap);
}

/*******************************************************************************
    PURPOSE: 
    INPUT:	- 
    OUTPUT: 
*******************************************************************************/
void render_obs(const Model *model , UINT32 *base){
    plot_obstacles(base, model->wall.top.top_left.x, model->wall.gap_y);
    /*plot_top_obs(base, model->wall.top.top_left.x, model->wall.gap_y);
    plot_bottom_obs(base, model->wall.bottom.top_left.x, model->wall.gap_y); */
}
