#include "render.h"
#include "model.h"
/*******************************************************************************
 AUTHORS: Anna Running Rabbit, Jordan Senko, Joseph Mills
 COURSE: COMP2659-001
 INSTRUCTOR: Tim Reimer
 DATE: Feb.24, 2025

 SUMMARY: Contains functions for all rendering game graphics
*******************************************************************************/

void render(const Model *model , UINT32 *base){
    clear_screen((UINT32 *)base, 0);
    render_sceen(model, base);
    render_dino(model, base);
    render_obs(model, base);
    render_score(model, base);
    render_start(model, base);


}
void render_sceen(const Model *model , UINT32 *base){}
void render_dino(const Model *model , UINT32 *base){}
void render_score(const Model *model , UINT32 *base){}
void render_start(const Model *model , UINT32 *base){}
void render_obs(const Model *model , UINT32 *base){}
