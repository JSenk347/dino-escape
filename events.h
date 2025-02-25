#ifndef EVENTS_H
#define EVENTS_H

#include "model.h"  /* Include Model definition for access */
#define SPEED_INCREMENT 1
#define SCORE_THRESHOLD 1000
#define OBSTACLE_SPEED 3

void handle_events(Model *gameModel);  /* Handles user input and synchronous events */
void update_score(Model *gameModel);   /* Placeholder for updating score */
void move_obstacle(Model *gameModel);
void handle_input(Model *gameModel);
void check_conditions(Model *gameModel);
void wait_for_game_start(Model *gameModel);

#endif
