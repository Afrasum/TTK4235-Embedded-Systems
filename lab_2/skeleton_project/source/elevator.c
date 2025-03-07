#include "elevator.h"
#include "driver/elevio.h"
#include "stdio.h"


void get_states(Elevator *elev)
{
    fpanel(elev);
    epanel(elev);

    elev->sensor = elevio_floorSensor();
    if (elev->sensor != -1)
    {
        elev->floor = elev->sensor;
    }

    if (elevio_stopButton())
    {
        elev->stop_button = true;
    } else
    {
        elev->has_stopped = false;
    } 

    if (elevio_obstruction())
    {
        elev->obstruction = true;
    } else
    {
        elev->obstruction = false;
    }
}

void update_states(Elevator *elev)
{
    if (elev->has_stopped)
    {
        elevio_motorDirection(DIRN_STOP);
    } else if (elev->dir == 1)
    {
        elevio_motorDirection(DIRN_UP);
    } else if (elev->dir == 0)
    {
        elevio_motorDirection(DIRN_DOWN);
    }

    for (int i = 0; i < 4; i++)
    {
        elevio_buttonLamp(i, BUTTON_HALL_UP, elev->vil_opp[i]);
        elevio_buttonLamp(i, BUTTON_HALL_DOWN, elev->vil_ned[i]);
        elevio_buttonLamp(i, BUTTON_CAB, elev->floor_stops[i]);
    }

    if (elev->door_is_open)
    {
        elevio_doorOpenLamp(1);
    } else
    {
        elevio_doorOpenLamp(0);
    }

    if (elev->floor == 0)
    {
        elevio_floorIndicator(0);
    } else if (elev->floor == 1)
    {
        elevio_floorIndicator(1);
    } else if (elev->floor == 2)
    {
        elevio_floorIndicator(2);
    } else if (elev->floor == 3)
    {
        elevio_floorIndicator(3);
    }

    if (elev->has_stopped)
    {
        elevio_stopLamp(1);
    } 
}





void get_next_dir(Elevator *elev)
{
    // Hvis vi er i øverste etasje (4), stopper heisen
    if (elev->floor == 3)
    {
        elev->dir = 0;
    } else if (elev->floor == 0)
    {
        for (int i = 1; i <= 3; i++)
        {
            // Sjekker om det er noen som vil opp, ned eller om det er noen som har trykket på knappene i heisen
            if (elev->vil_opp[i] || elev->vil_ned[i] || elev->floor_stops[i])
            {
                elev->dir = 1;
                break;
            }
        }
    } else if (elev->dir == 1)
    {
        // Sjekker om det er noen som vil opp, ned i etasjer over hvor heisen er eller om det er noen som har trykket på knappene i heisen
        for (int i = elev->floor + 1; i <= 3; i++)
        {
            if (elev->vil_opp[i] || elev->vil_ned[i] || elev->floor_stops[i])
            {
                elev->dir = 1;
                break;
            }
        }
    } else if (elev->dir == 0)
    {
        for (int i = elev->floor - 1; i >= 0; i--)
        {
            if (elev->vil_opp[i] || elev->vil_ned[i] || elev->floor_stops[i])
            {
                elev->dir = 0;
                break;
            }
        }
    } else
    {
        elev->dir = 0;
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
    elev->dir = 1;
    elev->door_is_open = false;
    elevio_doorOpenLamp(0);
    elev->floor = elevio_floorSensor();
    elev->sensor = elevio_floorSensor();
    for (int i = 0; i < 4; i++)
    {
        elev->vil_opp[i] = 0;
        elev->vil_ned[i] = 0;
        elev->floor_stops[i] = 0;
    }
}

//Sjekker hvilke knapper i heispanelen er trukket på, og setter verdiene i floor_stops. Oppdaterer lys i tillegg
void epanel(Elevator *elev)
{f(p_el->door_is_open==0 && p_el->has_stopped==1 || p_el->dir==1 && p_el->floor==4 || p_el->dir==0 && p_el->floor==1){

                    get_next_dir(p_el);
                    
                }
                // int floor = elevio_floorSensor();

                /* if(floor == 0){ */
                /*     elevio_motorDirection(DIRN_UP); */
                /* } */
                /**/
                /* if(floor == N_FLOORS-1){ */
                /*     elevio_motorDirection(DIRN_DOWN); */
                /* } */
                /**/
                /**/
                /* for(int f = 0; f < N_FLOORS; f++){ */
                /*     for(int b = 0; b < N_BUTTONS; b++){ */
                /*         int btnPressed = elevio_callButton(f, b); */
                /*         elevio_buttonLamp(f, b, btnPressed); */
                /*     } */
                /* } */
                /**/
            

                if(elevio_obstruction()){ 
                    elevio_stopLamp(1); 
                } else { 
                    elevio_stopLamp(0); 
                } 
                
                if(elevio_stopButton()){ 
                    elevio_motorDirection(DIRN_STOP); 
                    break; 
                } 
            }

    int floor_pushed;
    for (int i = 0; i <= N_FLOORS-1; i++)
    {
        floor_pushed=elevio_callButton(i, BUTTON_CAB);
        if(floor_pushed){
            elev->floor_stops[i] = 1;
        }
    }
}


//Sjekker hvilke knapper i etajsepanelen er trukket, og setter verdiene i vil_opp og vil_ned. Oppdaterer lys itillegg 
void fpanel(Elevator *elev){

    int up_pressed;
    int down_pressed;

    for (int i= 0; i <=N_FLOORS-1; i++)
    {
        up_pressed = elevio_callButton(i, BUTTON_HALL_UP);
        down_pressed = elevio_callButton(i, BUTTON_HALL_DOWN);
       
        if (up_pressed) 
        {
            elev->vil_opp[i] = 1;
        }
    
        if(down_pressed)
        {
            elev->vil_ned[i]=1;
        }
    }

}
    

void arrival(Elevator *elev){
    //Sjekker om man har ankommet en etasje som har blitt trykket på, skrur dermed lyset på etasjen, og endrer verdien til 0 i den etasjen. 
    //EtasjePanel

    int floor = elev->floor;
    int dir = elev->dir;


    if(elev->vil_ned[floor]==1 && dir==0){

        elev->vil_ned[floor]=0;
        elev->door_is_open=1;
        elev->has_stopped=1;

    }
    if(elev->vil_opp[floor]==1 && dir==1){

        elev->vil_opp[floor]=0;
        elev->door_is_open=1;
        elev->has_stopped=1;


    }

    //Heispanel
    if(elev->floor_stops[floor]==1){

        elev->floor_stops[floor]=0;
        elev->door_is_open=1;
        elev->has_stopped=1;


    }

    printf("%d ", elev->door_is_open);

}
