#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "main.h"
#include "pack.h"
#include "set.h"
#include "interface.h"


int main (void) {
    Set *test_set = NULL;
    char *test_pieces[] = {"1!", "1@", "1#", "1$"};
    test_set = new_set (test_set, false, test_pieces, 4);
    for (int i = 0; i < 4; ++i) {
        printf ("%s\n", test_set->set_piece[i]);
    }
    return 0;
}
