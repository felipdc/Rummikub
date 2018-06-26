#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "pack.h"
#include "main.h"
#include "set.h"
#include "interface.h"

Set *init_set(bool is_run, unsigned idx, unsigned num_pieces){	//Inicializa um set novo

	Set *new_set = NULL;
	new_set = (Set *)malloc(sizeof(Set));
	new_set->run = is_run;
	new_set->set_idx = idx;
	new_set->num_of_pieces = num_pieces;
	new_set->next = NULL;
	return new_set;
}

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
    int i = 0;

    if (is_new_set_possible (is_run, pieces, num_of_pieces) == false) {
        printf ("Jogada invalida");
        return;
    }

    // Verifica se eh o primeiro set do jogo
    if (set == NULL) {
        aux_set = init_set(is_run, 0, num_of_pieces);	//Como é o primeiro, o index é zero

        // Insere as novas pecas
        for (i = 0; i < num_of_pieces; ++i) {
            aux_set->set_piece[i][0] = pieces[i][0];
            aux_set->set_piece[i][1] = pieces[i][1];
        }
        set = aux_set;	//Aqui o aux_set passa a ser o head dos sets, pois é o primeiro
        return;
    } // Else
    
    // Avanca ate a ultima lista de set
    i = 1;	//Será o index do set
    while (aux_set->next != NULL) {	//Aqui tava aux_set->next == NULL, mas é aux_set->next != NULL
        aux_set = aux_set->next;
        ++i;
    }

    // Aloca memoria para um novo set
    aux_set->next = init_set(is_run, i, num_of_pieces);
    aux_set = aux_set->next;    // Muda para o novo set

    // Insere as pecas no set
    for (i = 0; i < num_of_pieces; ++i) {
        aux_set->set_piece[i][0] = pieces[i][0];
        aux_set->set_piece[i][1] = pieces[i][1];
    }
}


void insert_in_set (Set *dest_set, Hand *Player, char *pieces[], unsigned num_of_pieces) {
    
    if (insert_set_possible (dest_set, is_run, pieces, num_of_pieces) == false) {
        printf ("Jogada invalida");
        return;
    }

    // TODO

}


bool insert_set_possible (Set *dest_set, bool is_run, char *pieces[], unsigned num_of_pieces) {

    // Numero de pecas total apos a insercao
    unsigned total_num_of_pieces = dest_set->num_of_pieces + num_of_pieces;
    // Preenche um novo array de pecas com pecas do set + pecas a serem inseridas
    char *new_pieces[2]; 
    for (int i = 0; i < dest_set->num_of_pieces; ++i) {
        new_pieces[i][0] = aux_set->set_piece[i][0];
        new_pieces[i][1] = aux_set->set_piece[i][1];
    }
    
    for (int i = dest_set->num_of_pieces - 1; i < total_num_of_pieces; ++i) {
        new_pieces[i][0] = pieces[i][0];
        new_pieces[i][1] = pieces[i][1];
    }

    // Primeiro teste: Numero de pecas total < 13
    if (dest_set->num_of_pieces + num_of_pieces > 13) {
        return false;    
    }



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
    // Se passar em todos os testes, retorna true
    return true;
}


void show_set (Set *set) {
    Set *aux_set = set;
    while (aux_set->next != NULL) {
        aux_set = aux_set->next;
        for (int i = 0; i < aux_set->num_of_pieces; ++i) {
            printf ("%s ", aux_set->set_piece[i]);
        }
        printf ("\n");
    }
}
