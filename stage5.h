#ifndef RENDER_H
#define RENDER_H

#include "raster.h"
#include "events.h"
#include "model.h"
#include "bitmaps.h"


void render_game(const Model *model , UINT32 *base);
void clear_inside_borders(UINT32 *base);
void render_screen(UINT16 *base);
void render_dino(const Model *game, UINT32 *base);
void render_score(const Model *model , UINT32 *base);
void render_start(const Model *model , UINT32 *base);
void render_obs(const Model *model , UINT32 *base);
void render_dino_dead(const Model *game, UINT32 *base); 

void unrender_obs(const Model *model , UINT32 *base);
void unrender_dino(const Model *game, UINT32 *base);
void unrender_game(const Model *new_game , UINT32 *base);
#endif