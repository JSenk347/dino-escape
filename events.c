/*******************************************************************************
 AUTHORS:      Anna Running Rabbit, Jordan Senko, Joseph Mills
 COURSE:       COMP2659-001
 INSTRUCTOR:   Tim Reimer
 DATE:         Feb.10, 2025

 FILE:         events.c
 PURPOSE:      Holds all synchronous, asynchronous, conditional event functions
*******************************************************************************/
#include <stdio.h>
#include <osbind.h>
#include <time.h>
#include "events.h"
#include "model.h"

/* SYNCHRONUS EVENTS */
/*******************************************************************************
    PURPOSE: Updates the x position of each of the game's walls, moving them
             the left each time.
    INPUT:  - gameModel: pointer to the Model object, aka the current game
                instance
    OUTPUT: N/A
*******************************************************************************/
void move_walls(Model *game)
{
    /* NOT AN ISSUE WITH MOVE WALLS */
    int i;
    unsigned int h_vel;

    Obs_wall *walls = game->walls;
    for (i = 0; i < NUM_WALLS; i++)
    {
        Obs_wall *wall = &walls[i];

        /* Iterates through each wall */
        if (i + 1 < NUM_WALLS)
        {
            Obs_wall *next_wall = &walls[i + 1];
            /* Initializes next wall if not yet moving */
            if (next_wall -> is_moving != TRUE &&
                wall -> bottom.bot_left.x <= WIN_WIDTH - (WIN_WIDTH / NUM_WALLS))
            {
                next_wall -> is_moving = TRUE;
                init_wall(next_wall, gap_y());
            }
        }

        if (wall->is_moving == TRUE)
        {
            Obs *top = &(wall->top);
            Obs *bottom = &(wall->bottom);

            top -> prev_top_lt = top -> top_left;
            bottom -> prev_top_lt = bottom -> top_left;

            if ((bottom->bot_right.x < L_BORDER_X && top->top_right.x < L_BORDER_X) && wall -> been_passed == TRUE)
            {
                reset_wall(game, wall);
            }

            /* Wall only moves if no collision has occured */
            if (!(game -> game_state.dead_flag)) {
                h_vel = wall -> hor_velocity;
            }
            else {
                h_vel = 0;
            }
            /*h_vel = wall->hor_velocity;*/

            bottom->bot_left.x -= h_vel;
            bottom->bot_right.x -= h_vel;
            bottom->top_left.x -= h_vel;
            bottom->top_right.x -= h_vel;

            top->bot_left.x -= h_vel;
            top->bot_right.x -= h_vel;
            top->top_left.x -= h_vel;
            top->top_right.x -= h_vel;
        }
    }
}

/*******************************************************************************
    PURPOSE: Checks to see if the dino has collided with any of the barriers.
             If so, reflect_dino_death(Model *game) will be called to show the
             dino falling to the ground, and the game will then end.
    INPUT:  - gameModel: pointer to the Model object, aka the current game
    OUTPUT: N/A
*******************************************************************************/
void check_collisions(Model *game)
{
    int i;
    Dino *dino = &game->dino;
    Obs_wall *walls = game->walls;

    for (i = 0; i < NUM_WALLS; i++)
    {
        Obs_wall *wall = &walls[i];
        Obs *top = &wall->top;
        Obs *bottom = &wall->bottom;

        /*Collision with TOP obstacle*/
        if (dino->top_left.x + 3 < top->top_right.x &&
            dino->top_right.x + 3 > top->top_left.x &&
            dino->top_left.y < top->bot_left.y &&
            dino->bot_left.y > top->top_left.y)
        {
            /*reflect_dino_death(game);*/ /* COMMENT THIS OUT FOR TESTING */
            game->game_state.dead_flag = TRUE;
            game->game_state.start_flag = FALSE;
            /* Prevents walls from continuing to move after collision */
            /* walls -> hor_velocity = 0;
            walls -> is_moving = FALSE;*/
            return;
        }

        /*Collision with BOTTOM obstacle*/
        if (dino->top_left.x + 3 < bottom->top_right.x &&
            dino->top_right.x + 3 > bottom->top_left.x &&
            dino->top_left.y < bottom->bot_left.y &&
            dino->bot_left.y > bottom->top_left.y)
        {
            /*printf("Collision with bottom obstacle!, WALL %u\n",
            i + 1); */
            /*reflect_dino_death(game);*/
            game->game_state.dead_flag = TRUE;
            game->game_state.start_flag = FALSE;
            /* Prevents walls from continuing to move after collision */
            /*walls -> hor_velocity = 0;
            walls -> is_moving = FALSE;*/
            return;
        }
    }
}

bool fell_on_obs(Model *game){
    int i;

    Obs_wall *walls = game -> walls;
    Dino *dino = &game -> dino;

    for(i = 0; i < NUM_WALLS; i++){
        Obs_wall *wall = &walls[i];
        Obs *bottom = &wall -> bottom;

        if (dino -> bot_left.y >= bottom -> top_left.y &&
        ((dino -> bot_left.x <= bottom -> top_right.x && dino -> bot_left.x >= bottom -> top_left.x)||
        (dino -> bot_right.x >= bottom -> top_left.x && dino -> bot_right.x  <= bottom -> top_right.x)))
        {
            return TRUE;
        }
    }
    
    return FALSE;
}

/*******************************************************************************
    PURPOSE: Checks to see if a new point has been scored in the given game
                Model. If so, update_score(Model *game) will be called to
                increase the game's score value and the pt_scored boolean is
                updated to 'TRUE'.
    INPUT:  - game: pointer to the Model object, aka the current game
    OUTPUT: - pt_scored: boolean representing whether a new point has been
                scored
*******************************************************************************/
bool check_score(Model *game)
{
    bool pt_scored;

    if (point_earned(game))
    {
        update_score(game);
        pt_scored = TRUE;
    }
    else
    {
        pt_scored = FALSE;
    }

    return pt_scored;
}

/* ASYNCHRONUS EVENTS */
/*******************************************************************************
    PURPOSE: To update the given dino's velocity and direction to reflect
                upwards movement
    INPUT:  - dino: pointer to the Dino object, aka the current game
                instances dino character
    OUTPUT: N/A
*******************************************************************************/
void dino_mvd_up(Model *gameModel)
{
    gameModel->dino.vert_velocity = 5;
    gameModel->dino.vert_direction = UP;
    move_dino(&gameModel->dino);
    gameModel->dino.vert_velocity = 0;
    gameModel->dino.vert_direction = 0;
}

/*******************************************************************************
    PURPOSE: To update the given dino's velocity and direction to reflect
                downwards movement
    INPUT:  - dino: pointer to the Dino object, aka the current game
                instances dino character
    OUTPUT: N/A
*******************************************************************************/
void dino_mvd_down(Model *gameModel)
{
    gameModel->dino.vert_velocity = 5;
    gameModel->dino.vert_direction = DOWN;
    move_dino(&gameModel->dino);
    gameModel->dino.vert_velocity = 0;
    gameModel->dino.vert_direction = 0;
}

/*******************************************************************************
    PURPOSE: Updates the game's lost_flag, to trigger the game to stop.
    INPUT:  - gameModel: pointer to the Model object, aka the current game
                instance
    OUTPUT: N/A
*******************************************************************************/
void game_quit(Model *gameModel)
{
    gameModel->game_state.lost_flag = TRUE;
    printf("Game ended by user.\n");
}

/*******************************************************************************
    PURPOSE: Waits for the user to enter "enter" on the keyboard and then updates
             the start_flag to trigger the start of the game.
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
            if (key == 'q')
            {
                gameModel->game_state.lost_flag = FALSE;
                printf("Game not started by user.\n");
                break;
            }
        }
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
/*void read_input(Model *gameModel)
{
    if (Cconis())
    {
        char key = Cnecin();
        while (Cconis())
        {
            Cnecin();
        }

        if (key == 'w' || key == 's')
        {
            read_dino_input(gameModel, key);
        }

        if (key == 'q')
        {
            read_quit_req(gameModel, key);
        }
    }
}*/

/*******************************************************************************
    PURPOSE: To update the direction and velocity of the dino according to the
             user's input. Pressing 'w' will result in the dino going up, and
             pressing 's' will result in the dino going down.
    INPUT:  - gameModel: pointer to the Model object, aka the current game
                instance
            - key: the character the user has entered.
    OUTPUT: N/A
*******************************************************************************/
/*void read_dino_input(Model *gameModel, char key)
{
    /* Moves dino up
    if (key == 'w')
    {
        gameModel->dino.vert_velocity = 5;
        gameModel->dino.vert_direction = UP; /* Changes dino direction to up
        move_dino(&gameModel->dino);
    }
    /* Moves dino down
    else if (key == 's')
    {
        gameModel->dino.vert_velocity = 5;
        gameModel->dino.vert_direction = DOWN;
        move_dino(&gameModel->dino);
      }
}*/

/*******************************************************************************
    PURPOSE: Updates the game's dead_flag, triggereing a sequence of loop ending
             to ensure the game stops.
    INPUT:  - gameModel: pointer to the Model object, aka the current game
                instance
            - key: the key the user has pressed.
    OUTPUT: N/A
*******************************************************************************/
/*void read_quit_req(Model *gameModel, char key)
{
    if (key == 'q')
    {
        gameModel -> game_state.lost_flag = TRUE;
        printf("Game ended by user.\n");

    }
} */

/* CONDITION BASED EVENTS */
/******************************************************************************************
    PURPOSE: To check whether the dino has passed a barrier or not and update the wall's
             been_passed status
    INPUT:  - game: The model of the game
    OUTPUT: - bool: the truth value of whether a point has been gained or not
******************************************************************************************/
bool point_earned(Model *game)
{
    int i;
    Dino *dino = &(game->dino);
    Obs_wall *walls = game->walls;
    for (i = 0; i < NUM_WALLS; i++)
    {
        Obs_wall *wall = &walls[i];

        if ((wall->bottom.bot_right.x < dino->bot_left.x) && !wall->been_passed)
        {
            wall->been_passed = TRUE;
            return TRUE;
        }
    }
    return FALSE;
}

/******************************************************************************************
    PURPOSE: To update both the value of the Score object as well as the value of the
             Digit objects in the Digit array of the Score object.
    INPUT:  - game: The model of the game
    OUTPUT: N/A
******************************************************************************************/
void update_score(Model *game)
{
    int value;

    Score *score = &(game->score);
    score->prev_value = score->value;

    if (score->value < score->max_value)
    {
        (score->value)++;
        value = score->value;
        (score->digits)[0].value = (value / 1000) % 10; /* thousands digit */
        (score->digits)[1].value = (value / 100) % 10;  /* hundreds digit */
        (score->digits)[2].value = (value / 10) % 10;   /* tens digit */
        (score->digits)[3].value = value % 10;          /* ones digit */
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
    /*
     while (gameModel->dino.bot_left.y <= (B_BORDER_Y - 1))
     {*/
    gameModel->dino.vert_velocity = DEAD_VELOCITY;

    if (fell_on_obs(gameModel)){
        gameModel -> dino.vert_direction = 0;
        gameModel->game_state.lost_flag = TRUE;
        
    } else if (gameModel->dino.bot_left.y >= (B_BORDER_Y - 1)){
        gameModel->game_state.lost_flag = TRUE;
    }

    gameModel->dino.vert_direction = DOWN;
    move_dino(&gameModel->dino);
    /*
    if ()
    {
        gameModel->game_state.lost_flag = TRUE;
    }
    */
    
}