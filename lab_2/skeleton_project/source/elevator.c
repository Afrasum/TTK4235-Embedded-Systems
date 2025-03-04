#include "elevator.h"
#include "elevio.h"

void update_vil_opp(Elevator &elev, int floor, bool value){
    elev.vil_opp[floor] = value;
}

void update_vil_ned(Elevator &elev, int floor, bool value){
    elev.vil_ned[floor] = value;
}

void update_stops(Elevator &elev, int floor, bool value){
    elev.floor_stops[floor] = value;
}

void update_door(Elevator &elev, bool value){
    elev.door = value;
}

void update_has_stopped(Elevator &elev, bool value){
    elev.has_stopped = value;
}

void update_floor(Elevator &elev, int value){
    elev.floor = value;
}

void update_dir(Elevator &elev, int value){
    elev.dir = value;
}

void update_sensor(Elevator &elev, bool value){
    elev.sensor = value;
} 

void get_next_dir(Elevator &elev){
    if(elev.floor == 4) {
        elev.dir == 0;
    } else if (elev.floor == 0) {
        for (int i = 2; i <= 4; i++) {
            if (elev.vil_opp[i] || elev.vil_ned[i]) || elev.floor_stops[i]) {
                elev.dir = 1;
                break;
            }
        }
    } else {
        if (elev.dir == 1) {
            for (int i = elev.floor + 1; i <= 4; i++) {
                if (elev.vil_opp[i] || elev.vil_ned[i] || elev.floor_stops[i]) {
                    elev.dir = 1;
                    break;
                }
            }
        } else if (elev.dir == 0) {
            for (int i = elev.floor - 1; i >= 1; i--) {
                if (elev.vil_opp[i] || elev.vil_ned[i] || elev.floor_stops[i]) {
                    elev.dir = 0;
                    break;
                }
            }
        } else {
            elev.dir = 0;
        }
    }
}

void elevator_init(Elevator &elev){
    elev.has_stopped = true;
    elev.dir = 1;
    elev.door = elevio_doorOpenLamp();
    elev.floor = elevio_floorSensor();
    elev.sensor = elevio_floorSensor();
    elev.vil_opp = {false, false, false, false};
    elev.vil_ned = {false, false, false, false};
    elev.floor_stops = {false, false, false, false};
}
