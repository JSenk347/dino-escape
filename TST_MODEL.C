/*******************************************************************************
 AUTHORS: Anna Running Rabbit, Jordan Senko, Joseph Mills
 COURSE: COMP2659-001
 INSTRUCTOR: Tim Reimer
 DATE: Feb.10, 2025
*******************************************************************************/
#include "bitmaps.h"
#include "raster.h"
#include "model.h"

#define TRUE 1
#define FALSE 0

int main()
{
    Model init_all = {
        {(16,184),(16,184),(16,184),(16,184),0,0},   /* Dino variables */
        {},                                          /* Obs_wall variables */
        {((311,359),0,TRUE),((343,359),0,FALSE),((375,359),0,FALSE),((407,359),0,FALSE)} /* Score variables */
    }; 
}