
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
       
        if(p_el->door_is_open==true){
            time_t start = time(NULL);   

            while(difftime(time(NULL), start) < 3.0){
                get_states(p_el);
                update_states(p_el);

            }
            if(p_el->obstruction!=true){
                p_el->door_is_open=false;
                update_states(p_el);

            }
            
            
        }

        if(p_el->door_is_open==0){
            if(p_el->door_is_open==0 && p_el->has_stopped==true || p_el->dir==1 && p_el->floor==3 || p_el->dir==0 && p_el->floor==0){
                    get_next_dir(p_el);

                    
                    
                }
             

                
            }
        if(elevio_obstruction()){ 
                elevio_stopLamp(1); 
            } else { 
                elevio_stopLamp(0); 
            } 
            
        if(elevio_stopButton()){ 
                update_states(p_el);
                elevio_motorDirection(DIRN_STOP); 
                
            } 
        nanosleep(&(struct timespec){0, 20*1000*1000}, NULL); 
    }

    return 0;
}
