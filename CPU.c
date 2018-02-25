#include <stdlib.h>
#include <stdint.h>
#include "segmented_memory.h"
#include "ALU.h"
#include <uarray.h>
#include <assert.h>
#include <bitpack.h>
#include <sys/stat.h>

/*
 *      CPU.c
 *
 *      Hazen Breen and Jordan Stone 
 *
 *      This source file acts as the central processing unit for the 
 *      universal machine. It will read in the UM instruction file and store 
 *      the instructions in the zero segment in the representation of 
 *      segmented memory. After, the CPU will read the instructions and 
 *      interpret them to call the necessary functions in the arithmetic logic
 *      unit to perform the correpsonding actions. 
 *
 */

#define MAX_VAL 4294967295

typedef enum Um_opcode {
        CMOV = 0, SLOAD, SSTORE, ADD, MUL, DIV,
        NAND, HALT, ACTIVATE, INACTIVATE, OUT, IN, LOADP, LV
} Um_opcode;

void read_program(FILE *fp, Seq_T memory); 
void run_program(Seq_T memory);
uint32_t pick_function(Seq_T memory,  Seq_T unmapped_seg_IDs, uint32_t word,
                uint32_t program_counter);


int main(int argc, char *argv[]) 
{
        /* reading command line */
        if (argc != 2) {
                fprintf(stderr, "No UM program given\n");
                exit(EXIT_FAILURE);
        }
        FILE *fp = fopen(argv[1], "r");
        if (fp == NULL) {
                fprintf(stderr, "No UM program given\n");
                exit(EXIT_FAILURE);
        }

        struct stat data;
        stat(argv[1], &data);
        uint32_t num_words = data.st_size / 4;
        Seq_T memory = initialize_memory(num_words + 1);  

        read_program(fp, memory);

        fclose(fp);

        run_program(memory);
}

/* Name: read_program
 * Purpose: This function is responsible for reading the UM instructions and
 *          storing the instructions in the zero segment.
 */
void read_program(FILE *fp, Seq_T memory) 
{
        int byte = fgetc(fp);
        uint8_t iter = 4;
        uint64_t word = 0;
        uint32_t num_words = 0;
        uint32_t *empty;
        UArray_T segment = Seq_get(memory, 0);

        while ((byte <= 255) && (byte >= 0)) {
                iter--;
                
                word = Bitpack_newu(word, 8, (iter * 8), byte); 

                if (iter == 0) {
                        empty =  UArray_at(segment, num_words);
                        *empty = (uint32_t) word;
                        iter = 4;
                        word = 0;
                        num_words++;
                }

                byte = fgetc(fp);
        }

        word = MAX_VAL;
        empty =  UArray_at(segment, num_words);
        *empty = (uint32_t) word;  
}

/* Name: run_program
 * Purpose: This function is responsible for looping through all instructions 
 *          in the zero segment and calling the appropriate UM instructions. 
 */
void run_program(Seq_T memory)
{
        /* fetch */
        uint32_t word = 0;
        uint32_t program_counter = 0;
        Seq_T unmapped_seg_IDs = initialize_unmapped_seg_IDs();    


        while (word != MAX_VAL) {
                UArray_T segment = Seq_get(memory, 0);

                word = *(uint32_t *) UArray_at(segment, program_counter);
                
                program_counter = pick_function(memory, unmapped_seg_IDs, word, 
                        program_counter);

                assert(program_counter < 
                        (uint32_t)UArray_length((UArray_T) Seq_get(memory, 0)));
        }
}

/* Name: pick_function
 * Purpose: This function is responsible for specifying which UM instruction 
 *          should be called. It also gets the appropriate information from 
 *          the word to be passed in to the instruction.
 */
uint32_t pick_function(Seq_T memory, Seq_T unmapped_IDs, uint32_t word, 
        uint32_t program_counter)
{
        Um_opcode opcode = Bitpack_getu(word, 4, 28);
        assert(opcode < 14);
        
        uint8_t A, B, C;
        uint32_t value;

        A = Bitpack_getu(word, 3, 6);
        B = Bitpack_getu(word, 3, 3);
        C = Bitpack_getu(word, 3, 0);

        switch (opcode) {
                case CMOV:       conditional_move(A, B, C);               break;
                case SLOAD:      segmented_load(memory, A, B, C);         break;
                case SSTORE:     segmented_store(memory, A, B, C);        break;
                case ADD:        add(A, B, C);                            break;
                case MUL:        multiply(A, B, C);                       break;
                case DIV:        division(A, B, C);                       break;
                case NAND:       bitwise_nand(A, B, C);                   break;
                case HALT:       halt(memory, unmapped_IDs);              break;
                case ACTIVATE:   map_segment(memory, unmapped_IDs, B, C); break;
                case INACTIVATE: unmap_segment(memory, unmapped_IDs, C);  break;
                case OUT:        output(C);                               break;
                case IN:         input(C);                                break;
                case LOADP:   
                        return load_program(memory, B, C);
                case LV:
                        A = Bitpack_getu(word, 3, 25);
                        value = Bitpack_getu(word, 25, 0);
                        load_value(A, value);
                        break;
        }
        return ++program_counter;
}

