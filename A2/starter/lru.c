#include <stdio.h>
#include <assert.h>
#include <unistd.h>
#include <getopt.h>
#include <stdlib.h>
#include <limits.h>
#include "pagetable.h"


extern int memsize;

extern int debug;

extern struct frame *coremap;

pgtbl_entry_t *lru_pte;
unsigned long max_timestamp;

/* Page to evict is chosen using the accurate LRU algorithm.
 * Returns the page frame number (which is also the index in the coremap)
 * for the page that is to be evicted.
 */

int lru_evict() {
	pgtbl_entry_t *old_lru_pte = lru_pte;
	pgtbl_entry_t *current;

	int i;
	int frame;
	unsigned long min = ULONG_MAX;

	for (i = 0; i < memsize; i++) {
		current = coremap[i].pte;
		if (current->frame & PG_VALID) {
			if (current != old_lru_pte) {
				if (current->timestamp < min) {
					min = current->timestamp;
					lru_pte = current; // the new minimum
				}
			}
		}
		if (current == old_lru_pte) {
			frame = i;
		}
	}

	return frame;
}

/* This function is called on each access to a page to update any information
 * needed by the lru algorithm.
 * Input: The page table entry for the page that is being accessed.
 */
void lru_ref(pgtbl_entry_t *p) {
	if (lru_pte == NULL) {
		lru_pte = p;
	}
	p->timestamp = max_timestamp;
	max_timestamp++;
	// Catching overflows
	if (max_timestamp == ULONG_MAX) {
		perror("lru.c: max_timestamp reached overflow");
		exit(1);
	}

	return;
}


/* Initialize any data structures needed for this
 * replacement algorithm
 */
void lru_init() {
	lru_pte = NULL;
	max_timestamp = 0;
}
