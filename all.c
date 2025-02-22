#include <stdio.h>
#include <osbind.h>
#include <linea.h>
#include "model.h"
#include "events.h"
#include "raster.h"  
#include "bitmaps.h"

#define SCREEN_WIDTH 680
#define GAP_CENTER 200
#define OBSTACLE_SPEED 3
#define TRUE 1
#define FALSE 0

int main() {
    /* Initialize screen */
    void *base = Physbase();
    linea0();
    disable_cursor();
    clear_screen((UINT16 *)base, 0);

    /* Initialize model (Dino + Obstacle Wall) */
    Model gameModel;
    init_obs_wall(&gameModel.wall, SCREEN_WIDTH, GAP_CENTER);

    /* Main game loop */
    while (TRUE) {
        /* Handle events (e.g., key press for Dino jump) */
        handle_events(&gameModel);

        /* Update model (move obstacles) */
        move_obstacles(&gameModel.wall, OBSTACLE_SPEED);

        /* Render model (draw Dino and obstacles) */
        clear_screen((UINT16 *)base, 0);  
        render_dino(&gameModel.dino, (UINT32 *)base);            
        render_obstacle(&gameModel.wall, (UINT32 *)base);        

        /* Delay (simulate frame rate) */
        for (volatile int delay = 0; delay < 100000; delay++);   
    }

    return 0;
}
