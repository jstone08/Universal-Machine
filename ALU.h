#ifndef ALU_INCLUDED
#define ALU_INCLUDED
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <seq.h>
#include "segmented_memory.h"

/*
 *      ALU.h
 *
 *      Hazen Breen and Jordan Stone
 *
 *      This header file contains the function declarations for the functions
 *      relating to the UM instructions module.
 *
 */

void conditional_move(uint8_t A, uint8_t B, uint8_t C);

void segmented_load(Seq_T memory, uint8_t A, uint8_t B,
        uint8_t C);

void segmented_store(Seq_T memory, uint8_t A, uint8_t B,
        uint8_t C);

void add(uint8_t A, uint8_t B, uint8_t C);

void multiply(uint8_t A, uint8_t B, uint8_t C);

void division(uint8_t A, uint8_t B, uint8_t C);

void bitwise_nand(uint8_t A, uint8_t B, uint8_t C);

void halt(Seq_T memory, Seq_T unmapped_seg_IDs);

void map_segment(Seq_T memory, Seq_T unmapped_seg_IDs, uint8_t B, uint8_t C);

void unmap_segment(Seq_T memory, Seq_T unmapped_seg_IDs, uint8_t C);

void output(uint8_t C);

void input(uint8_t C);

uint32_t load_program(Seq_T memory, uint8_t B, uint8_t C);

void load_value(uint8_t A, uint32_t value);

#endif

