
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include "driver/elevio.h"
#include "elevator.h"

int main()
{
    Elevator el;
    Elevator *p_el = &el;
    elevio_init();
    elevator_init(&el);

    printf("Press the stop button on the elevator panel to exit\n");
    
    

    // elevio_motorDirection(DIRN_UP);

    while (1)
    {
        get_states(p_el);
        if(p_el->sensor!=-1){
            arrival(p_el);

        }

        if(p_el->door_is_open==1){
            for (int i = 0; i<10000000; i++) {
                get_states(p_el);

            }
            if(p_el->obstruction!=0){
                p_el->door_is_open=0;
            }
            
            
        }
        if(p_el->door_is_open==0){
            if(p_el->door_is_open==0 && p_el->has_stopped==1 || p_el->dir==1 && p_el->floor==4 || p_el->dir==0 && p_el->floor==1){

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

        update_states(p_el);
        nanosleep(&(struct timespec){0, 20*1000*1000}, NULL); 
    }

    return 0;
}
