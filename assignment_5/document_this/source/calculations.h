#ifndef CALCULATIONS_H
#define CALCUATIONS_H
#include "system.h"

// Document this

/**
 * @file calculations.h
 * @brief Funksjoner for å beregne PID-parametre
 *
*/

/**
 * @brief Beregner P-parameteren for PID
 *
 * @param[in] current_system En peker til systemstrukturen som inneholder Ku og Tu
 * @return P-parameteren
 */
double calculate_P_parameter(System * current_system);

/**
 * @brief Beregner I-parameteren for PID
 *
 * @param[in] current_system En peker til systemstrukturen som inneholder Ku og Tu
 * @return I-parameteren
 */
double calculate_I_parameter(System * current_system);

/**
 * @brief Beregner D-parameteren for PID
 *
 * @param[in] current_system En peker til systemstrukturen som inneholder Ku og Tu
 * @return D-parameteren
 */
double calculate_D_parameter(System * current_system);

#endif
