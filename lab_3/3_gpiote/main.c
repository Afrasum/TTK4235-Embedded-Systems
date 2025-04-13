#include "gpiote.h"   // Inkluder header for GPIOTE
#include "ppi.h"      // Inkluder header for PPI
#include "gpio.h"     // Inkluder evt. header for GPIO (hvor GPIO->DIRSET osv. er definert)
#include <stdint.h>

#define DELAY_LOOP_CONSTANT_1MS 16000


void led_init(void) {
    for (int i = 17; i <= 20; i++) {
        GPIO->DIRSET = (1 << i); // Sett pin som utgang
        GPIO->OUTSET = (1 << i); // Sett pin høy (LED-er er aktivt lave, altså av)
    }
}

void buttons_init(void) {
    GPIO->PIN_CNF[13] = (3 << 2); // Sett pin 13 som input med pull-up
    GPIO->PIN_CNF[14] = (3 << 2); // Sett pin 14 som input med pull-up
}

void gpiote_init(void) {
    // Konfigurer GPIOTE kanal 0 for BUTTON 1 (f.eks. pin 13), modus Event, polaritet Hi-to-Lo (typisk for en aktiv lav knapp)
    GPIOTE->CONFIG[0] = (1 << 0) | (13 << 8) | (2 << 16);
    
    // Konfigurer GPIOTE-kanaler for LED-oppgaver. Her bruker vi Task-modus med toggle.
    // For eksempel: Kanal 1 for LED på pin 17, kanal 2 for LED på pin 18, 
    // kanal 4 for LED på pin 19 og kanal 5 for LED på pin 20.
    GPIOTE->CONFIG[1] = (3 << 0) | (17 << 8) | (3 << 16);
    GPIOTE->CONFIG[2] = (3 << 0) | (18 << 8) | (3 << 16);
    GPIOTE->CONFIG[4] = (3 << 0) | (19 << 8) | (3 << 16);
    GPIOTE->CONFIG[5] = (3 << 0) | (20 << 8) | (3 << 16);
}

void ppi_init(void) {
    // Vi kobler BUTTON 1-hendelsen (konfigurert på GPIOTE-kanal 0, således EVENTS_IN[0])
    // til LED-oppgavene. For hver PPI-kanal må vi lagre adressen til hendelsen (EEP)
    // og adressen til oppgaven (TEP), typecastet til uint32_t.
    
    // PPI-kanal 0 kobler til LED-oppgave på GPIOTE-kanal 1:
    PPI->PPI_CH[0].EEP = (uint32_t)&(GPIOTE->EVENTS_IN[0]);
    PPI->PPI_CH[0].TEP = (uint32_t)&(GPIOTE->TASKS_OUT[1]);
    
    // PPI-kanal 1 kobler til LED-oppgave på GPIOTE-kanal 2:
    PPI->PPI_CH[1].EEP = (uint32_t)&(GPIOTE->EVENTS_IN[0]);
    PPI->PPI_CH[1].TEP = (uint32_t)&(GPIOTE->TASKS_OUT[2]);
    
    // PPI-kanal 2 kobler til LED-oppgave på GPIOTE-kanal 4:
    PPI->PPI_CH[2].EEP = (uint32_t)&(GPIOTE->EVENTS_IN[0]);
    PPI->PPI_CH[2].TEP = (uint32_t)&(GPIOTE->TASKS_OUT[4]);
    
    // PPI-kanal 3 kobler til LED-oppgave på GPIOTE-kanal 5:
    PPI->PPI_CH[3].EEP = (uint32_t)&(GPIOTE->EVENTS_IN[0]);
    PPI->PPI_CH[3].TEP = (uint32_t)&(GPIOTE->TASKS_OUT[5]);
    
    // Aktiver PPI-kanalene 0 til 3
    PPI->CHENSET = (1 << 0) | (1 << 1) | (1 << 2) | (1 << 3);
}
void delay_ms(volatile unsigned int ms) {
    volatile unsigned int i, j;
    for (i = 0; i < ms; i++) {
        for (j = 0; j < DELAY_LOOP_CONSTANT_1MS; j++) {
            __asm__("nop"); // Hindre optimalisering, "no operation"
        }
    }
}


int main(void) {
		led_init();
		buttons_init();
		gpiote_init();
		ppi_init();

		while (1) {
				// Main loop does nothing, everything is handled by interrupts and PPI
				__asm__("nop"); // No operation
		}
}
