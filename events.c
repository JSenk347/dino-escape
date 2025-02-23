#include "events.h"
#include "model.h"


/* SYNCHRONUS EVENTS */

/* move_obstacles() - Jordan*/

/* generate_obs_pos() */

/* check_game_state() */

/* move_dino() */

/* update_dino_sprint() */

/* ASYNCHRONUS EVENTS */

/* CONDITION BASED EVENTS */

void update_score(Model *game){
    int value;

    Score *score = &(game -> game_state.score);
    if (score -> value < score -> max_value){
        (score -> value)++;
        value = score -> value;
        (score -> digits)[0].value = (value / 1000) % 10;
        (score -> digits)[1].value = (value / 100) % 10;
        (score -> digits)[2].value = (value / 10) % 10;
        (score -> digits)[3].value = value % 10;
    }
}

/* upper_edge_collision() */

/* lower_edge_collision() */

/* left_edge_collision() */

/* roof_collision() */

/* ground_collision() */

/* reflect_dino_death() */

/* update_lost_flag() */

/* update_start_flag() */

/* update_death_flag() */

/* play_point_sound() */
