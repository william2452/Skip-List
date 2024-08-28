#include "skipList.h"
#include <malloc.h>

int main() {
	/* initialize list one - max depth 4 */
	int cap = 6;
	struct skipList *lst = malloc(sizeof(struct skipList) + sizeof(struct sLink)*cap);
	initSkipList(lst, cap);

	printf("--------------Testing levelGen--------------\n");
	printf("You need to eyeball this - ensure that levels do not break 'the rules'\n");
	printf("The level should never increase by more than 1 above the previous max and never exceed 5. Should go above 0.\n");

	int i = 0;
	while(i < 16) {
        printf("%d ", levelGen(lst));
        i++;
	}

	printf("\n\n");

	printf("------------------- Static Testing -------------------\n");
	printf("This is a scripted routine of inserts and levels - see the print to determine if it is working correctly\n");
	staticTest(lst);


	printf("--------------Dynamic Testing--------------\n");



	test();

	return 0;
}

/*
	staticTest: Function tests the addValTest, printLv and removeLink functions
	pre: lst is not null
	param1: lst - the list
	post: links are added to the list at varying levels
	post: results are displayed via standard output
*/
void staticTest(struct skipList *lst) {
	printf("\n-------------- Testing addValTest --------------\n");
	addValTest(lst, 2, 0);
	addValTest(lst, 6, 0);
	addValTest(lst, 4, 0);
	addValTest(lst, 5, 1);
	addValTest(lst, 10, 1);
	addValTest(lst, 3, 1);
	addValTest(lst, 7, 0);
	addValTest(lst, 8, 2);
	addValTest(lst, 15, 2);
    addValTest(lst, 9, 3);
	addValTest(lst, 13, 0);

	printf("\n-------------- Testing printLv --------------\n");
	printLv(lst, 0);
	/* should display: 2, 3, 4, 5, 6, 7, 8, 9, 10, 13, 15 */
	printLv(lst, 1);
	/* should display: 3, 5, 8, 9, 10, 15 */
	printLv(lst, 2);
	/* should display: 8, 9, 15 */
	printLv(lst, 3);
	/* should display: 9 */
    printf("Testing getSize(): %d\n", getSize(lst) == 11);

	printf("\n-------------- Testing searchVal --------------\n");
	printf("Search for 4: returned: %d \n", searchVal(lst,4));
	printf("Search for 1: returned: %d \n", searchVal(lst,1));
	printf("Search for 15: returned: %d \n", searchVal(lst,15));

	printf("\n-------------- Testing removeLink --------------\n");
	printf("Removing 2 from list \n");
	removeLink(lst, 2);

	printLv(lst, 0);
	/* should display: 3, 4, 5, 6, 7, 8, 9, 10, 13, 15 */
	printLv(lst, 1);
	/* should display: 3, 5, 8, 9, 10, 15 */
	printLv(lst, 2);
	/* should display: 8, 9, 15 */
	printLv(lst, 3);
	/* should display: 9 */
    printf("Testing getSize(): %d\n\n", getSize(lst) == 10);

	printf("Removing 5 from list \n");
	removeLink(lst, 5);

	printLv(lst, 0);
	/* should display: 3, 4, 6, 7, 8, 9, 10, 13, 15 */
	printLv(lst, 1);
	/* should display: 3, 8, 9, 10, 15 */
	printLv(lst, 2);
	/* should display: 8, 9, 15 */
	printLv(lst, 3);
	/* should display: 9 */
    printf("Testing getSize(): %d\n\n", getSize(lst) == 9);

	deleteList(lst);

	printf("List deleted\n");

	printf("\n--------------Testing Complete--------------\n");

}

/*
	Function: test tests the addVal, printLv and removeLink functions with a random, large set of values and levels
    param1: lst - the list
	pre: list is not null
	post: links are added to the list at varying levels
	post: results are displayed via standard output
*/
void test() {

    /* initialize list two - max depth 8 */
	int cap = 8;
	struct skipList *lst;
	lst = malloc(sizeof(struct skipList) + sizeof(struct sLink)*cap);
	initSkipList(lst, cap);

	int i = 0;

	while(i < 25) {
		addVal(lst, rand()%100);
		i++;
	}

	printLv(lst, 0);
	printLv(lst, 1);
	printLv(lst, 2);
	printLv(lst, 3);
	printLv(lst, 4);
	printLv(lst, 5);
	printLv(lst, 6);
	printLv(lst, 7);

	printf("Search for 50: returned: %d \n", searchVal(lst, 50));
	printf("Search for 1: returned: %d \n", searchVal(lst, 1));
	printf("Search for 76: returned: %d \n", searchVal(lst, 76));
	/* Verify your own results */
}
