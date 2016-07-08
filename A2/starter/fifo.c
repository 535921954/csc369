#include <stdio.h>
#include <assert.h>
#include <unistd.h>
#include <getopt.h>
#include <stdlib.h>
#include "pagetable.h"


extern int memsize;

extern int debug;

extern struct frame *coremap;

/* Page to evict is chosen using the fifo algorithm.
 * Returns the page frame number (which is also the index in the coremap)
 * for the page that is to be evicted.
 */
int fifo_evict() {

	int ev_page;
	int i;

	for (i = 0; i < memsize; i++) {
		if (coremap[i].fifo_place == 1) {
			ev_page = i;
			coremap[i].fifo_place = 0;
		}
		else if (coremap[i].fifo_place > 1) {
			coremap[i].fifo_place = coremap[i].fifo_place - 1;
		}
		coremap[i].fifo_max = coremap[i].fifo_max - 1;
	}

	return ev_page;
}

/* This function is called on each access to a page to update any information
 * needed by the fifo algorithm.
 * Input: The page table entry for the page that is being accessed.
 */
void fifo_ref(pgtbl_entry_t *p) {

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

/* Initialize any data structures needed for this
 * replacement algorithm
 */
void fifo_init() {

	int i;

	// Initialize all values of fifo_place to zero,
	// meaning they haven't been paged in.
	for (i = 0; i < memsize; i++) {
		coremap[i].fifo_place = 0;
		coremap[i].fifo_max = 1;
	}

}
