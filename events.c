#include <stdio.h>
#include <osbind.h>
#include "events.h"
#include "model.h"

void wait_for_game_start(Model *gameModel) {
    printf("Press ENTER to start the game...\n");

    while (!gameModel->game_state.start_flag) {
        if (Cconis()) {                  // Check if a key is pressed
            char key = Cnecin();         // Read the pressed key

            if (key == '\r') {           // '\r' corresponds to the Enter key
                gameModel->game_state.start_flag = TRUE;
                printf("Game started by user!\n");  // ✅ Message printed when Enter is pressed
            }
        }
    }
}

/* For Cconis() and Cnecin() */
/* Handles user input and calls other event-related functions */
void handle_events(Model *gameModel)
{
    /* 1) Asynchronous key presses */
    handle_input(gameModel);

    /* 2) Synchronous (clock/tick) updates */
    handle_clock_tick(gameModel);

    /* 3) Condition-based checks (collisions, etc.) */
    check_conditions(gameModel);
}

void handle_input(Model *gameModel) {
    if (Cconis()) {                   
        char key = Cnecin();          

        if (key == 'w') {             
            gameModel->dino.vert_velocity = 5;
            gameModel->dino.vert_direction = -1;
            move_dino(&gameModel->dino);
            printf("Dino moved up!\n");

        } else if (key == 's') {      
            gameModel->dino.vert_velocity = 5;
            gameModel->dino.vert_direction = 1;
            move_dino(&gameModel->dino);
            printf("Dino moved down!\n");

        } else if (key == 'q') {      
            gameModel->game_state.start_flag = FALSE;
            printf("Game ended by user.\n");
        }
    }
}


/* SYNCHRONUS EVENTS */

void move_obstacle(Model gameModel) {
    move_obstacles(&gameModel, OBSTACLE_SPEED); 
    printf("Obstacle at X: %u\n", gameModel->wall.bottom.top_left.x);
}


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
