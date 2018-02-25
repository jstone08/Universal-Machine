#include "ALU.h"
/*
 *      ALU.c
 *
 *      Hazen Breen and Jordan Stone
 *
 *      This source file contains the function definitions for the UM 
 *      instructions module.
 *
 */

uint32_t reg[8];
#define MAX_VAL 4294967295

/* moves reg[B] into reg[A] if reg[C] != 0  */
void conditional_move(uint8_t A, uint8_t B, uint8_t C)
{
        if (reg[C] != 0) {
                reg[A] = reg[B];
        }    
}

/* loads a word from a segment of memory */
void segmented_load(Seq_T memory, uint8_t A, uint8_t B, uint8_t C)
{
        reg[A] = load_word(memory, reg[B], reg[C]);
}

/* stores a word into a segment of memory */
void segmented_store(Seq_T memory, uint8_t A, uint8_t B, uint8_t C)
{
        store_word(memory, reg[A], reg[B], reg[C]);
}

/* adds reg[B] and reg[C] and stores the sum in reg[A] */
void add(uint8_t A, uint8_t B, uint8_t C)
{       
        reg[A] = (reg[B] + reg[C]);
}

/* multiplies reg[B] and reg[C] and stores the product in reg[A] */
void multiply(uint8_t A, uint8_t B, uint8_t C)
{
        reg[A] = (reg[B] * reg[C]); 
}

/* divides reg[B] by reg[C] and stores the quotient in reg[A] */
void division(uint8_t A, uint8_t B, uint8_t C)
{
        assert(reg[C] != 0);
        reg[A] = (reg[B] / reg[C]);
}

/* not ands reg[B] and reg[C] and stores the reuslt in reg[A] */
void bitwise_nand(uint8_t A, uint8_t B, uint8_t C)
{
        reg[A] = ~(reg[B] & reg[C]);
}

/* stops the program and frees memory usage */
void halt(Seq_T memory, Seq_T unmapped_seg_IDs)
{
        free_memory(memory, unmapped_seg_IDs);
        exit(EXIT_SUCCESS);   
}

/* creates segment with reg[C] elements and stores the segment ID in reg[B] */
void map_segment(Seq_T memory, Seq_T unmapped_seg_IDs, uint8_t B, uint8_t C)
{        
        reg[B]= map(memory, unmapped_seg_IDs, reg[C]);
}

/* unmaps segment at segment ID reg[C] */
void unmap_segment(Seq_T memory, Seq_T unmapped_seg_IDs, uint8_t C)
{
        unmap(memory, unmapped_seg_IDs, reg[C]);
}

/* value in reg[C] displayed on I/0 Device */
void output(uint8_t C)
{
        uint32_t value = reg[C];
        fputc(value, stdout);
}

/* when input arrives from I/0 Device, word is written to reg[C] */
void input(uint8_t C)
{
        uint32_t val = fgetc(stdin);
        if (val <= 255) {
                reg[C] = val;
        } else {
                reg[C] = MAX_VAL;
        }
}

/* segment with segment ID reg[B] is copied and placed into the zero segment
   the program counter is set to reg[C]                                     */
uint32_t load_program(Seq_T memory, uint8_t B, uint8_t C)
{
        load_new_program(memory, reg[B]);
        return reg[C];
}

/* places value into reg[A] */
void load_value(uint8_t A, uint32_t value)
{
        reg[A] = value;
}

