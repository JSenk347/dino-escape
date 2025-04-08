#ifndef INPUT_H
#define INPUT_H

#include "model.h"  /* Include Model definition for access */

void process_input(Model *gameModel, char key);
void start_or_quit(Model *gameModel, char key);
#endif