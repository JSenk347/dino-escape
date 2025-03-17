#ifndef RENDER_H
#define RENDER_H
#define XOR 2

#include "raster.h"
#include "events.h"
#include "model.h"
#include "bitmaps.h"


void init_screen(const Model *game, UINT16 *base);
void render_objs(const Model *model , UINT32 *base);
void render_dino(const Model *game, UINT32 *base);
void render_score(const Model *model , UINT32 *base);
void render_start(const Model *model , UINT32 *base);
void render_obs(const Model *model , UINT32 *base);
void draw_top_lns(Obs *top, int vel);
void draw_bot_lns(Obs *bottom, int vel);
/*void render_obs_2(const Model *model, UINT32 *base);*/
void render_dino_dead(const Model *game, UINT32 *base); 

#endif