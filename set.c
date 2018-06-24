#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "pack.h"
#include "main.h"
#include "set.h"
#include "interface.h"


static unsigned get_piece_number (char piece[]) {
    if (piece[0] == '*') {
        return 99;  // Retorna 99 caso a peca seja um coringa
    }
    return strtol (piece, NULL, 16);
}


static Color get_piece_color (char piece[]) {
    if (piece[1] == '!') return blue;
    if (piece[1] == '@') return yellow;
    if (piece[1] == '#') return black;
    if (piece[1] == '$') return red;
    if (piece[1] == '*') return none;
}


unsigned cmpfunc (const void * a, const void * b) {
       return ( *(unsigned*)a - *(unsigned*)b  );
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
    while (aux_set->next != NULL) {	//Aqui tava aux_set->next == NULL, mas é aux_set->next != NULL
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
    // 1 - Cria um array com os numeros das pecas (exceto o coringa)
    // 2 - Ordena o array
    // 3 - Verifica quantos coringas ha no set
    // 4 - Verifica se (X[i+1] - X[i] == 1). Se for 2, checa se ha um coringa no set
    // 5 - Verifica se ha coringas suficientes

    // 1.
    unsigned pieces_num[num_of_pieces];
    for (int i = 0; i < num_of_pieces; ++i) {
        pieces_num[i] = get_piece_number(pieces[i]);
    }
    
    // 2.
    qsort (pieces_num, num_of_pieces, sizeof(unsigned), cmpfunc);

    // 3.
    unsigned joker_num = 0;
    for (int i = 0; i < num_of_pieces; ++i) {
        if (pieces_num[i] == 99) ++joker_num;
    }

    // 4.
    unsigned non_consecutive_num = 0;   // Conta quantas vezes sera necessario um coringa
    for (int i = 0; i < num_of_pieces - joker_num - 1; ++i) {
        if (pieces_num[i+1] - pieces_num[i] == 1) {
            continue;
        }
        if (pieces_num[i+1] - pieces_num[i] == 2) {
            ++non_consecutive_num;
        }
        if (pieces_num[i+1] - pieces_num[i] == 3) {
            non_consecutive_num += 2;
        }
        else {
            printf ("Pecas nao estao em sequencia!\n");
            return false;
        }
    }

    // 5.
    if (non_consecutive_num > joker_num) return false;

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
