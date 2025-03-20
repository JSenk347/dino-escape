#include "psg.h"
#include <stdio.h>

int main()
{
    Channel A = {0, 1, 8};
    Channel B = {2, 3, 9};
    Channel C = {4, 5, 10};

    /*                g4        c5        e4        d4        D4        c4        C4   */
    Scale scale = {{159, 0}, {119, 0}, {190, 0}, {213, 0}, {201, 0}, {239, 0}, {225, 0}};
    Lvl_up lvl_up = {{159, 0}, {119, 0}, 2};
    Game_Over game_over = {{190, 0}, {201, 0}, {213, 0}, {225, 0}, {239, 0}, 5};

    write_psg(A.fine_reg, scale.g4.fine); /*159*/
    write_psg(A.coarse_reg, scale.g4.coarse); /*0*/

    printf("A Fine Reg: %u\n", read_psg(A.fine_reg)); /*Should print 59*/
    printf("A Coarse Reg: %u\n", read_psg(A.coarse_reg)); /*Should print 0*/

    return 0;
}
