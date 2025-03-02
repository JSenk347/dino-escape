#ifndef EVENTS_H
#define EVENTS_H

#include "model.h"  /* Include Model definition for access */

/* Synchronous events */
void move_walls(Model *game);
void check_collisions(Model *gameModel);
/* Asynchronous events */
void wait_for_game_start(Model *gameModel);
void read_input(Model *gameModel);
void read_dino_input(Model *gameModel, char key);
void read_quit_req(Model *gameModel, char key);
/* Condition based events */
void play_point_sound();                /* Placeholder for playing point sound */
void reflect_dino_death(Model *gameModel);
void check_score(Model *game);
void update_score(Model *game);
#endif