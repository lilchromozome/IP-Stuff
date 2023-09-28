#include "player_ops.h"

void move_player(struct Player *p, int dx, int dy){
    p -> x += dx;
    p -> y += dy;
}