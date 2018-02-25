#include "io_device.h"
/*
 *      io_device.h
 *
 *      Hazen Breen and Jordan Stone
 *
 *      This header file contains the function definitions for the functions
 *      relating to the io_device.
 *
 */

/* 
 * Name: input_from_file_stream
 * Purpose: reads the word from from the file stream
 */
uint32_t input_from_file_stream()
{
        uint32_t c = getc(stdin);
        if (c == EOF) {
                /* code */
        }                  
        return;  
}

/* 
 * Name: output_to_file_stream
 * Purpose: writes words to stdout
 */
void output_to_file_stream(uint32_t word)
{
        putchar((char) byte);
}


