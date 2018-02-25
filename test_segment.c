#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <except.h>

#include "segmented_memory.h"


/*
 *      test_segment.c
 *
 *      Hazen Breen and Jordan Stone
 *
 *      This file contains the testing routines for our segmented memory representation.
 *
 */



int main()
{
        fprintf(stderr, "Starting testing segmented memory \n\n"); 

        Seq_T mem = initialize_memory(15);
        Seq_T unmapped_seg_IDs = initialize_unmapped_seg_IDs();

        fprintf(stderr, "map test 1 start \n");

        uint32_t segment_ID = map(mem, unmapped_seg_IDs, 10);

        if (segment_ID == 1) {
                fprintf(stderr, "map test 1 passed. \n\n");
        } else {
                fprintf(stderr, "map test 1 failed. \n\n");
        }

/*************************************************************************/

        fprintf(stderr, "map test 2 start \n");

        segment_ID = map(mem, unmapped_seg_IDs, 5);

        if (segment_ID == 2) {
                fprintf(stderr, "map test 2 passed. \n\n");
        } else {
                fprintf(stderr, "map test 2 failed. \n\n");
        }

/*************************************************************************/
        fprintf(stderr, "unmap/map test 3 start \n");

        unmap(mem, unmapped_seg_IDs, 1);

        segment_ID = map(mem, unmapped_seg_IDs, 15);

        if (segment_ID == 1) {
                fprintf(stderr, "unmap/map test 3 passed. \n\n");
        } else {
                fprintf(stderr, "unmap/map test 3 failed. \n\n");
        }

/*************************************************************************/

        fprintf(stderr, "map test 4 start \n");

        segment_ID = map(mem, unmapped_seg_IDs, 5);

        if (segment_ID == 3) {
                fprintf(stderr, "map test 4 passed. \n\n");
        } else {
                fprintf(stderr, "map test 4 failed. \n\n");
        }

/*************************************************************************/
        fprintf(stderr, "store word test 5 \n" );

        uint32_t word = 4294967295;
        uint32_t seg_ID = 3;
        uint32_t word_index = 0;
        store_word(mem, seg_ID, word_index, word);

        uint32_t loaded_word = load_word(mem, seg_ID, word_index);


        if (word != loaded_word) {
                fprintf(stderr, "store/load test 5 failed. \n\n");
        } else if (word == loaded_word) {
                fprintf(stderr, "store/load test 5 passed. \n\n");
        }
        
/*************************************************************************/
        fprintf(stderr, "store word test 6 \n" );

        int i = 0;
        word = 4294967294;
        seg_ID = 3;
        word_index = 1;
        store_word(mem, seg_ID, word_index, word);

        loaded_word = load_word(mem, seg_ID, word_index);
        if (loaded_word != word)
        {
                fprintf(stderr, "store/load test 6 failed. \n\n");
        }
        i++;


        word = 4294967293;
        seg_ID = 3;
        word_index = 2;
        store_word(mem, seg_ID, word_index, word);

        loaded_word = load_word(mem, seg_ID, word_index);
        if (loaded_word != word)
        {
                fprintf(stderr, "store/load test 6 failed. \n\n");
        }
        i++;

        word = 4294967292;
        seg_ID = 3;
        word_index = 3;
        store_word(mem, seg_ID, word_index, word);

        loaded_word = load_word(mem, seg_ID, word_index);
        if (loaded_word != word)
        {
                fprintf(stderr, "store/load test 6 failed. \n\n");
        }
        i++;

        if (i == 3){
                fprintf(stderr, "store/load test 6 passed. \n\n");
        }

/*************************************************************************/
        fprintf(stderr, "load program test 7 \n" );


        load_new_program(mem, 3);

        i = 0;
        word = 4294967294;
        seg_ID = 0;
        word_index = 1;
        

        loaded_word = load_word(mem, seg_ID, word_index);
        if (loaded_word != word)
        {
                fprintf(stderr, "store/load test 7 failed. \n\n");
        }
        i++;


        word = 4294967293;
        word_index = 2;
       
        loaded_word = load_word(mem, seg_ID, word_index);
        if (loaded_word != word)
        {
                fprintf(stderr, "store/load test 7 failed. \n\n");
        }
        i++;

        word = 4294967292;
        word_index = 3;
        
        loaded_word = load_word(mem, seg_ID, word_index);
        if (loaded_word != word)
        {
                fprintf(stderr, "store/load test 7 failed. \n\n");
        }
        i++;

        if (i == 3) {
                fprintf(stderr, "store/load test 7 passed. \n\n");
        }
        
}
