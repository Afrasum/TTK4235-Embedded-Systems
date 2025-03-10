#include "elevator.h"
#include "driver/elevio.h"
#include "stdio.h"
#include <time.h>



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
       elev->stop_button=true;

    } else
    {
        elev->stop_button = false;
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
        elevio_stopLamp(0);
    } 
}






void get_next_dir(Elevator *elev)
{
    // Hvis vi er i øverste etasje (4), stopper heisen

    if (elev->floor == 3)

    {
        elev->dir=0;

        for (int i = elev->floor - 1; i >= 0; i--)
        {
            if (elev->vil_opp[i] || elev->vil_ned[i] || elev->floor_stops[i])
            {
                elev->has_stopped = false;
                break;
            }
        }
        
    } else if (elev->floor == 0)
    {
        elev->dir=1;
         
        for (int i = 1; i <= 3; i++)
        {
            // Sjekker om det er noen som vil opp, ned eller om det er noen som har trykket på knappene i heisen
            if (elev->vil_opp[i] || elev->vil_ned[i] || elev->floor_stops[i])
            {
                elev->has_stopped = false;
                return;
            }
        }
    } 
    else if (elev->dir == 1)
    {
        // Sjekker om det er noen som vil opp, ned i etasjer over hvor heisen er eller om det er noen som har trykket på knappene i heisen
        for (int i = elev->floor + 1; i <= 3; i++)
        {
            if (elev->vil_opp[i] || elev->vil_ned[i] || elev->floor_stops[i])
            {
                elev->dir=1;
                elev->has_stopped = false;
                
                return;
            }

        }

        for (int i = elev->floor - 1; i >=0; i--)
        {
            if (elev->vil_opp[i] || elev->vil_ned[i] || elev->floor_stops[i])
            {
                elev->dir = 0;
                elev->has_stopped = false;
                return;
            }

        }
        
    } else if (elev->dir == 0)
    {
        for (int i = elev->floor - 1; i >= 0; i--)
        
        {
            if (elev->vil_opp[i] || elev->vil_ned[i] || elev->floor_stops[i])
            {
                elev->dir=0;
                elev->has_stopped = false;
                return;
            }
        }

        for (int i = elev->floor + 1; i <= 3; i++)
        {
            if (elev->vil_opp[i] || elev->vil_ned[i] || elev->floor_stops[i])
            {
                elev->dir = 1;
                elev->has_stopped = false;
                
                return;
            }

        }
    } 
}

void elevator_init(Elevator *elev)
// Initialiserer heisen til å starte i første etasje og med døren lukket
{
    if (elevio_floorSensor()==0){
  elev->has_stopped = true;
    elev->dir = 1;
    elev->door_is_open = false;
    elevio_doorOpenLamp(false);
    elev->floor = elevio_floorSensor();
    elev->sensor = elevio_floorSensor();
    for (int i = 0; i < 4; i++)
    {
        elev->vil_opp[i] = 0;
        elev->vil_ned[i] = 0;
        elev->floor_stops[i] = 0;
    }
        return;
    }
    while (elevio_floorSensor() != 0)
    {

        elevio_motorDirection(DIRN_DOWN);

        if (elevio_floorSensor() == 0)    {

        {
            elevio_motorDirection(DIRN_STOP);

            break;
        }
    }

    
    elev->has_stopped = true;
    elev->dir = 1;
    elev->door_is_open = false;
    elevio_doorOpenLamp(false);
    elev->floor = elevio_floorSensor();
    elev->sensor = elevio_floorSensor();
    for (int i = 0; i < 4; i++)
    {
        elev->vil_opp[i] = 0;
        elev->vil_ned[i] = 0;
        elev->floor_stops[i] = 0;
    }
}
}

//Sjekker hvilke knapper i heispanelen er trukket på, og setter verdiene i floor_stops. Oppdaterer lys i tillegg
void epanel(Elevator *elev)
{
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
    

    if(elev->vil_ned[floor]==1){

            bool continue_up=false;
            for (int i= floor+1; i<=N_FLOORS-1; i++){
                if(elev->vil_opp[i] || (elev->vil_ned[i] && dir==1) || elev->floor_stops[i]==1){
                    continue_up=true;
                    break;
                }
            }
            if(continue_up == false){
                    elev->door_is_open=true;
                    elev->has_stopped=true;
                    elev->vil_ned[floor]=0;
                   
                   
                        
            } 

    }

    if(elev->vil_opp[floor]==1){
        
        bool continue_down=false;
        for (int i= floor-1; i>=0; i--){
            if(elev->vil_opp[i] || (elev->vil_ned[i] && dir==0) || elev->floor_stops[i]==1){
                continue_down=true;
                break;
            }
        }
        if(continue_down==false){

            elev->vil_opp[floor]=0;
            elev->door_is_open=true;
            elev->has_stopped=true;
            
        }
}
    //Heispanel
    if(elev->floor_stops[floor]==1){

        elev->floor_stops[floor]=0;
        elev->door_is_open=true;
        elev->has_stopped=true;


    }

    //printf("%d ", elev->door_is_open);

}



void handle_door(Elevator *elev){
    if(elev->door_is_open==true){
        
        time_t start = time(NULL);   

        while(difftime(time(NULL), start) < 3.0){
            get_states(elev);
            update_states(elev);
            
            if (elevio_obstruction()) {
                start=time(NULL);
            }

        }
        
       elev->door_is_open=false;
        
        
    }
}
void stop(Elevator *elev){
    elevio_motorDirection(DIRN_STOP); 
    elevio_stopLamp(1);


    if (elevio_floorSensor()!=-1){
        elev->door_is_open=true;
        elevio_doorOpenLamp(1);

    }
    
    for (int i = 0; i < 4; i++)
    {
        elev->vil_opp[i] = 0;
        elev->vil_ned[i] = 0;
        elev->floor_stops[i] = 0;
    }

    elevio_motorDirection(DIRN_STOP);
    
    
    update_states(elev);


    while (elevio_stopButton()){
        elevio_motorDirection(DIRN_STOP); 

        }

    elevio_stopLamp(0);    
    elevio_doorOpenLamp(0);

    handle_door(elev);



   

        elev->has_stopped=true;



        
    while (1) {
        get_states(elev);
        epanel(elev);
        fpanel(elev);

     
        for (int i = 0; i < 4; i++) {
            if (elev->vil_opp[i] || elev->vil_ned[i] || elev->floor_stops[i]) {
                elev->has_stopped = false;
                get_next_dir(elev);
                update_states(elev);

                return;
            }
        }

        elevio_motorDirection(DIRN_STOP); 

    }
}



void printElevator(Elevator *e) {
    // Boolske felt – skriv ut som "true"/"false".
    printf("has_stopped:  %s\n", e->has_stopped  ? "true" : "false");
    printf("door_is_open: %s\n", e->door_is_open ? "true" : "false");
    printf("obstruction:  %s\n", e->obstruction  ? "true" : "false");
    printf("stop_button:  %s\n", e->stop_button  ? "true" : "false");

    // Enkle heltallsfelt.
    printf("dir:    %d\n", e->dir);
    printf("floor:  %d\n", e->floor);
    printf("sensor: %d\n", e->sensor);
    printf("size:   %d\n", e->size);

    // Array-felter. Bruk løkker for å gå gjennom dem.
    printf("floor_stops:\n");
    for (int i = 0; i < 4; i++) {
        printf("  [%d] = %d\n", i, e->floor_stops[i]);
    }

    printf("vil_opp:\n");
    for (int i = 0; i < 4; i++) {
        printf("  [%d] = %s\n", i, e->vil_opp[i] ? "true" : "false");
    }

    printf("vil_ned:\n");
    for (int i = 0; i < 4; i++) {
        printf("  [%d] = %s\n", i, e->vil_ned[i] ? "true" : "false");
    }
}


//.               ,.
//T."-._..---.._,-"/|
//l|"-.  _.v._   (" |
//[l /.'_ \; _~"-.`-t
//Y " _(o} _{o)._ ^.|
//j  T  ,-<v>-.  T  ]
//\  l ( /-^-\ ) !  !
// \. \.  "~"  ./  /c-..,__
//   ^r- .._ .- .-"  `- .  ~"--.
//    > \.                      \
//    ]   ^.                     \
//    3  .  ">            .       Y  -Mjau
//,.__.--._   _j   \ ~   .         ;       |
//(    ~"-._~"^._\   ^.    ^._      I     . l
//"-._ ___ ~"-,_7    .Z-._   7"   Y      ;  \        _
///"   "~-(r r  _/_--._~-/    /      /,.--^-._   / Y
//"-._    '"~~~>-._~]>--^---./____,.^~        ^.^  !
//~--._    '   Y---.                        \./
//   ~~--._  l_   )                        \
//         ~-._~~~---._,____..---           \
//             ~----"~       \