#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../main.h"
#include "../pack.h"
#include "../set.h"
#include "../interface.h"


int main (void) {
    Set *test_set1 = NULL;
    Set *test_set2 = NULL;
    Set *test_set3 = NULL;
    Set *test_set4 = NULL;
    Set *test_set5 = NULL;
    char *test_pieces[] = {"1!", "1@", "1#", "**"};
    char *test_pieces_2[] = {"4$", "4#", "4@", "4!"};
    char *test_pieces_3[] = {"3$", "3!", "**", "**"};
    char *test_pieces_4[] = {"9!", "A!", "B!", "C!"};
    char *test_pieces_5[] = {"**", "**", "C!",  "D!"};
    test_set1 = new_set (test_set1, false, test_pieces, 4);
    test_set2 = new_set (test_set2, false, test_pieces_2, 4);
    test_set3 = new_set (test_set3, false, test_pieces_3, 4);
    test_set4 = new_set (test_set4, true, test_pieces_4, 4);
    test_set5 = new_set (test_set5, true, test_pieces_5, 4);
    if (test_set1 == NULL) {
        printf ("Conjunto 1 nao passou no teste\n");
    }
    if (test_set2 == NULL) {
        printf ("Conjunto 2 nao passou no teste\n");
    }
    if (test_set3 == NULL) {
        printf ("Conjunto 3 nao passou no teste\n");
    }
    if (test_set4 == NULL) {
        printf ("Conjunto 4 nao passou no teste\n");
    }
    else {
        printf ("Todos os conjuntos de pecas passaram no teste\n");
    }
} 
