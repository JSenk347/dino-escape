#ifndef EVENTS_H
#define EVENTS_H

#include "model.h"  /* Include Model definition for access */

/* Synchronous events */
void move_walls(Model *game);
void check_collisions(Model *gameModel);
bool check_score(Model *game);
/* Asynchronous events */
void dino_mvd_up(Model *gameModel);
void dino_mvd_down(Model *gameModel);
void game_quit(Model *gameModel);
void wait_for_game_start(Model *gameModel);
/* NOW ALL IN INPUT.C
void read_input(Model *gameModel);              
void read_dino_input(Model *gameModel, char key);
void read_quit_req(Model *gameModel, char key);*/
/* Condition based events */
void play_point_sound();                /* Placeholder for playing point sound */
void reflect_dino_death(Model *gameModel);
bool point_earned(Model *game);
void update_score(Model *game);
#endif