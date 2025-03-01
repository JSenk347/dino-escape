const#ifndef RENDER_H
#define RENDER_H

#include "raster.h"
#include "events.h"
#include "model.h"
#include "bitmaps.h"


void render (const Model *model , UINT32 *base );
void render_sceen(const Model *model , UINT32 *base);
void render_dino(const Model *model , UINT32 *base);
void render_score(const Model *model , UINT32 *base);
void render_start(const Model *model , UINT32 *base);
void render_obs(const Model *model , UINT32 *base);

#endif