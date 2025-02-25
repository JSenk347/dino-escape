#include <stdio.h>
#include <osbind.h>
#include <time.h>
#include "events.h"
#include "model.h"

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

/* For Cconis() and Cnecin() */
/* Handles user input and calls other event-related functions */
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

void move_obstacle(Model *gameModel)
{
    /* Just call the model behavior function each tick */
    move_obstacles(&gameModel->wall, OBSTACLE_SPEED);
    printf("Obstacle moving... Current X: %u\n", gameModel->wall.bottom.top_left.x);
}

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
        gameModel->game_state.dead_flag = TRUE;
        gameModel->game_state.start_flag = FALSE;
        printf("Collision with top obstacle!\n");
    }

    /*Collision with BOTTOM obstacle*/
    if (d->top_left.x < bottom_obs->top_right.x &&
        d->top_right.x > bottom_obs->top_left.x &&
        d->top_left.y < bottom_obs->bot_left.y &&
        d->bot_left.y > bottom_obs->top_left.y)
    {
        gameModel->game_state.dead_flag = TRUE;
        gameModel->game_state.start_flag = FALSE;
        printf("Collision with bottom obstacle!\n");
    }
}

/* ASYNCHRONUS EVENTS */
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

void read_dino_input(Model *gameModel, char key)
{
    /* Moves dino up */
    if (key == 'w')
    {
        gameModel->dino.vert_velocity = 5;
        gameModel->dino.vert_direction = -1;
        move_dino(&gameModel->dino);
        printf("Dino moved up!\n");
        /* Moves dino down */
    }
    else if (key == 's')
    {
        gameModel->dino.vert_velocity = 5;
        gameModel->dino.vert_direction = 1;
        move_dino(&gameModel->dino);
        printf("Dino moved down!\n");
    }
}

/* Quits game */
void read_quit_req(Model *gameModel, char key)
{
    if (key == 'q')
    {
        gameModel->game_state.lost_flag = TRUE;
        printf("Game ended by user.\n");
    }
}

/* CONDITION BASED EVENTS */
/* point_scored() checks if obs was passed */

/* reflect_dino_death() -updates sprints, lost_flag, calls move_dino to 'fall'*/

/* play_point_sound() */