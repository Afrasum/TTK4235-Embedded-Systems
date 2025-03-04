#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct
{

    bool has_stopped;
    int dir;
    bool door;
    int floor;
    int floor_stops[4];
    bool sensor;
    int size;
    bool vil_opp[4];
    bool vil_ned[4];

} Elevator;

void update_vil_opp(Elevator *elev, int floor, bool value);
void update_vil_ned(Elevator *elev, int floor, bool value);
void update_stops(Elevator *elev, int floor, bool value);
void update_door(Elevator *elev, bool value);
void update_has_stopped(Elevator *elev, bool value);
void update_floor(Elevator *elev, int value);
