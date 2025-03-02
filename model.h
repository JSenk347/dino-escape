#ifndef MODEL_H
#define MODEL_H

typedef unsigned int bool;
#define TRUE 1
#define FALSE 0
#define HALF_GAP 25
#define T_BORDER_Y 49
#define B_BORDER_Y 352
#define R_BORDER_X 639
#define L_BORDER_X 0
#define DINO_HEIGHT 32

/* STRUCTURE DEFINITIONS */
typedef struct {
    int x, y;
} Vertex;

typedef struct {
    Vertex top_left;
    Vertex top_right;
    Vertex bot_left;
    Vertex bot_right;
    Vertex prev_top_lt;     /* For clearing render when moving the Dino */
    int vert_velocity;
    int vert_direction;
    unsigned int frame_counter;
} Dino;

typedef struct{
    Vertex top_left;
    Vertex top_right;
    Vertex bot_left;
    Vertex bot_right;
    Vertex prev_top_lt;     /* For clearing render when moving the Obs */
} Obs;

typedef struct {
    Obs top;
    Obs bottom;
    bool been_passed;
    unsigned int gap_y;
    unsigned int hor_velocity;
} Obs_wall;

typedef struct
{
    Vertex top_left;
    Vertex top_right;
    Vertex bot_left;
    Vertex bot_right;
    unsigned int value;
} Digit;

typedef struct {
    Vertex top_left;
    Vertex top_right;
    Vertex bot_left;
    Vertex bot_right;
    Digit digits[4];
    unsigned int max_value;
    unsigned int value;
} Score;

typedef struct {
    bool start_flag;
    bool lost_flag;
    bool dead_flag;
} Context;

typedef struct {
    Dino dino;
    Obs_wall wall;
    Score score;
    Context game_state;
} Model;

/* FUNCTION DECLARATIONS */
void move_dino(Dino *dino);
void init_obs_wall(Obs_wall *wall, unsigned int gap_y);
unsigned int gap_y();
void move_obstacles(Model *game);
void reset_obs(Model *game);
void update_score(Model *game);
#endif
