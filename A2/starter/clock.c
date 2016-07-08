#include <stdio.h>
#include <assert.h>
#include <unistd.h>
#include <getopt.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "pagetable.h"


extern int memsize;

extern int debug;

extern struct frame *coremap;

// Initialize clock hand
int hand;
// Record referenced frames in here
bool* clk_referenced;

/* Page to evict is chosen using the clock algorithm.
 * Returns the page frame number (which is also the index in the coremap)
 * for the page that is to be evicted.
 */

int clock_evict() {
	// Starting from hand, search for the first unreferenced bit
	int i;
	for (i = hand; i < memsize; i = (i + 1) % memsize) {
		// Invert reference bit
		if (clk_referenced[i]) {
			clk_referenced[i] = 0;
		} else {
			// Found the unreferenced frame; update hand for the next run
			clk_referenced[i] = 1;
			hand = i;
			return i;
		}
	}
	// Shouldn't return 0, but here to maybe remove a warning
	return 0;
}

/* This function is called on each access to a page to update any information
 * needed by the clock algorithm.
 * Input: The page table entry for the page that is being accessed.
 */
void clock_ref(pgtbl_entry_t *p) {
	int frame = p->frame >> PAGE_SHIFT;
	clk_referenced[frame] = 1;
}

/* Initialize any data structures needed for this replacement
 * algorithm.
 */
void clock_init() {
	hand = 0;
	clk_referenced = malloc(sizeof(bool) * memsize);
	memset(clk_referenced, 0, sizeof(bool) * memsize);
}
