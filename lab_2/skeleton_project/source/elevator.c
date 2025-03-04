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
    elev->door_is_open = value;
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
        elev->dir = DIRN_STOP;
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
    // Sjekker om det er noen som vil opp, ned i etasjer under hvor heisen er eller om det er noen som har trykket på knappene i heisen
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
    }
    else
    {
        elev->dir = DIRN_STOP;
    }
}

void elevator_init(Elevator *elev)
// Initialiserer heisen til å starte i første etasje og med døren lukket
{
    while (elevio_floorSensor() != 0)
    {

        elevio_motorDirection(DIRN_DOWN);

        if (elevio_floorSensor() == 0)
        {
            elevio_motorDirection(DIRN_STOP);

            break;
        }
    }

    elev->has_stopped = true;
    elev->dir = DIRN_STOP;
    elev->door_is_open = false;
    elev->floor = elevio_floorSensor();
    elev->sensor = elevio_floorSensor();
    for (int i = 0; i < 4; i++)
    {
        elev->vil_opp[i] = 0;
        elev->vil_ned[i] = 0;
        elev->floor_stops[i] = 0;
    }
}

void panel(Elevator *elev)
{
    int floor;
    for (int i = 0; i <= 3; i++)
    {
        floor = elevio_callButton(i, BUTTON_CAB);
        elev->floor_stops[i] = floor;
        if (floor)
        {
            elevio_buttonLamp(i, BUTTON_CAB, 1);
        }
    }
}
