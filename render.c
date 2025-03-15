/*******************************************************************************
 AUTHORS: Anna Running Rabbit, Jordan Senko, Joseph Mills
 COURSE: COMP2659-001
 INSTRUCTOR: Tim Reimer
 DATE: Mar.2, 2025

 FILE: render.c
 SUMMARY: Contains functions for all rendering game graphics
*******************************************************************************/
#include "render.h"
#include "events.h"
#include "model.h"
#include "raster.h"
#include "tst_mod.h"
#include "bitmaps.h"
#include "clock.h"
#include <stdio.h>
#include <osbind.h>
#include <linea.h>

/*******************************************************************************
    PURPOSE: Calls the functions to set up for the start of the game, render the
                basic screen, score and borders
    INPUT:  - base: 16 bit base address of the screen
    OUTPUT: - N/A
*******************************************************************************/
void init_screen(const Model *game, UINT16 *base)
{
    int i;

    Digit *digits = game->score.digits;

    disable_cursor();
    clear_screen((UINT16 *)base, 0);
    plot_borders();

    /* Plots the initial score '0000' */
    for (i = 0; i < 4; i++)
    {
        plot_bitmap_32((UINT32 *)base, digits[i].top_left.x, digits[i].top_left.y, zero_bitmap, HEIGHT_32);
    }
}

/*******************************************************************************
    PURPOSE: Calls the functions to render the dino, the obstacles, and the
                score in the game 
    INPUT:	- model: Game model
            - base: Base address of the screen
    OUTPUT: - N/A
*******************************************************************************/
void render_objs(const Model *new_game, UINT32 *base, bool pnt_earned, bool dino_dead)
{
    if (dino_dead)
    {
        if (new_game->dino.bot_left.y < (B_BORDER_Y - 1))
        {
            render_dino_dead(new_game, (UINT32 *)base);
        }
    }
    else
    {
        render_obs(new_game, base);
        render_dino(new_game, base);
        if (pnt_earned)
        {
            render_score(new_game, (UINT32 *)base);
        }
    }
}

/*******************************************************************************
    PURPOSE: Calls the functions to render the obstacles in the game
    INPUT:	- model: Game model
            - base: Base address of the screen
    OUTPUT: - N/A
*******************************************************************************/
void render_dino(const Model *game, UINT32 *base)
{
    UINT32 *bitmap;
    Dino *dino = &(game->dino);

    /* Select new Dino sprite - flaps dino wings */
    UINT32 *bitmap;
    if ((get_time() / 10) % 2 == 0)
    {
        bitmap = dino_wdown_bitmap;
        /*clear_square_32(base, dino -> prev_top_lt.x, dino -> prev_top_lt.y, 0, HEIGHT_32); /* clears previous dino bitmap */
        /*overwrite_bitmap_32(base, dino->top_left.x, dino->top_left.y, dino_wup_bitmap, HEIGHT_32);*/
    }
    else
    {
        bitmap = dino_wup_bitmap;
        /*clear_square_32(base, dino -> prev_top_lt.x, dino -> prev_top_lt.y, 0, HEIGHT_32); /* clears previous dino bitmap */
        /*overwrite_bitmap_32(base, dino->top_left.x, dino->top_left.y, dino_wdown_bitmap, HEIGHT_32);*/
    }
    /* Draw new Dino frame */
    clear_region(base, dino->prev_top_lt.x, dino->prev_top_lt.y, 0x00000000);       /* clears previous dino bitmap */
    plot_bitmap_32(base, dino->top_left.x, dino->top_left.y, bitmap, HEIGHT_32); /* 1 = draw mode */
    /* Increment frame counter */
}

/*******************************************************************************
    PURPOSE: Calls the functions to render the dead dino in the game over screen
    INPUT:	- model: Game model
            - base: Base address of the screen
    OUTPUT: - N/A
*******************************************************************************/
void render_dino_dead(const Model *game, UINT32 *base)
{
    UINT32 *bitmap;
    Dino *dino = &(game->dino);
    bitmap = dino_dead_bitmap;
    clear_region(base, dino->prev_top_lt.x, dino->prev_top_lt.y, 0x00000000);
    plot_bitmap_32(base, dino->top_left.x, dino->top_left.y, bitmap, HEIGHT_32);
}

/*******************************************************************************
    PURPOSE: Renders the current game score of the given game model
    INPUT:	- model: Game model
            - base: Base address of the screen
    OUTPUT: - N/A
*******************************************************************************/
void render_score(const Model *model, UINT32 *base)
{
    int i;
    int dig_index;

    Digit *digits = model->score.digits;
    UINT32 *digit_bitmaps[] = {
        zero_bitmap, one_bitmap, two_bitmap, three_bitmap, four_bitmap,
        five_bitmap, six_bitmap, seven_bitmap, eight_bitmap, nine_bitmap};

    for (i = 0; i < 4; i++)
    {
        dig_index = digits[i].value;

        /*clear_square_32((UINT32 *)base, digits[i].top_left.x, digits[i].top_left.y, 1, HEIGHT_32); /* clears previous bitmap */
        clear_region(base, digits[i].top_left.x, digits[i].top_left.y, 0x00000000); /* clears previous digit bitmap */
        plot_bitmap_32((UINT32 *)base, digits[i].top_left.x, digits[i].top_left.y, digit_bitmaps[dig_index], HEIGHT_32);
    }
}

/*******************************************************************************
    PURPOSE: Calls the functions to render the start screen
    INPUT:	- model: Game model
            - base: Base address of the screen
    OUTPUT: - N/A
*******************************************************************************/
void render_start(const Model *model, UINT32 *base)
{
    plot_top_start_button((UINT32 *)base, lt_top_start_bitmap, mid_lt_top_start_bitmap, mid_rt_top_start_bitmap, rt_top_start_bitmap);
    plot_bottom_start_button((UINT32 *)base, lt_bottom_start_bitmap, mid_lt_bottom_start_bitmap, mid_rt_bottom_start_bitmap, rt_bottom_start_bitmap);
}

/*******************************************************************************
    PURPOSE: To render the obstacles on the screen in acordance to the model
    INPUT:	- model: Game model
            - base: Base address of the screen
    OUTPUT: - N/A
*******************************************************************************/
void render_obs(const Model *model, UINT32 *base)
{
    int i;
    int vel;
    int h_vel;

    for (i = 0; i < NUM_WALLS; i++)
    {
        Obs_wall *wall = &model->walls[i];

        if (wall->is_moving && wall->top.top_right.x < R_BORDER_X)
        {
            Obs *top = &wall->top;
            Obs *bottom = &wall->bottom;
            vel = wall->hor_velocity;
            h_vel = vel / 2;

            /* Plot new lines - TOP */
            plot_gline(top->top_left.x, T_BORDER_Y + 1, top->top_left.x, (top->bot_left.y) - 31, XOR);                        /*      ->||    ||       */
            plot_gline((top->top_left.x) + h_vel, T_BORDER_Y + 1, (top->top_left.x) + h_vel, (top->bot_left.y) - 31, XOR);    /*        ||<-  ||       */
            plot_gline(top->top_right.x, T_BORDER_Y + 1, top->top_right.x, (top->bot_right.y) - 31, XOR);                     /*        ||    ||<-     */
            plot_gline((top->top_right.x) - h_vel, T_BORDER_Y + 1, (top->top_right.x) - h_vel, (top->bot_right.y) - 31, XOR); /*        ||  ->||       */
            /* Clear old lines - TOP */
            plot_gline((top->top_left.x) + vel, T_BORDER_Y + 1, (top->top_left.x) + vel, (top->bot_left.y) - 31, XOR);                 /*   NEW  ||    ||OLD->||    ||    */
            plot_gline((top->top_left.x) + vel + h_vel, T_BORDER_Y + 1, (top->top_left.x) + vel + h_vel, (top->bot_left.y) - 31, XOR); /*        ||    ||     ||<-  ||    */
            plot_gline((top->top_right.x) + vel, T_BORDER_Y + 1, (top->top_right.x) + vel, (top->bot_right.y) - 31, XOR);              /*        ||    ||     ||    ||<-  */
            plot_gline((top->top_right.x) + h_vel, T_BORDER_Y + 1, (top->top_right.x) + h_vel, (top->bot_right.y) - 31, XOR);          /*        ||    ||     ||  ->||    */

            clear_region(base, top->bot_left.x + vel, (top->bot_left.y) - 31, 0x00000000);
            plot_bitmap_32(base, top->bot_left.x, (top->bot_left.y) - 31, obs_bottom_edge_bitmap, HEIGHT_32);

            /*Plot new lines - BOTTOM */
            plot_gline(bottom->top_left.x, (bottom->top_left.y) + 31, bottom->top_left.x, B_BORDER_Y - 2, XOR);
            plot_gline((bottom->top_left.x) + h_vel, (bottom->top_left.y) + 31, (bottom->top_left.x) + h_vel, B_BORDER_Y - 2, XOR);
            plot_gline(bottom->top_right.x, (bottom->top_right.y) + 31, bottom->top_right.x, B_BORDER_Y - 2, XOR);
            plot_gline((bottom->top_right.x) - h_vel, (bottom->top_right.y) + 31, (bottom->top_right.x) - h_vel, B_BORDER_Y - 2, XOR);
            /* Clear old lines - BOTTOM */
            plot_gline((bottom->top_left.x) + vel, (bottom->top_left.y) + 31, (bottom->top_left.x) + vel, B_BORDER_Y - 2, XOR);
            plot_gline((bottom->top_left.x) + vel + h_vel, (bottom->top_left.y) + 31, (bottom->top_left.x) + vel + h_vel, B_BORDER_Y - 2, XOR);
            plot_gline((bottom->top_right.x) + vel, (bottom->top_right.y) + 31, (bottom->top_right.x) + vel, B_BORDER_Y - 2, XOR);
            plot_gline((bottom->top_right.x) + h_vel, (bottom->top_right.y) + 31, (bottom->top_right.x) + h_vel, B_BORDER_Y - 2, XOR);

            clear_region(base, bottom->top_left.x + vel, bottom->top_left.y, 0x00000000);
            plot_bitmap_32(base, bottom->top_left.x, bottom->top_left.y, obs_top_edge_bitmap, HEIGHT_32);

            if (top->top_right.x == R_BORDER_X - 2 || top->top_right.x == R_BORDER_X - 1)
            {
                /* Cancels out the lines that are supposed to cancel out old lines on the first plot, since there are no old lines on the first plot */
                plot_gline((top->top_left.x) + vel, T_BORDER_Y + 1, (top->top_left.x) + vel, (top->bot_left.y) - 31, XOR);                 
                plot_gline((top->top_left.x) + vel + h_vel, T_BORDER_Y + 1, (top->top_left.x) + vel + h_vel, (top->bot_left.y) - 31, XOR); 
                plot_gline((top->top_right.x) + vel, T_BORDER_Y + 1, (top->top_right.x) + vel, (top->bot_right.y) - 31, XOR);              
                plot_gline((top->top_right.x) + h_vel, T_BORDER_Y + 1, (top->top_right.x) + h_vel, (top->bot_right.y) - 31, XOR); 

                plot_gline((bottom->top_left.x) + vel, (bottom->top_left.y) + 31, (bottom->top_left.x) + vel, B_BORDER_Y - 2, XOR);
                plot_gline((bottom->top_left.x) + vel + h_vel, (bottom->top_left.y) + 31, (bottom->top_left.x) + vel + h_vel, B_BORDER_Y - 2, XOR);
                plot_gline((bottom->top_right.x) + vel, (bottom->top_right.y) + 31, (bottom->top_right.x) + vel, B_BORDER_Y - 2, XOR);
                plot_gline((bottom->top_right.x) + h_vel, (bottom->top_right.y) + 31, (bottom->top_right.x) + h_vel, B_BORDER_Y - 2, XOR);
            }
        }
    }
}

void render_obs_2(const Model *model, UINT32 *base)
{
    int i;
    int k;

    for (i = 0; i < NUM_WALLS; i++)
    {
        Obs_wall *wall = &model->walls[i];

        if (wall->is_moving && wall->top.top_right.x < R_BORDER_X)
        {
            Obs *top = &wall->top;
            Obs *bottom = &wall->bottom;

            for (k = (T_BORDER_Y + 1); k < (top->bot_left.y - 40); k += 16)
            {
                clear_region(base, bottom->top_left.x + 2, k, 0x00000000);
                plot_bitmap_32(base, bottom->top_left.x, k, obs_bitmap, HEIGHT_32);
            }

            clear_region(base, top->bot_left.x + 2, (top->bot_left.y) - 31, 0x00000000);
            plot_bitmap_32(base, top->bot_left.x, (top->bot_left.y) - 31, obs_bottom_edge_bitmap, HEIGHT_32);

            for (k = (B_BORDER_Y - 1); k > (bottom->top_left.y + 32); k -= 16)
            {
                clear_region(base, bottom->top_left.x + 2, k, 0x00000000);
                plot_bitmap_32(base, bottom->top_left.x, k, obs_bitmap, HEIGHT_32);
            }

            clear_region(base, bottom->top_left.x + 2, bottom->top_left.y, 0x00000000);
            plot_bitmap_32(base, bottom->top_left.x, bottom->top_left.y, obs_top_edge_bitmap, HEIGHT_32);
        }
    }
}

/*******************************************************************************
    PURPOSE: Renders the current game score of the given game model
    INPUT:	- model: Game model
            - base: Base address of the screen
    OUTPUT: - N/A
*******************************************************************************/