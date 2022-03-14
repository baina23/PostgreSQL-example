#include "exerciser.h"

void exercise(connection *C)
{
    string state = "FL";
    string color = "Green";
    //query4(C, state, color);
    add_state(C, state);
    add_color(C, color);
    return;
}
