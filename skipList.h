#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <assert.h>

#define TYPE int

struct sLink {
    TYPE value;
    int level;
    struct sLink *next[1];
};

struct skipList {
    int maxLevel;
    int currMax;
    int size;
    struct sLink *sentinel;
};

void initSkipList(struct skipList *lst, int maxLvl);
int levelGen(struct skipList *lst);
void addValTest(struct skipList *lst, TYPE val, int lvl);
void addVal(struct skipList *lst, TYPE val);
int searchVal(struct skipList *lst, TYPE val);
void printLv(struct skipList *lst, int lv);
int getSize(struct skipList *lst);
void removeLink(struct skipList *lst, TYPE val);
void deleteList(struct skipList *lst);
void staticTest(struct skipList *lst);
void test();
