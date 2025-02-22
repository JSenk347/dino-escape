#ifndef MODEL_H
#define MODEL_H

#define SCREEN_WIDTH  680
#define SCREEN_HEIGHT 400
#define HALF_GAP      25
#define TOP_BORDER    50
#define BOTTOM_BORDER 350
#define DINO_HEIGHT   32
#define OBSTACLE_WIDTH 32  /* X dimension of each obstacle rectangle */


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
    unsigned int bool_in_use;
} Digit;

typedef struct {
    Vertex top_left;
    Vertex top_right;
    Vertex bot_left;
    Vertex bot_right;
    unsigned int max_value;
    unsigned int value;
} Score;

typedef struct {
    int start_flag;
    int lost_flag;
    int dead_flag;
    int score;
} Context;

typedef struct {
    Dino dino;
    Obs_wall wall;
    Score score;
} Model;

/* FUNCTION DECLARATIONS */
void init_obs_wall(Obs_wall *wall, unsigned int x, unsigned int gap_y);
void move_obstacles(Obs_wall *wall, int speed);
#endif