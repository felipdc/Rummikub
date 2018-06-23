#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "pack.h"
#include "main.h"
#include "set.h"
#include "interface.h"


void new_set (Set *set, Hand *Player, bool is_run, char *pieces[2], unsigned num_of_pieces) {
    
    Set *aux_set = set;

    if (is_new_set_possible (is_run, pieces, num_of_pieces) == false) {
        printf ("Jogada invalida");
        return;
    }

    // Verifica se eh o primeiro set do jogo
    if (set == NULL) {
        aux_set = malloc (sizeof(Set));
        aux_set->run = is_run;
        aux_set->num_of_pieces = num_of_pieces;
        aux_set->next = NULL;
    }

    // Insere as pecas no set
    for (int i = 0; i < num_of_pieces; ++i) {
        aux_set->set_piece[i][0] = pieces[i][0];
        aux_set->set_piece[i][1] = pieces[i][1];
    }
}

