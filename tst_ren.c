#include "render.h"
#include "events.h"
#include "model.h"
#include "raster.h"
#include "tst_mod.h"
#include "bitmaps.h"
#include "input.h"
#include <stdio.h>
#include <osbind.h>
#include <linea.h>

int main()
{
    bool pt_scored = FALSE, dino_dead = FALSE;

    int i;
    void *base = Physbase();
    Model new_game = {
        {{16, 184}, {47, 184}, {16, 215}, {47, 215}, {16, 184}, 0, 0, 0}, /* Dino variables */
        {
            {{{640, 50}, {672, 50}, {640, 200}, {672, 200}}, {{640, 251}, {672, 251}, {640, 351}, {672, 351}}, TRUE, FALSE, 200, OBS_START_SPEED},  /* wall 1 */
            {{{640, 50}, {672, 50}, {640, 200}, {672, 200}}, {{640, 251}, {672, 251}, {640, 351}, {672, 351}}, FALSE, FALSE, 200, OBS_START_SPEED}, /* wall 2 */
            {{{640, 50}, {672, 50}, {640, 200}, {672, 200}}, {{640, 251}, {672, 251}, {640, 351}, {672, 351}}, FALSE, FALSE, 200, OBS_START_SPEED}, /* wall 3 */
        },
        {{{{505, 359}, {536, 359}, {505, 390}, {536, 390}, 0},  /* ones digit */
          {{537, 359}, {568, 359}, {537, 390}, {568, 390}, 0},  /* tens digit */
          {{569, 359}, {600, 359}, {568, 390}, {600, 390}, 0},  /* hundreds digit */
          {{601, 359}, {632, 359}, {601, 390}, {632, 390}, 0}}, /* thousands digit */
         5000,                                                  /* max score value */
         0},                                                    /* current score value */
        {FALSE, FALSE, FALSE}, /* Context variables */
    };
    linea0();
    
    
    init_screen(&new_game, (UINT16 *)base);
    
    while (i != 21) {
        pt_scored = check_score(&new_game);
        render_objs(&new_game, (UINT32 *)base, pt_scored, dino_dead);
        dino_dead = new_game.game_state.dead_flag;
        move_walls(&new_game);
        read_input(&new_game);
        check_collisions(&new_game);

        i++;
    }

    Cconin();

    pt_scored = check_score(&new_game);
    render_objs(&new_game, (UINT32 *)base, pt_scored, dino_dead);
    dino_dead = new_game.game_state.dead_flag;
    move_walls(&new_game);
    read_input(&new_game);
    check_collisions(&new_game);

    Cconin();

    pt_scored = check_score(&new_game);
    render_objs(&new_game, (UINT32 *)base, pt_scored, dino_dead);
    dino_dead = new_game.game_state.dead_flag;
    move_walls(&new_game);
    read_input(&new_game);
    check_collisions(&new_game);
    
    

    /* PLAY GAME AS NORMAL CODE BELOW 
    
    init_screen(&new_game, (UINT16 *)base);
    while (new_game.game_state.dead_flag == FALSE && new_game.game_state.lost_flag == FALSE)
    {
        pt_scored = check_score(&new_game);
        render_objs(&new_game, (UINT32 *)base, pt_scored, dino_dead);
        dino_dead = new_game.game_state.dead_flag;
        move_walls(&new_game);
        read_input(&new_game);
        check_collisions(&new_game);
        
        if (pt_scored) {
            render_score(&new_game, (UINT32 *)base);
        } 
        
    }
    while(new_game.dino.bot_left.y < (B_BORDER_Y - 1)){
        render_dino_dead(&new_game, (UINT32 *)base);
        reflect_dino_death(&new_game); 
    }*/
    
    Cconin();

    /* Render outside of while loop so just one frame is rendered*/
    return 0;
}
