#include <uarh.h>
#include <gpio.h>
#include <stdint.h>



#define UART ((NRF_UART_REG*)0x40002000)

typedef struct {
    volatile uint32_t TASKS_STARTRX;
    volatile uint32_t TASKS_STOPRX;
    volatile uint32_t TASKS_STARTTRX;
    volatile uint32_t TASKS_STOPTX;
    volatile uint32_t RESERVED0[3];
    volatile uint32_t TASKS_SUSPEND;
    volatile uint32_t RESERVED1[56];
    volatile uint32_t EVENTS_CTS;
    volatile uint32_t EVENTS_NCTS;
    volatile uint32_t EVENTS_RXDRDY;
    volatile uint32_t RESERVED2[4];
    volatile uint32_t EVENTS_TXDRDY;
    volatile uint32_t RESERVED3[1];
    volatile uint32_t EVENTS_ERROR;
    volatile uint32_t RESERVED4[7];
    volatile uint32_t EVENTS_RXTO;
    volatile uint32_t RESERVED5[46];
    volatile uint32_t SHORTS;
    volatile uint32_t RESERVED6[64];
    volatile uint32_t INTENSET;
    volatile uint32_t INTENCLR;
    volatile uint32_t RESERVED7[93];
    volatile uint32_t ERRORSRC;
    volatile uint32_t RESERVED8[31];
    volatile uint32_t ENABLE;
    volatile uint32_t RESERVED9[1];
    volatile uint32_t PSELRTS;
    volatile uint32_t PSELTXD;
    volatile uint32_t PSELCTS;
    volatile uint32_t PSELRXD;
    volatile uint32_t RXD; 
    volatile uint32_t TXD;
    volatile uint32_t RESERVED10[1];
    volatile uint32_t BAUDRATE;
    volatile uint32_t RESERVED11[17];
    volatile uint32_t CONFIG;
}NRF_UART_REG;


void uart_pins_init(){ 

    GPIO->DIRSET = (1 << 6);
    GPIO->DIRCLR = (1 << 8);
    /* GPIO->DIRCLR = (1 << 7); */
    /* GPIO->DIRSET = (1 << 5); */

    UART->PSELTXD = (0 << 6);
    UART->PSELRXD = (0 << 8);

    UART->BAUDRATE = 0x00275000;

    UART->PSELRTS = 0xFFFFFFFF;
    UART->PSELCTS = 0xFFFFFFFF;

    UART->ENABLE = 4;

    UART->TASKS_STARTRX = 1;        

}

void uart_send(char letter){

    UART->TASKS_STARTTX = 1; //Starter TX

    UART->TXD = letter;
 //Venter til den blir 1
    while(!UART->EVENTS_TXDRDY){
        __NOP();
    }
    
    UART->EVENTS_TXDRDY = 0; 
    UART->TASKS_STOPTX = 1; //Stopper TX


}

char uart_read(){

//Venter til den blir 1
if(UART->EVENTS_RXDRDY==1){


    
 //Setter lik 0
  UART->EVENTS_RXDRDY = 0; 

//leser
   return (char) UART->RXD;

}

else {

    return "\0";
}

}





    













}



