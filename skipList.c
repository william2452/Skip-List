/*
William McClean
CS 260
Assignment 5
20 October 2022
*/
#include "skipList.h"
#include <malloc.h>
#include <time.h>

/*
	skip list implementation
*/


/*
	initSkipList: Skiplist is initialized - memory is allocated for the sentinel
	param1: lst - the list
	param2: maxLvl - maximum depth of the list
	pre: lst is not null
    pre: maxLvl is greater than 0
    post: rand() has been seeded
	post: memory is allocated to sentinel
	post: sentinel->next points to lst->sentinel at every level
	post: maxLevel is set to maxLvl - should be log n(size of list)
	post: currMax is set to 0
	post: size is set to 0
*/
void initSkipList(struct skipList *lst, int maxLvl) {
	assert(lst != NULL);
	assert(maxLvl > 0);

    srand(time(NULL));

	lst->sentinel = malloc(sizeof(struct sLink)+sizeof(struct sLink)*maxLvl);/* sentinel is an array with a pointer to every level */

    int i;
	for(i = 0; i < maxLvl; i++) {
		lst->sentinel->next[i] = lst->sentinel;/* sentinel points to the sentinel at every level */
	}

	lst->maxLevel = maxLvl;/* max allowable levels */
	lst->currMax = 0;/* level of highest node currently */
	lst->size = 0;/* number of level 1 links */

}


/*
	levelGen: Generate a random level for new links - probabilistically determined
	param1: lst - the list
	return: random level from 0 to lst->maxLevel - 1
	pre: lst is not null

	HINT: random levels are determined by a "series of coin flips"
	HINT: Each level is 50% less common than the last
	HINT: Approximately 50% are level 2, 25% are level 3, 12.5% are level 4, etc
	HINT: Each consecutive "heads" adds one to the level, at the first "tails" we have reached our level

	HINT: start at level 0 and add 1 for each heads
	HINT: level is capped at maxLevel - 1
	HINT: level can only exceed currMax by 1 - currMax will need to get incremented in this case

	Ex: HHT = level 2, T = 0, THH = 0, HHHT = 3
*/
int levelGen(struct skipList *lst) {
	/* FIX ME */
    assert(lst != NULL);

    int level = 0;

    while(rand() %2 == 0 && level < lst -> maxLevel) {
        level++;
    }
    if(level > lst -> currMax) {
        lst -> currMax++;
        level = lst -> currMax;
    }
    if(level > lst -> maxLevel) {
        level = lst -> maxLevel;
    }

	return level;
}

/*
slideRight traverses a skip list and returns the node before the value being searched for.
param 1 - struct skipList *lst = the skip list being passed to the function.
param 2 - TYPE val = the value to be searched for.
param 3 - int lvl = the level of node in the skip list.
param 4 - struct sLink *curr = the node where slide right starts rather than all the way at sentinel.
*/
struct sLink* slideRight(struct skipList *lst, TYPE val, int lvl, struct sLink *curr) {
    /*FIX ME*/
    assert(lst != NULL);

    int i = lvl;
    while(curr -> next[i] != lst -> sentinel && curr -> next[i] -> value < val) {
        curr = curr -> next[i];
    }
    return curr;
}


/*
	addValTest: Adds a new sLink to the skipList at a specified level - for testing purposes
	param1: lst - the list
	param2: val - the value to add
	param3: lvl - the level of the link
	pre: lst is not null
	pre: lvl >= 0
	pre: lvl < maxLevel
	post: memory has been allocated to the new skip link
	post: value has been set for the new skip link
	post: pointers have been adjusted at each necessary level
	post: a new sLink is added to the skip list and pointers are adjusted at each necessary level
	post: compare each node's level to the currMax and adjust the currMax as needed - this is only in the test function
*/
void addValTest(struct skipList *lst, TYPE val, int lvl) {
	assert(lst != NULL);
	assert(lvl < lst->maxLevel);
	assert(lvl >= 0);

	/* Allocate memory for link to insert - extra space is allocated for the "height" of the link +1 (in case it is zero)*/
	struct sLink *insert = malloc(sizeof(struct sLink) + sizeof(struct sLink)*lvl+1);
	insert->value = val;
	insert->level = lvl;

	/* Iterator node pointer*/
	struct sLink *curr = lst->sentinel;

	printf("inserting %d as a lvl %d node\n", val, lvl);

	/* FIX ME */
	/* Adjust pointers at each applicable level of the skip list less or equal to the link's level */
    /* HINT: Start at the top and work down */
    /* HINT: Slide to the right until you find the right position to drop down */
	/* HINT: Don't hesitate to put debugging statements in to help navigate the skip list Ex - slide, drop, etc*/

    if(insert -> level > lst -> currMax) {
        lst -> currMax++;
        insert -> level = lst -> currMax;
    }
    int i;
	for(i = insert -> level; i >= 0; i--) {
        curr = slideRight(lst, val, i, curr);
        insert -> next[i] = curr -> next[i];
        curr -> next[i] = insert;
	}
	lst -> size++;

}

/*
	addVal: Adds a new sLink to the skipList at a random level and maintains the skip list
	param1: lst - the list
	param2: val - the value to add
	pre: lst is not null
	post: memory has been allocated to the new skip link
	post: value has been set for the new skip link
	post: pointers have been adjusted at each necessary level
	post: a new sLink is added to the skip list and pointers are adjusted at each necessary level - level is generated randomly

	HINT - this is the same process as addValTest with one exception - you need to generate a level using LevelGen()
*/
void addVal(struct skipList *lst, TYPE val) {
	/* FIX ME */

  int lvl = levelGen(lst);
	struct sLink *insert = malloc(sizeof(struct sLink) + sizeof(struct sLink)*lvl+1);
	insert->value = val;
	insert->level = lvl;
	struct sLink *curr = lst->sentinel;

    int i;
	for(i = insert -> level; i >= 0; i--) {
        curr = slideRight(lst, val, i, curr);
        insert -> next[i] = curr -> next[i];
        curr -> next[i] = insert;
	}
	lst -> size++;


}


/*
	printLv: Print the specified level of the list
	param1: lst - the list
	param2: lv - level of the list to print
	pre: lst is not null
	pre: lv is greater than 0 and less than list->maxLevel
	post: prints all of the values at a specified level separated by a space - line break at the end
*/
void printLv(struct skipList *lst, int lv) {
	printf("Level %d: ", lv);
	/* FIX ME */
    assert(lst != NULL);
    assert(lv >= 0 && lv < lst -> maxLevel);

    struct sLink *curr = lst -> sentinel -> next[lv];

    while(curr != lst -> sentinel) {
        printf("%i, ", curr -> value);
        curr = curr -> next[lv];
    }

    printf("\n");
}


/*
	searchVal: Searches the skipList for a value
	param1: lst - the list
	param2: val - the search value
    pre: lst is not null
	return: return 1 if found - If not found, return 0
	HINT - traversing the list is similar to the an insert - start at currMax and slide right and down
*/
int searchVal(struct skipList *lst, TYPE val) {
    assert(lst != 0);
	printf("Searching for: %d\n", val);
	/* FIX ME */

	struct sLink *curr = lst -> sentinel;

	int i;
	for(i = lst -> currMax; i >= 0; i--) {
        curr = slideRight(lst, val, i, curr);
        if(curr -> next[i] -> value == val) {
            return 1;
        }
	}
    return 0;
}


/*
	removeLink: Remove the first instance of the link containing the value from the list and maintains the skip list
	param1: lst - the list
	param2: val - value to remove
	pre: lst is not null
    pre: val is in the list
	post: pointers are adjusted at each relevant level
	post: sLink is freed from the list (after pointers are adjusted at each level)

	HINT: Start at the top and search for the value on that level
	HINT: You have to visit each level from the start because you don't know anything about the previous nodes' pointers
	HINT: Each level of pointers needs to be adjusted as applicable
	HINT: Print statements displaying slides and dropping down a level might help to see what is happening
	HINT: This is probably the most difficult function
*/
void removeLink(struct skipList *lst, TYPE val) {
	/* FIX ME */
    assert(lst != NULL);
    assert(searchVal(lst, val) == 1);

    struct sLink *curr = lst -> sentinel;
    struct sLink *freeNode = curr;

    int i;
    for(i = lst -> currMax; i >= 0; i--) {
        curr = slideRight(lst, val, i, curr);
        if(curr -> next[i] -> value == val) {
            freeNode = curr -> next[i];
            curr -> next [i] = curr -> next[i] -> next[i];

        }
    }
    free(freeNode);
    freeNode = 0;

    lst -> size--;
}


/*
	getSize: return the number of level 1 links in the skip list
	param1: lst - the list
	pre: lst is not null
	post: return the number of level 0 links in the list
*/
int getSize(struct skipList *lst) {
	/* FIX ME */
    assert(lst != 0);

	return lst->size;
}


/*
	deleteList: memory is freed for the skip list
    param1: lst - the list
	pre: lst is not null
	post: lst is freed
	post: sLinks are freed
    HINT: all of the links are at level 0
*/
void deleteList(struct skipList *lst) {
	/* FIX ME */
    assert(lst != 0);

    struct sLink *curr = lst -> sentinel;
    struct sLink *freeNode = curr;
    int lvl = 0;
    while(curr -> next[lvl] != lst -> sentinel) {
        freeNode = curr;
        curr = curr -> next[lvl];
        free(freeNode);
        freeNode = 0;
    }
    free(lst);
    lst = 0;
}
