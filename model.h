#ifndef MODEL_H
#define MODEL_H

typedef unsigned int bool;
#define TRUE 1
#define FALSE 0

/* STRUCTURE DEFINITIONS */
typedef struct {
    unsigned int x, y;
} Vertex;

typedef struct {
    Vertex top_left;
    Vertex top_right;
    Vertex bot_left;
    Vertex bot_right;
    int vert_velocity;
    int vert_direction;
} Dino;

typedef struct{
    Vertex top_left;
    Vertex top_right;
    Vertex bot_left;
    Vertex bot_right;
} Obs;

typedef struct {
    Obs top;
    Obs bottom;
    unsigned int gap_y;
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
    Score score;
} Context;

typedef struct {
    Dino dino;
    Obs_wall wall;
    Score score;
    Context game_state;
} Model;

/* FUNCTION DECLARATIONS */
void move_dino(Dino *dino, int direction);
void init_obs_wall(Obs_wall *wall, unsigned int gap_y);
unsigned int gap_y();
void move_obstacles(Obs_wall *wall, unsigned int velocity);
#endif