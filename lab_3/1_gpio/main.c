 #include <stdint.h>



        
#define GPIO ((NRF_GPIO_REGS*)0x50000000)

typedef struct {
    volatile uint32_t RESERVED0[321]; 
    volatile uint32_t OUT; 
    volatile uint32_t OUTSET;
    volatile uint32_t OUTCLR;
    volatile uint32_t IN;
    volatile uint32_t DIR;
    volatile uint32_t DIRSET;
    volatile uint32_t DIRCLR;
    volatile uint32_t LATCH;
    volatile uint32_t DETECTMODE;
    volatile uint32_t RESERVED1[118];
    volatile uint32_t PIN_CNF[32];
} NRF_GPIO_REGS;

void button_init(){ 
    GPIO->PIN_CNF[13] = (3 << 2); //venstre skifter slik at vi får pullup
    GPIO->PIN_CNF[14] = (3 << 2);
    // Fill inn the configuration for the remaining buttons 
}

int main(){
    // Configure LED Matrix
    for(int i = 17; i <= 20; i++){
        GPIO->DIRSET = (1 << i); //forteller pi at det er en output pin
        GPIO->OUTCLR = (1 << i); // Setter output til 0
    }

    // Configure buttons -> see button_init()
    button_init();


    int sleep = 0;
    while(1){

        /* Check if button 1 is pressed;
         * turn on LED matrix if it is. */

        if (((GPIO->IN >> 13) & 1) == 0){   // sjekker om input i pin 13 er 1, og siden knappene er aktiv lave, så er knappene trukket når den statmenten er false

            for(int i = 17; i <= 20; i++){  //går i hvert ledlys
                GPIO->OUTCLR = (1 << i);    // setter ledlys på, siden de er også aktiv lave 
            }
        }

        /* Check if button 2 is pressed;
         * turn off LED matrix if it is. */

         //akkurat samme bare med knapp 2, og skur av lyset

         if (((GPIO->IN >> 14) & 1) == 0){

            for(int i = 17; i <= 20; i++){
                GPIO->OUTSET = (1<< i);
            }
        }

        sleep = 10000;
        while(--sleep); // Delay
    }
    return 0;
}
