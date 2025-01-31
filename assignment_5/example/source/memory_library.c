/**
 * @file
 * @brief Implementation file for memory library
 */
#include "memory_library.h"
#include <stdlib.h>



/**
* @brief copy a list of integers from one buffer to another
* reversing the order of the output in the process
*
* @param[in] p_from Source buffer
* @param[out] p_to Destination buffer
* @param[in] size Number of integers in buffer
*
* @return 0 on success, 1 if either @p p_from or @p p_to is a @c NULL pointer
* */
int memory_reverse_copy(const int * p_from, int * p_to, int size){
    if(p_from == NULL || p_to == NULL)
        return 1;

    for(int i = 0; i < size; i++){
        p_to[size - i - 1] = p_from[i];
    }
    return 0;
}

/**
* @brief Multiply all the elements in @p p_buffer, of size
* @p size with the supplied @p factor.
*
* @param[in,out] p_buffer Buffer of integers to be multiplied
* with @p factor.
*
* @param[in] factor Factor to multiply each of the
* elements in @p p_buffer with.
*
* @param[in] size Size of @p p_buffer.
*
* @warning If @p p_buffer is @c NULL, the function will
* abruptly terminate the program with exit code @c 1.
*/
void memory_multiply_elements(int * p_buffer, int factor, int size){
    if(p_buffer == NULL)
        exit(1);

    for(int i = 0; i < size; i++){
        p_buffer[i] *= factor;
    }
}
