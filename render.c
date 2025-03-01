#include "render.h"
#include "model.h"
/*******************************************************************************
 AUTHORS: Anna Running Rabbit, Jordan Senko, Joseph Mills
 COURSE: COMP2659-001
 INSTRUCTOR: Tim Reimer
 DATE: Feb.24, 2025

 SUMMARY: Contains functions for all rendering game graphics
*******************************************************************************/

void render_game(const Model *model , UINT32 *base){
    render_dino(model, base);
    render_obs(model, base);
    render_score(model, base);
    render_start(model, base);


}
void render_sceen(UINT16 *base){
    clear_screen(base, 0);
    plot_borders();
}
void render_dino(const Model *model , UINT32 *base){}
void render_score(const Model *model , UINT32 *base){}
void render_start(const Model *model , UINT32 *base){
    plot_top_start_button((UINT32 *)base, lt_top_start_bitmap,
			mid_lt_top_start_bitmap, mid_rt_top_start_bitmap,
			rt_top_start_bitmap);
	plot_bottom_start_button((UINT32 *)base, lt_bottom_start_bitmap,
			mid_lt_bottom_start_bitmap, mid_rt_bottom_start_bitmap,
			rt_bottom_start_bitmap);
    return 0;
}
void render_obs(const Model *model , UINT32 *base){}
 