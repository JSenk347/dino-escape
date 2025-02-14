#ifndef MODEL_H
#define MODEL_H

/* STRUCTURE DEFINITIONS */
typedef struct {
    unsigned int x, y;
    int vert_velocity;
    int vert_direction;
    /*dino bitmap?*/
} Dino;

/* FUNCTION DECLARATIONS */
void move_dino(Dino *dino);
#endif