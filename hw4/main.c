#include <stdio.h>

#include "player_ops.h"

// //directly implement move_player in main.c
// void move_player(struct Player *p, int dx, int dy){  
//     p -> x += dx;
//     p -> y += dy;
// }

int main(void){
    struct Player the_player = {
        .x = 10, .y = 5, .symbol = '@', .health = 121
    };

    printf("player pos %d, %d\n", the_player.x, the_player.y);

    move_player(&the_player, +3, -1);

    printf("new play pos %d, %d\n", the_player.x, the_player.y);
    return 0;
}