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
        {{16,184},{47,184},{16,215},{47,215},0,0}, /* Dino variables */
          { 
              {{{640,50},{672,50},{640,200},{672,200}}, {{640,251},{672,251},{640,351},{672,351}}, TRUE, FALSE, 200, OBS_START_SPEED}, /* wall 1 */
              {{{640,50},{672,50},{640,200},{672,200}}, {{640,251},{672,251},{640,351},{672,351}}, FALSE, FALSE, 200, OBS_START_SPEED}, /* wall 2 */
              {{{640,50},{672,50},{640,200},{672,200}}, {{640,251},{672,251},{640,351},{672,351}}, FALSE, FALSE, 200, OBS_START_SPEED}, /* wall 3 */
          }, 
          {{505,359},{632,359},{505,390},{632,390}, 
              {{{505,359},{536,359},{505,390},{536,390},0},
              {{537,359},{568,359},{537,390},{568,390},0},
              {{569,359},{600,359},{568,390},{600,390},0},
              {{601,359},{632,359},{601,390},{632,390},0}},5000,0},
        {FALSE,FALSE,FALSE},                                                                        /* Context variables */
      }; 
    linea0();
    while (i != 250) { /* Find a random position during the game to show what it will look like when played */
        move_walls(&new_game); /* Happens first to prevent obstacle from moving after collision has occured */
        read_input(&new_game); /* Read user input */
        check_collisions(&new_game); /* */
        check_score(&new_game); 
        i++;

        if (new_game.game_state.dead_flag) {
            printf("Game Over!\n");
        }
    } 
    /* Render outside of while loop so just one frame is rendered*/
    init_screen(&new_game, (UINT16 *)base);
    render_game(&new_game, (UINT32 *)base);
    return 0;
}


