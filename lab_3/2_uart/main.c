#include <stdint.h>
#include "uart.h"
#include "buttons.h"

// Omtrentlige sykluser for 1 ms ved 64 MHz.
// Her antar vi at en enkel iteration i løkken bruker ~4 CPU-sykluser.
// Du kan starte med en antatt faktor og deretter justere empirisk.
#define DELAY_LOOP_CONSTANT_1MS 16000

void delay_ms(volatile unsigned int ms) {
    volatile unsigned int i, j;
    for (i = 0; i < ms; i++) {
        for (j = 0; j < DELAY_LOOP_CONSTANT_1MS; j++) {
            __asm__("nop"); // Hindre optimalisering, "no operation"
        }
    }
}

void leds_init(void) {
    // Sett pinnene 17, 18, 19 og 20 til utgang
    for (int i = 17; i <= 20; i++) {
        GPIO->DIRSET |= (1 << i);
    }
}


int main(void) {
    uart_init();
    button_init();
    leds_init();
    
    int leds_on = 0; // Hold track of LED state
    char letter;

    while (1) {
        // Sjekk knapper og send UART-data
        if (((GPIO->IN >> 13) & 1) == 0) {
            uart_send('A');
            delay_ms(200); // Debounce delay
        } 
        
        if (((GPIO->IN >> 14) & 1) == 0) {
            uart_send('B');
            delay_ms(200); // Debounce delay
        }
        
        // Sjekk for mottatte data
        letter = uart_read();
        uart_send(letter); // Send tilbake det mottatte tegnet
        if (letter != '\0') {
            // Toggle LED state on any received character
            if (leds_on) {
                // Slå av LED-lysene
                for(int i = 17; i <= 20; i++) {
                    GPIO->OUTSET = (1 << i);
                }
                leds_on = 0;
            } else {
                // Slå på LED-lysene
                for(int i = 17; i <= 20; i++) {
                    GPIO->OUTCLR = (1 << i);
                }
                leds_on = 1;
            }
        }

        if (letter == 'q') {
            // Avslutt programmet hvis 'q' er mottatt
            break;
        }

    }
        
    return 0;
}

