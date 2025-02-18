#ifndef MODEL_H
#define MODEL_H

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
    unsigned int value;
    unsigned int bool_in_use;
} Ones_digit;

typedef struct
{
    Vertex top_left;
    unsigned int value;
    unsigned int bool_in_use;
} Tens_digit;

typedef struct
{
    Vertex top_left;
    unsigned int value;
    unsigned int bool_in_use;
} Hund_digit;

typedef struct
{
    Vertex top_left;
    unsigned int value;
    unsigned int bool_in_use;
} Thous_digit;

typedef struct {
    Ones_digit ones;
    Tens_digit tens;
    Hund_digit hund;
    Thous_digit thous;
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
void move_dino(Dino *dino, int direction);
#endif