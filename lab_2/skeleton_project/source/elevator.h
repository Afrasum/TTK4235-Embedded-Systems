#include <iostream>
#include <vector>


typedef struct {

    bool has_stopped;
    int dir;
    bool door;
    int floor;
    int floor_stops[4];
    bool sensor;
    std::vector<bool> vil_opp;
    std::vector<bool> vil_ned;


} Elevator;


void update_vil_opp(Elevator &elev, int floor, bool value);
void update_vil_ned(Elevator &elev, int floor, bool value);
void update_stops(Elevator &elev, int floor, bool value);
void update_door(Elevator &elev, bool value);
void update_has_stopped(Elevator &elev, bool value);
void update_floor(Elevator &elev, int value);

