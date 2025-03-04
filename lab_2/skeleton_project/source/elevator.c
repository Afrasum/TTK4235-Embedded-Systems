#include "elevator.h"
#include "driver/elevio.h"

void update_vil_opp(Elevator *elev, int floor, bool value)
{
    elev->vil_opp[floor] = value;
}

void update_vil_ned(Elevator *elev, int floor, bool value)
{
    elev->vil_ned[floor] = value;
}

void update_stops(Elevator *elev, int floor, bool value)
{
    elev->floor_stops[floor] = value;
}

void update_door(Elevator *elev, bool value)
{
    elev->door = value;
}

void update_has_stopped(Elevator *elev, bool value)
{
    elev->has_stopped = value;
}

void update_floor(Elevator *elev, int value)
{
    elev->floor = value;
}

void update_dir(Elevator *elev, int value)
{
    elev->dir = value;
}

void update_sensor(Elevator *elev, bool value)
{
    elev->sensor = value;
}

void get_next_dir(Elevator *elev)
{
    // Hvis vi er i øverste etasje (4), stopper heisen
    if (elev->floor == 3)
    {
        elev->dir == DIRN_STOP;
    }
    else if (elev->floor == 0)
    {
        for (int i = 1; i <= 3; i++)
        {
            // Sjekker om det er noen som vil opp, ned eller om det er noen som har trykket på knappene i heisen
            if (elev->vil_opp[i] || elev->vil_ned[i] || elev->floor_stops[i])
            {
                elev->dir = DIRN_UP;
                break;
            }
        }
    }
    else if (elev->dir == DIRN_UP)
    {
        // Sjekker om det er noen som vil opp, ned i etasjer over hvor heisen er eller om det er noen som har trykket på knappene i heisen
        for (int i = elev->floor + 1; i <= 3; i++)
        {
            if (elev->vil_opp[i] || elev->vil_ned[i] || elev->floor_stops[i])
            {
                elev->dir = DIRN_UP;
                break;
            }
        }
    }
    else if (elev->dir == DIRN_DOWN)
    {
        for (int i = elev->floor - 1; i >= 0; i--)
        {
            if (elev->vil_opp[i] || elev->vil_ned[i] || elev->floor_stops[i])
            {
                elev->dir = DIRN_DOWN;
                break;
            }
        }
        else
        {
            elev->dir = DIRN_STOP;
        }
    }

    void elevator_init(Elevator * elev)
    {
        elev->has_stopped = true;
        elev->dir = 1;
        elev->door = elevio_doorOpenLamp();
        elev->floor = elevio_floorSensor();
        elev->sensor = elevio_floorSensor();
        elev->vil_opp = {false, false, false, false};
        elev->vil_ned = {false, false, false, false};
        elev->floor_stops = {false, false, false, false};
    }
