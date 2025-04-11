#ifndef SYSTEM_H
#define SYSTEM_H

/**
 * @file system.h
 * @brief Definerer systemobjeter of funksjoner for å representere og håndtere systemer
 */

/*
 * @brief Enum of tuning rules
 */
typedef enum {
    Classic_Ziegler_Nichols, /*< Ziegler Nichols */
    Pessen_Integral_Rule /*< Pessen */
} Tuning;

/**
 * @brief A structure to represent a system and desired PID tuning method.
 */
typedef struct {
    double Ku;            /** < The gain margin for loop stability */
    double Tu;            /** < The period of the oscillations frequency at the stability limit */
    Tuning tuning_method; /** < The desired PID tuning method */
} System;


/**
 * @brief Oppretter nytt systemobjekt
 *
 * @param[in] Ku Gain margin for loop stability
 * @param[in] Tu Period of the oscillations frequency at the stability limit
 * @param[in] tuning_method Ønsket PID tuning metode 
 * @return En peker til det nyopprettede systemobjektet
 */
System * system_create(double Ku, double Tu, Tuning tuning_method);

/**
 * @brief Sletter systemobjektet
 *
 * @param[in] system_current En peker til systemobjektet som skal slettes
 */
void system_delete(System * system_current);

#endif
