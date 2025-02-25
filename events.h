#ifndef EVENTS_H
#define EVENTS_H

#include "model.h"  /* Include Model definition for access */
#define SPEED_INCREMENT 1
#define SCORE_THRESHOLD 1000
#define OBSTACLE_SPEED 3

void wait_for_game_start(Model *gameModel);
void handle_events(Model *gameModel);  /* Handles user input and synchronous events */
void move_obstacle(Model *gameModel);
void check_conditions(Model *gameModel);
void update_score(Model *gameModel);   /* Placeholder for updating score */
void read_input(Model *gameModel);
void read_dino_input(Model *gameModel, char key);
void read_quit_req(Model *gameModel, char key);

#endif