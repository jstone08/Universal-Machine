#ifndef IO_DEVICE_INCLUDED
#define IO_DEVICE_INCLUDED

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

/*
 *      io_device.h
 *
 *      Hazen Breen and Jordan Stone
 *
 *      This header file contains the function declarations for the functions
 *      relating to the io_device.
 */

uint32_t input_from_file_stream();

void output_to_file_stream(uint32_t word);

#endif
