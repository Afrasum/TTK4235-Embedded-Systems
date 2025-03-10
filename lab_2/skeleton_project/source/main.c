
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
    elevator_init(p_el);
    update_states(p_el);

    
    printElevator(p_el);
    printf("Press the stop button on the elevator panel to exit\n");
    elevio_motorDirection(DIRN_STOP);           
    
    

    // elevio_motorDirection(DIRN_UP);

    while (1)
    {
        
        get_states(p_el);
        if(p_el->sensor!=-1){
            printf("Got states: ");

            printElevator(p_el);
            arrival(p_el);
            update_states(p_el);


            printf("After arrival: ");
            printElevator(p_el);

        }
       
       handle_door(p_el);

       if (elevio_obstruction()) { 
        if (p_el->door_is_open) {
            elevio_motorDirection(DIRN_STOP);
            elevio_doorOpenLamp(1);
        }
    } else {
            handle_door(p_el);
        }


        get_states(p_el);
        handle_door(p_el);
    
        if (!p_el->door_is_open && p_el->has_stopped) {
            for (int i = 0; i < 4; i++) {
                if (p_el->vil_opp[i] || p_el->vil_ned[i] || p_el->floor_stops[i]) {
                    get_next_dir(p_el);
                    update_states(p_el);
                    break;
                }
            }
        }
    
    
       
           
        if (elevio_stopButton()){ 
            stop(p_el);
            update_states(p_el);
               

                
                

            
        nanosleep(&(struct timespec){0, 20*1000*1000}, NULL); 
    }


    }
    return 0;
}
