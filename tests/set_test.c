#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../main.h"
#include "../set.h"
#include "../pack.h"
#include "../interface.h"


int main (void) {
    Set *test_set;
    char *test_pieces[] = {"1!", "1@", "1#", "1$"};
    /* new_set (test_set, false, test_pieces, 4); */
    show_set (test_set);
    return 0;

}
