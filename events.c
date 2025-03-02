/*******************************************************************************
 AUTHORS:      Anna Running Rabbit, Jordan Senko, Joseph Mills
 COURSE:       COMP2659-001
 INSTRUCTOR:   Tim Reimer
 DATE:         Feb.10, 2025

 FILE:          events.c
 PURPOSE:       
*******************************************************************************/
#include <stdio.h>
#include <osbind.h>
#include <time.h>
#include "events.h"
#include "model.h"

/*******************************************************************************
    PURPOSE: For Cconis() and Cnecin() - Handles user input and calls other
                event-related functions
    INPUT:  - gameModel: pointer to the Model object, aka the current game
                instance
    OUTPUT: N/A
*******************************************************************************/
void handle_events(Model *gameModel) {
    /* 1) Asynchronous key presses */
    read_input(gameModel);

    /* 2) Synchronous (clock/tick) updates
    handle_clock_tick(gameModel);*/

    /* 3) Condition-based checks (collisions, etc.) */
    check_conditions(gameModel);
}

/* SYNCHRONUS EVENTS */
/*******************************************************************************
    PURPOSE: 
    INPUT:  - gameModel: pointer to the Model object, aka the current game
                instance
    OUTPUT: N/A
*******************************************************************************/
void move_obstacle(Model *gameModel) {
    /* Just call the model behavior function each tick */
    move_walls(gameModel);
}

/*******************************************************************************
    PURPOSE: 
    INPUT:  - gameModel: pointer to the Model object, aka the current game

                instance
    OUTPUT: N/A
*******************************************************************************/
void check_conditions(Model *gameModel) {

    Obs *top_obs = &gameModel -> wall.top;
    Obs *bottom_obs = &gameModel -> wall.bottom;
    Dino *d = &gameModel -> dino;
    
    /*Collision with TOP obstacle*/
    if (d -> top_left.x < top_obs -> top_right.x &&
        d -> top_right.x > top_obs -> top_left.x &&
        d -> top_left.y < top_obs -> bot_left.y &&
        d -> bot_left.y > top_obs -> top_left.y) {
            printf("Collision with top obstacle!\n");
            reflect_dino_death(gameModel);
            gameModel -> game_state.dead_flag = TRUE;
            gameModel -> game_state.start_flag = FALSE;
            return;
    }

    /*Collision with BOTTOM obstacle*/
    if (d -> top_left.x < bottom_obs -> top_right.x &&
        d -> top_right.x > bottom_obs -> top_left.x &&
        d -> top_left.y < bottom_obs -> bot_left.y &&
        d -> bot_left.y > bottom_obs -> top_left.y) {
            printf("Collision with bottom obstacle!\n");
            reflect_dino_death(gameModel);
            gameModel -> game_state.dead_flag = TRUE;
            gameModel -> game_state.start_flag = FALSE;
        }
}

/*
void move_walls(Model *game){
    Obs_wall *walls[] = &(game -> walls);

    
}
*/


/* ASYNCHRONUS EVENTS */
/*******************************************************************************
    PURPOSE: 
    INPUT:  - gameModel: pointer to the Model object, aka the current game
                instance
    OUTPUT: N/A
*******************************************************************************/
void wait_for_game_start(Model *gameModel) {
    printf("Press ENTER to start the game...\n");

    init_walls(gameModel);
    printf("WALLS INITIAILIZED\n");

    while (!gameModel -> game_state.start_flag) {
        if (Cconis()) {
            char key = Cnecin();

            if (key == '\r') {
                gameModel -> game_state.start_flag = TRUE;
                printf("Game started by user!\n");
            }
        }
    }
}

/*******************************************************************************
    PURPOSE: 
    INPUT:  - gameModel: pointer to the Model object, aka the current game
                instance
    OUTPUT: N/A
*******************************************************************************/
void read_input(Model *gameModel) {

    if (Cconis()) {
        char key = Cnecin(); 
            while (Cconis()) {
                Cnecin(); 
            }

            if (key == 'w' || key == 's') {
                read_dino_input(gameModel, key);
            }

            if (key == 'q') {
                read_quit_req(gameModel, key);
            }
        } 
}

/*******************************************************************************
    PURPOSE: 
    INPUT:  - gameModel: pointer to the Model object, aka the current game
                instance
            -  
    OUTPUT: N/A
*******************************************************************************/
void read_dino_input(Model *gameModel, char key) {
    /* Moves dino up */
    if (key == 'w') {
        gameModel -> dino.vert_velocity = 5;
        gameModel -> dino.vert_direction = UP;
        move_dino(&gameModel -> dino);
    }
    /* Moves dino down */
    else if (key == 's') {
        gameModel -> dino.vert_velocity = 5;
        gameModel -> dino.vert_direction = DOWN;
        move_dino(&gameModel -> dino);
    }
}

/*******************************************************************************
    PURPOSE: Quits game ... expand
    INPUT:  - gameModel: pointer to the Model object, aka the current game
                instance
            -  
    OUTPUT: N/A
*******************************************************************************/
void read_quit_req(Model *gameModel, char key) {
    if (key == 'q') {
        gameModel -> game_state.dead_flag = TRUE;
        printf("Game ended by user.\n");
    }
}

/* CONDITION BASED EVENTS */

/******************************************************************************************
    PURPOSE: To check whether the dino has passed a barrier or not, and then update the 
             score with update_score(Model *model)
    INPUT:  - game The model of the game
    OUTPUT: N/A
******************************************************************************************/
void check_score(Model *game) {
    Dino *dino = &(game->dino);
    Obs_wall *wall = &(game->wall);

    if ((wall->bottom.bot_right.x < dino->bot_left.x) && !wall->been_passed) {
        update_score(game);
        wall->been_passed = TRUE;
    }
}


/* play_point_sound() */

/*******************************************************************************
    PURPOSE: Reflects the death of the given Model's dino by moving the dino
                down, stopping at the lower border, at double the dino's initial
                velocity.
    INPUT:  - gameModel: pointer to the Model object, aka the current game
                instance 
    OUTPUT: N/A
*******************************************************************************/
void reflect_dino_death(Model *gameModel) {   
    /* Will need to add dino bitmap update to dino_dead_bitmap() */

    /* gameModel -> dino.vert_direction = 1; /* Changes dino direction to down 
    gameModel -> dino.vert_velocity = gameModel -> dino.vert_velocity*2; */

    printf("Dino has died.\n");

    while(gameModel -> dino.bot_left.y < B_BORDER_Y - 1) {
        gameModel -> dino.vert_direction = DOWN;
        gameModel -> dino.vert_velocity = DEAD_VELOCITY;
        move_dino(&gameModel -> dino);
        printf("Top Lt Y: %u | ", gameModel -> dino.top_left.y);
        printf("Top Rt Y: %u | ", gameModel -> dino.top_right.y);
        printf("Bot Lt Y: %u | ", gameModel -> dino.bot_left.y);
        printf("Bot Rt Y: %u\n", gameModel -> dino.bot_right.y);
        /* printf("Dino direction: %u | ", gameModel -> dino.vert_direction);
        printf("Dino velocity: %u\n", gameModel -> dino.vert_velocity); */
    }

    gameModel -> game_state.lost_flag = TRUE;
}