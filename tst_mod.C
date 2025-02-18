/*******************************************************************************
 AUTHORS: Anna Running Rabbit, Jordan Senko, Joseph Mills
 COURSE: COMP2659-001
 INSTRUCTOR: Tim Reimer
 DATE: Feb.10, 2025
*******************************************************************************/
#include "model.h"
#include "events.h"

#define TRUE 1
#define FALSE 0

int main()
{
    Model init_all = {
        {{16,184},{16,184},{16,184},{16,184},0,0},   /* Dino variables */
        {{{0,0},{0,0},{0,0},{0,0}}, {{0,0},{0,0},{0,0},{0,0}}, 278},  /* Obs_wall variables */
        {{311,359},{407,359},{311,391},{407,391},5000,0} /* Score variables */
    }; 

    return 0;
}