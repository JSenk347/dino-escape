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
void handle_events(Model *gameModel)
{
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
void move_obstacle(Model *gameModel)
{
    /* Just call the model behavior function each tick */
    move_obstacles(gameModel);
    printf("Obstacle moving... Current X: %u\n", gameModel->wall.bottom.top_left.x);
}

/*******************************************************************************
    PURPOSE: 
    INPUT:  - gameModel: pointer to the Model object, aka the current game
                instance
    OUTPUT: N/A
*******************************************************************************/
void check_conditions(Model *gameModel)
{
    Obs *top_obs = &gameModel->wall.top;
    Obs *bottom_obs = &gameModel->wall.bottom;
    Dino *d = &gameModel->dino;

    /*Collision with TOP obstacle*/
    if (d->top_left.x < top_obs->top_right.x &&
        d->top_right.x > top_obs->top_left.x &&
        d->top_left.y < top_obs->bot_left.y &&
        d->bot_left.y > top_obs->top_left.y)
    {
        reflect_dino_death(gameModel);
        gameModel->game_state.lost_flag = TRUE;
        gameModel->game_state.start_flag = FALSE;
        printf("Collision with top obstacle!\n");
    }

    /*Collision with BOTTOM obstacle*/
    if (d->top_left.x < bottom_obs->top_right.x &&
        d->top_right.x > bottom_obs->top_left.x &&
        d->top_left.y < bottom_obs->bot_left.y &&
        d->bot_left.y > bottom_obs->top_left.y)
    {
        reflect_dino_death(gameModel);
        gameModel->game_state.lost_flag = TRUE;
        gameModel->game_state.start_flag = FALSE;
        printf("Collision with bottom obstacle!\n");
    }
}

/* ASYNCHRONUS EVENTS */
/*******************************************************************************
    PURPOSE: 
    INPUT:  - gameModel: pointer to the Model object, aka the current game
                instance
    OUTPUT: N/A
*******************************************************************************/
void wait_for_game_start(Model *gameModel)
{
    printf("Press ENTER to start the game...\n");

    while (!gameModel->game_state.start_flag)
    {
        if (Cconis())
        {
            char key = Cnecin();

            if (key == '\r')
            {
                gameModel->game_state.start_flag = TRUE;
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
void read_input(Model *gameModel)
{
    if (Cconis())
    {
        char key = Cnecin();
        /* Moves dino */
        if (key == 'w' || key == 's')
        {
            read_dino_input(gameModel,key);
        }
        /* Quits game */
        if (key == 'q')
        {
            read_quit_req(gameModel,key);
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
void read_dino_input(Model *gameModel, char key)
{
    /* Moves dino up */
    if (key == 'w')
    {
        gameModel->dino.vert_velocity = 5;
        gameModel->dino.vert_direction = -1; /* Changes dino direction to up */
        move_dino(&gameModel->dino);
        printf("Dino moved up!\n");
    }
    /* Moves dino down */
    else if (key == 's')
    {
        gameModel->dino.vert_velocity = 5;
        gameModel->dino.vert_direction = 1; /* Changes dino direction to down */
        move_dino(&gameModel->dino);
        printf("Dino moved down!\n");
    }
}

/*******************************************************************************
    PURPOSE: Quits game ... expand
    INPUT:  - gameModel: pointer to the Model object, aka the current game
                instance
            -  
    OUTPUT: N/A
*******************************************************************************/
void read_quit_req(Model *gameModel, char key)
{
    if (key == 'q')
    {
        gameModel->game_state.lost_flag = TRUE;
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
void check_score(Model *game){
    Dino *dino = &(game -> dino);
    Obs_wall *wall = &(game -> wall);

    if ((dino -> bot_left.x > wall -> bottom.top_right.x)  && (wall -> been_passed == FALSE)){
        update_score(game);
        wall -> been_passed = TRUE;
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
void reflect_dino_death(Model *gameModel)
{   
    /* Will need to add dino bitmap update to dino_dead_bitmap() */

    gameModel->dino.vert_direction = 1; /* Changes dino direction to down */
    gameModel->dino.vert_velocity = gameModel->dino.vert_velocity*2;
    move_dino(&gameModel->dino);
}