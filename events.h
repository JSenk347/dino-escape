#ifndef EVENTS_H
#define EVENTS_H

#include "model.h"  /* Include Model definition for access */
#define SPEED_INCREMENT 1
#define SCORE_THRESHOLD 1000
#define OBSTACLE_SPEED 3

void handle_events(Model *gameModel);  /* Handles user input and synchronous events */
void update_score(Model *gameModel);   /* Placeholder for updating score */
void move_dino(Dino *dino, int direction); /* Moves the Dino */
void move_obstacle(Model *gameModel);

#endif
