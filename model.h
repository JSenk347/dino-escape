#ifndef MODEL_H
#define MODEL_H

typedef unsigned int bool;
#define TRUE 1
#define FALSE 0
#define DEAD_VELOCITY 2
#define HALF_GAP 25
#define OBS_START_SPEED 2
#define WIN_WIDTH 640
#define T_BORDER_Y 49   /* 0 to 49 = 50 lines */
#define B_BORDER_Y 350  /* 350 to 399 = 50 lines */
#define R_BORDER_X 639
#define L_BORDER_X 0
#define DINO_HEIGHT 32
#define LVL_THRESHOLD 50
#define NUM_WALLS 3
#define UP -1
#define DOWN 1

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
    bool is_moving;
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
    Digit digits[4];
    unsigned int max_value;
    unsigned int value;
    unsigned int prev_value;
} Score;

typedef struct {
    bool start_flag;
    bool lost_flag;
    bool dead_flag;
} Context;

typedef struct {
    Dino dino;
    Obs_wall walls[3];
    Score score;
    Context game_state;
} Model;

/* FUNCTION DECLARATIONS */
void move_dino(Dino *dino);
void init_wall(Obs_wall *wall, int gap);
unsigned int gap_y();
void reset_wall(Model *game, Obs_wall *wall);
#endif
