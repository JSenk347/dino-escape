#ifndef MODEL_H
#define MODEL_H

/* STRUCTURE DEFINITIONS */
typedef struct {
    unsigned int x, y;
    int vert_velocity;
    int vert_direction;
} Dino;

typedef struct {
    unsigned int upr_x;
    unsigned int upr_y;
    unsigned int lwr_x;
    unsigned int lwr_y;

} Obs;

typedef struct {
    Dino dino;
    Obs obstacle;
} All_models;

/* FUNCTION DECLARATIONS */
void move_dino(Dino *dino, int direction);
#endif