#include "events.h"
#include <osbind.h>  /* For Cconis() and Cnecin() */

/* Handles user input and calls other event-related functions */
void handle_events(Model *gameModel) {
    /* Check for key press (example: 'w' for Dino jump) */
    if (Cconis()) {  /* Cconis() checks if a key is pressed */
        char key = Cnecin();  /* Reads the pressed key */

        if (key == 'w') {  /* Simulate Dino jump */
            gameModel->dino.vert_velocity = -5;
            gameModel->dino.vert_direction = -1;
        }
    }

    /* Simulate gravity (Dino returns down after jump) */
    if (gameModel->dino.vert_velocity < 5) {
        gameModel->dino.vert_velocity += 1;
        gameModel->dino.vert_direction = 1;
    }
    move_dino(&gameModel->dino, gameModel->dino.vert_direction);
}


/* SYNCHRONUS EVENTS */

/* move_obstacles() - Joseph*/

/* generate_obs_pos() */

/* check_game_state() */

/* move_dino() */

/* update_dino_sprint() */

/* ASYNCHRONUS EVENTS */

/* CONDITION BASED EVENTS */

/* update_score() */

/* move_dino() */

/* upper_edge_collision() */

/* lower_edge_collision() */

/* left_edge_collision() */

/* roof_collision() */

/* ground_collision() */

/* reflect_dino_death() */

/* update_lost_flag() */

/* update_start_flag() */

/* update_death_flag() */

/* play_point_sound() */
