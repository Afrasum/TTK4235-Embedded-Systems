#ifndef GPIO_DRIVER_H
#define GPIO_DRIVER_H

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

#define GPIO ((NRF_GPIO_REGS*)0x50000000)

void button_init(void);  // Bare prototype

#endif
