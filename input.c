/*******************************************************************************
 AUTHORS:      Anna Running Rabbit, Jordan Senko, Joseph Mills
 COURSE:       COMP2659-001
 INSTRUCTOR:   Tim Reimer
 DATE:         Mar.21, 2025

 FILE:         input.c
 PURPOSE:      Holds all input handling functions for the Dino Escape game
*******************************************************************************/
#include "events.h"
#include "model.h"
#include <osbind.h>

/*******************************************************************************
    PURPOSE: To update the given game Model's dino according to the user's 
                input. Pressing 'w' will result in the dino going up, and
                pressing 's' will result in the dino going down.
    INPUT:  - gameModel: pointer to the Model object, aka the current game
                instance
            - key: the character the user has entered.
    OUTPUT: N/A
*******************************************************************************/
void read_dino_input(Model *gameModel, char key) {
    /*Dino dino = gameModel -> dino;*/

    /* Moves dino up */
    if (key == 'w') {
        dino_mvd_up(gameModel);
    }
    /* Moves dino down */
    else if (key == 's') {
        dino_mvd_down(gameModel);
    }
}

/*******************************************************************************
    PURPOSE: To read the user's keyboard input and call the appropriate functions
             such as read_dino_input(Model *gameModel, char key) and 
             read_quit_req(Model *gameModel, char key)
    INPUT:  - gameModel: pointer to the Model object, aka the current game
                instance
    OUTPUT: N/A
*******************************************************************************/
/*void read_input(Model *gameModel) {
    if (Cconis()) {
        char key = (char)Cnecin();
        while (Cconis()) {
            Cnecin();
        }

        if (key == 'w' || key == 's') {
            read_dino_input(gameModel, key);
        }

        if (key == 'q') {
            game_quit(gameModel);
        }
    }
}*/

void process_input(Model *gameModel, char key) {
    /* Moves dino up */
    if (key == 'w') {
        dino_mvd_up(gameModel);
    }
    /* Moves dino down */
    else if (key == 's') {
        dino_mvd_down(gameModel);
    }
    /* Quits game */
    if (key == 'q') {
        game_quit(gameModel);
    }
}