#include "segmented_memory.h"
#include <mem.h>
/*
 *      sim_mem.c
 *
 *      Hazen Breen and Jordan Stone
 *
 *      This header file contains the function declarations for the functions
 *      relating to the segmented memory module.
 */


void mark_unmap(Seq_T unmapped_seg_IDs, uint32_t seg_ID);

uint32_t find_next_seg_ID();

void copy_segment(UArray_T segment, UArray_T seg_copy, uint32_t length);


/* Name: initialize_memory
 * Purpose: This function is responsible for creating the representation 
 *          of main memory and initializing the zero segment.
 */
Seq_T initialize_memory(uint32_t num_words)
{
        Seq_T memory = Seq_new(800000);

        UArray_T segment0 = UArray_new(num_words, sizeof(uint32_t));

        Seq_addhi(memory, segment0);
        
        return memory;
}

Seq_T initialize_unmapped_seg_IDs()
{
        return Seq_new(1);
}

/* Name: map
 * Purpose: This function is responsible for creating a segment at the next 
 *          avaliable segment ID. The length of the segment is determined 
 *          by the second argument.
 */
uint32_t map(Seq_T memory, Seq_T unmapped_seg_IDs, uint32_t num_words)
{
        UArray_T segment = UArray_new(num_words, sizeof(uint32_t));

        uint32_t seg_ID;

        if (Seq_length(unmapped_seg_IDs) != 0) {
                seg_ID =  ((uint32_t)(uintptr_t) Seq_remhi(unmapped_seg_IDs));
                Seq_put(memory, seg_ID, segment);
                return seg_ID;
        } else {
                Seq_addhi(memory, segment);
                return Seq_length(memory) - 1;
        }
}

/* Name: unmap
 * Purpose: This function is responsible for unmapping a segment.
 */
void unmap(Seq_T memory, Seq_T unmapped_seg_IDs, uint32_t seg_ID)
{
        assert(seg_ID != 0);
        UArray_T segment = (UArray_T) Seq_get(memory, seg_ID);
        assert(segment != NULL);
        UArray_free(&segment);
        mark_unmap(unmapped_seg_IDs, seg_ID);
}

/* Name: load_new_program
 * Purpose: This function is responsible for copying the segment with 
 *          segment ID, "seg_ID" and placing the copy in segment zero. 
 */
void load_new_program(Seq_T memory, uint32_t seg_ID)
{
        if (seg_ID == 0) {
                return;
        }

        
        UArray_T segment0 = (UArray_T) Seq_get(memory, 0);
        UArray_free(&segment0);

        UArray_T segment = ((UArray_T) Seq_get(memory, seg_ID));
        assert(segment != NULL);
        
        uint32_t length = UArray_length(segment);
        UArray_T seg_copy = UArray_new(length, sizeof(uint32_t));

        copy_segment(segment, seg_copy, length);

        Seq_put(memory, 0, seg_copy);
}

/* Name: load_word
 * Purpose: This function is responsible for retrieving a word from a specified
 *          segment with a specified word within the segment.
 */
uint32_t load_word(Seq_T memory, uint32_t seg_ID, uint32_t word_index)
{
        assert(seg_ID < (uint32_t) Seq_length(memory));

        assert(word_index < (uint32_t) UArray_length((UArray_T) 
                Seq_get(memory, seg_ID)));

        UArray_T segment = (UArray_T) Seq_get(memory, seg_ID); 
        return (*(uint32_t *) UArray_at(segment, word_index));
}

/* Name: store_word
 * Purpose: This function is responsible for storing a word at specified 
 *          segment ID at a specifed word within the segment. 
 */
void store_word(Seq_T memory, uint32_t seg_ID, uint32_t word_index, 
        uint32_t word)
{
        assert(seg_ID < (uint32_t) Seq_length(memory));

        assert(word_index < (uint32_t) UArray_length((UArray_T) 
                Seq_get(memory, seg_ID)));

        void *empty_segment = Seq_get(memory, seg_ID);
        UArray_T segment = (UArray_T) empty_segment;

        *(uint32_t *) UArray_at(segment, word_index) = word;
}

/* Name: mark_unmap
 * Purpose: This function is responsible for marking a segment ID to keep 
 *          track of segment ID's that have been unmapped. This allows for 
 *          previously unmapped segment ID's to be reused which will aid in 
 *          space complexity.
 */
void mark_unmap(Seq_T unmapped_seg_IDs, uint32_t seg_ID)
{
        Seq_addhi(unmapped_seg_IDs, (void *)(uintptr_t)seg_ID);
}

/* Name: copy_segment
 * Purpose: This function is performs a copy of the elements up to 
 *          index "length" of a segment into another segment.
 */
void copy_segment(UArray_T seg_orig, UArray_T seg_copy, uint32_t length)
{
        for (uint32_t i = 0; i < length; i++) {
                (*(uint32_t *) UArray_at(seg_copy, i)) = 
                        (*(uint32_t *) UArray_at(seg_orig, i));
        }

}

/* Name: free_memory
 * Purpose: This function is responsible for freeing the segmented memory 
 *          representation, as well as the individual elements. 
 */
void free_memory(Seq_T memory, Seq_T unmapped_seg_IDs)
{
        uint32_t mem_length = Seq_length(memory);
        uint32_t unmapped_length = Seq_length(unmapped_seg_IDs);
        UArray_T segment;
        bool is_unmapped = false;

        for (uint32_t i = 0; i < mem_length; i++) {
                for (uint32_t j = 0; j < unmapped_length; j++) {
                        if (i == (uint32_t)(uintptr_t)Seq_get(unmapped_seg_IDs,
                                         j)) {
                                is_unmapped = true;  
                        }
                }
                if (is_unmapped) {
                        is_unmapped = false;
                        continue;
                }
                segment = Seq_get(memory, i);
                UArray_free(&segment);
        }

        Seq_free(&memory);
        Seq_free(&unmapped_seg_IDs);
}
