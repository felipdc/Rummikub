#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "pack.h"
#include "main.h"
#include "set.h"
#include "interface.h"


static unsigned get_piece_number (char piece[]) {
    return strtol (piece, NULL, 16);
}


static Color get_piece_color (char piece[]) {
    if (piece[1] == '!') return blue;
    if (piece[1] == '@') return yellow;
    if (piece[1] == '#') return black;
    if (piece[1] == '$') return red;
    if (piece[1] == '*') return none;
}


void new_set (Set *set, Hand *Player, bool is_run, char *pieces[], unsigned num_of_pieces) {
    
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

        // Insere as novas pecas
        for (int i = 0; i < num_of_pieces; ++i) {
            aux_set->set_piece[i][0] = pieces[i][0];
            aux_set->set_piece[i][1] = pieces[i][1];
        }
        return;
    } // Else
    
    // Avanca ate a ultima lista de set
    while (aux_set->next == NULL) {
        aux_set = aux_set->next;
    }

    // Aloca memoria para um novo set
    aux_set->next = malloc (sizeof(Set));
    aux_set = aux_set->next;    // Muda para o novo set

    // Insere as pecas no set
    for (int i = 0; i < num_of_pieces; ++i) {
        aux_set->set_piece[i][0] = pieces[i][0];
        aux_set->set_piece[i][1] = pieces[i][1];
    }
}


void insert_in_set (Set *dest_set, Hand *Player, char *pieces[], unsigned num_of_pieces) {
    
    if (insert_set_possible (dest_set, is_run, pieces, num_of_pieces) == false) {
        printf ("Jogada invaliida");
        return;
    }

    // TODO

}


bool is_new_set_possible (bool is_run, char *pieces[], unsigned num_of_pieces) {
    
    // Primeiro teste: Numero de pecas > 3
    if (num_of_pieces < 3) {
        printf ("Numero de pecas para formar um set deve ser maior do que 3");
        return false;
    }

    // Segundo teste: Exceto o coringa, nao deve haver pecas repetidas no set
    for (int i = 0; i < num_of_pieces; ++i) {
        for (int j = i; j < num_of_pieces; ++j) {
           
            // Verifica se as pecas sao iguais
            if (piece[i][0] == piece[j][0] &&
                   piece[i][1] == piece[j][1]) {
                
                // Veriica se as pecas nao sao coringas
                if (piece[i][0] != "*") {
                    return false;
                }
            }
        } 
    }
    
    // Terceiro teste: Se o set for do tipo run, as pecas devem ser uma sequencia
    // TODO
   

    // Quarto teste: Se o set for do tipo group, as pecas devem ter a mesmo numero
    if (is_run == false) {
        for (int i = 0; i < num_of_pieces; ++i) {
            for (int j = i; j < num_of_pieces; ++j) {
                // Retorna falso caso haja pecas de numeros diferentes
                if (piece[i][0] != piece[j][0]) return false;
            }
        }
    }

}
