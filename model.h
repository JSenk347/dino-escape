#ifndef MODEL_H
#define MODEL_H

/* STRUCTURE DEFINITIONS */

typedef struct {
    unsigned int x, y;
} Vertex;

typedef struct {
    unsigned int x, y;
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

typedef struct {
    int start_flag;
    int lost_flag;
    int dead_flag;
    int score;
} Context;

typedef struct {
    Dino dino;
    Obs_wall wall;
} Model;

/* FUNCTION DECLARATIONS */
void move_dino(Dino *dino, int direction);
#endif