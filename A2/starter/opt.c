#include <stdio.h>
#include <assert.h>
#include <unistd.h>
#include <getopt.h>
#include <stdlib.h>
#include "pagetable.h"


extern int memsize;

extern int debug;

extern struct frame *coremap;

/* Page to evict is chosen using the optimal (aka MIN) algorithm. 
 * Returns the page frame number (which is also the index in the coremap)
 * for the page that is to be evicted.
 */
int opt_evict() {

	int ev_page; 
	int i; 
	int j; 
	int nru_switch = 0; //To check if the other classes need to be checked.
	int nru_stage = 0; // goes in order: 0, 2, 1, 3. 
	int curr_fifo = -1; 
	int old_fifo; 

	for (i = 0; i < memsize; i++) {
		if ((((coremap[i].pte)->frame) >> 30) == nru_stage) {
			//Find a frame in this nru class. 
			if (curr_fifo == -1) {			
				ev_page = i; 
				old_fifo = coremap[i].fifo_place; 
				coremap[i].fifo_place = 0; 
				nru_switch = 1; 
			}
			//Find a frame with the lowest fifo value. 
			else {
				coremap[ev_page].fifo_place = old_fifo - 1;
				ev_page = i; 
				old_fifo = coremap[i].fifo_place; 
				coremap[i].fifo_place = 0;  
			}
		}
		//Decrease the values of all fifo places premptively. 
		else if (coremap[i].fifo_place > 1) {
			coremap[i].fifo_place = coremap[i].fifo_place - 1; 		
		}
		//Decrese fifo_max of all by one. 
		coremap[i].fifo_max = coremap[i].fifo_max - 1; 
	}

	nru_stage = 2; 	

	for (j = 0; j < 3; j++) { 
		if (nru_switch == 0) {
			for (i = 0; i < memsize; i++) {
				if ((((coremap[i].pte)->frame) >> 30) == nru_stage) {
					//Find a frame in this nru class. 
					if (curr_fifo == -1) {			
						ev_page = i; 
						old_fifo = coremap[i].fifo_place; 
						coremap[i].fifo_place = 0; 
						nru_switch = 1; 
					}
					//Find a frame with the lowest fifo value. 
					else {
						coremap[ev_page].fifo_place = old_fifo - 1;
						ev_page = i; 
						old_fifo = coremap[i].fifo_place; 
						coremap[i].fifo_place = 0;  
					}
				}
			}
			if (nru_stage == 2) {
				nru_stage = 1; 
			}
			else {
				nru_stage = 3; 			
			}	
		}
	}
	
	return ev_page;
}

/* This function is called on each access to a page to update any information
 * needed by the opt algorithm.
 * Input: The page table entry for the page that is being accessed.
 */
void opt_ref(pgtbl_entry_t *p) {

	int i; 

	//Check if the page is in a frame.
	if ((((p-> frame) >> 29) & 1) == 1) {
		for (i = 0; i < memsize; i++) {
			if(coremap[i].pte == p) {
				//Check if this is the first time the page is accessed in a frame.
				if (coremap[i].fifo_place == 0) {
					coremap[i].fifo_place = coremap[i].fifo_max;  
				}
			}
			coremap[i].fifo_max = coremap[i].fifo_max + 1; 
		}		
	}
}

/* Initializes any data structures needed for this
 * replacement algorithm.
 */
void opt_init() {

	int i;  

		//Initialize all values of fifo_place to zero,
		//meaning they haven't been paged in.
		for (i = 0; i < memsize; i++) {
			coremap[i].fifo_place = 0; 
			coremap[i].fifo_max = 1; 
		}

}


