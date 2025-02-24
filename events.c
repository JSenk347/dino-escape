/*******************************************************************************
 AUTHORS: Anna Running Rabbit, Jordan Senko, Joseph Mills
 COURSE: COMP2659-001
 INSTRUCTOR: Tim Reimer
 DATE: Feb.24, 2025

 SUMMARY: Contains ..... (incomplete)
*******************************************************************************/
#include "events.h"
#include "model.h"

#include <stdio.h>
#include <osbind.h>
#include "events.h"
#include "model.h"

#define SCREEN_WIDTH 680
#define GAP_CENTER   200
#define OBSTACLE_SPEED 3
#define TRUE 1
#define FALSE 0

/* For Cconis() and Cnecin() */
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
void move_obstacle(Model *gameModel) {
    int i;
    finit_obs_wall(&gameModel->wall, SCREEN_WIDTH, GAP_CENTER);
    printf("Initial Obstacle Position (Bottom top-left X): %u\n", gameModel->wall.bottom.top_left.x);
   
    for (i = 0; i < 250; i++) {  /* Move enough times to ensure reset triggers */
        move_obstacles(&gameModel->wall, OBSTACLE_SPEED);
        printf("Step %d - Obstacle Bottom top-right X: %u\n", i + 1, gameModel->wall.bottom.top_right.x);
    
        /* Check if reset occurs after moving off the screen */
        if (gameModel->wall.bottom.top_right.x == SCREEN_WIDTH + OBSTACLE_WIDTH - 1) {
            printf("Obstacle reset to right side at Step %d\n", i + 1);
            i = 250;  
        }
    }
}
/* generate_obs_pos() */

/* check_game_state() */

/* move_dino() */

/* update_dino_sprint() */

/* ASYNCHRONUS EVENTS */

/* CONDITION BASED EVENTS */

void update_score(Model *game){
    int value;

    Score *score = &(game -> game_state.score);
    if (score -> value < score -> max_value){
        (score -> value)++;
        value = score -> value;
        (score -> digits)[0].value = (value / 1000) % 10;
        (score -> digits)[1].value = (value / 100) % 10;
        (score -> digits)[2].value = (value / 10) % 10;
        (score -> digits)[3].value = value % 10;
    }
}

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
