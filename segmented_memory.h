#ifndef SEGMENTED_MEMORY_INCLUDED
#define SEGMENTED_MEMORY_INCLUDED

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <seq.h>
#include <uarray.h>
#include <stdbool.h>
#include <assert.h>

/*
 *      segmented_memory.h
 *
 *      Hazen Breen and Jordan Stone
 *
 *      This header file contains the function declarations for the functions
 *      relating to the segmented memory module.
 *
 */


Seq_T initialize_memory(uint32_t num_words);

Seq_T initialize_unmapped_seg_IDs();

uint32_t map(Seq_T memory, Seq_T unmapped_seg_IDs, uint32_t num_words);

void unmap(Seq_T memory, Seq_T unmapped_seg_IDs, uint32_t seg_ID);

void load_new_program(Seq_T memory, uint32_t seg_ID);

void store_word(Seq_T memory, uint32_t seg_ID, uint32_t word_index, 
	uint32_t word);

uint32_t load_word(Seq_T memory, uint32_t seg_ID, uint32_t word_index);

void free_memory(Seq_T memory, Seq_T unmapped_seg_IDs);


#endif
