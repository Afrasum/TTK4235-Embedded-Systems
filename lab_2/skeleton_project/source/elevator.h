#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct
{

    bool has_stopped;
    int dir;
    bool door_is_open;
    int floor;
    int floor_stops[4];
    int sensor;
    int size;
    bool vil_opp[4];
    bool vil_ned[4];
    bool obstruction;
    bool stop_button;

} Elevator;

void update_vil_opp(Elevator *elev, int floor, bool value);
void update_vil_ned(Elevator *elev, int floor, bool value);
void update_stops(Elevator *elev, int floor, bool value);
void update_door(Elevator *elev, bool value);
void update_has_stopped(Elevator *elev, bool value);
void update_floor(Elevator *elev, int value);

void update_states(Elevator *elev);
void get_next_dir(Elevator *elev);
void elevator_init(Elevator *elev);
void epanel(Elevator *elev);
void fpanel(Elevator *elev);
void arrival(Elevator *elev);
void handle_door(Elevator *elev);
void stop(Elevator *elev);

