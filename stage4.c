#include "render.h"
#include "events.h"
#include "model.h"
#include "raster.h"
#include "tst_mod.h"
#include "bitmaps.h"
#include <stdio.h>
#include <osbind.h>
#include <linea.h>
int main()
{
    int i;
	void *base = Physbase();
    Model new_game = {
        {{16,184},{47,184},{16,215},{47,215},0,0,0},                    /* Dino variables */
        {{{0,0},{0,0},{0,0},{0,0}}, {{0,0},{0,0},{0,0},{0,0}}, FALSE, 278, OBS_START_SPEED},  /* Obs variables */
        {{505,359},{632,359},{505,390},{632,390},                     /* Score variables */
            {{{505,359},{536,359},{505,390},{536,390},0},
            {{537,359},{568,359},{537,390},{568,390},0},
            {{569,359},{600,359},{568,390},{600,390},0},
            {{601,359},{632,359},{601,390},{632,390},0}},5000,0},
        {0,0,0},                                                            /* Context variables */
    };
    linea0(); 
	disable_cursor();
    render_screen((UINT16 *)base);
    plot_borders();
    init_obs_wall(&new_game.wall, gap_y());
    while (i != 200) {
        read_input(&new_game);
        check_score(&new_game); 
        check_conditions(&new_game); 
        move_obstacle(&new_game);
        i++;
        if (new_game.game_state.dead_flag) {
            printf("Game Over!\n");
        }
    }  
    
    render_screen((UINT16 *)base);

    render_game(&new_game, (UINT32 *)base);
    Cconin();
    return 0;
}


