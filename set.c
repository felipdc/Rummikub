#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "pack.h"
#include "main.h"
#include "set.h"
#include "interface.h"


Set *init_set (bool is_run, unsigned idx, unsigned num_pieces){	//Inicializa um set novo

	Set *new_set = NULL;
	new_set = (Set *)malloc(sizeof(Set));
	new_set->run = is_run;
	new_set->set_idx = idx;
	new_set->num_of_pieces = num_pieces;
	new_set->next = NULL;
	return new_set;
}


int cmpfunc (const void * a, const void * b) {
       return ( *(int*)a - *(int*)b  );
}


/*
 * @desc Verifica se um conjunto de pecas possui pecas repetidas (exceto coringa)
 * @param char *pieces[] - conjunto de pecas a ser analisado
 *        unsigned num_of_pieces - numero total de pecas
 * @return True caso possua cartas repetidas, false contrario
 */

static bool have_same_piece (char *pieces[], unsigned num_of_pieces) {
    for (int i = 0; i < num_of_pieces; ++i) {
        for (int j = 0; j < num_of_pieces; ++j) {
           
            if (i == j) continue;

            // Verifica se as pecas sao iguais
            if (pieces[i][0] == pieces[j][0] &&
                   pieces[i][1] == pieces[j][1]) {
                
                // Veriica se as pecas nao sao coringas
                if (pieces[i][0] != '*') {
                    return true;
                }
            }
        } 
    }
    return false;
}


/*
 * @desc Verifica se as pecas possuem o mesmo numero
 * @param char *pieces[] - conjunto de pecas a ser analisado
 * 	  unsigned num_of_pieces - numero total de pecas
 * @return True caso possua mesmo numero, false contrario
 */

static bool have_same_number (char *pieces[], unsigned num_of_pieces) {
	// Quarto teste: Se o set for do tipo group, as pecas devem ter a mesmo numero
	for (int i = 0; i < num_of_pieces; ++i) {
		for (int j = 0; j < num_of_pieces; ++j) {

            if (i == j) continue; // Nao avalia a mesma peca
            // Se a peca for coringa, passa para a proxima peca
            if (pieces[i][0] == '*' || pieces[j][0] == '*') {
                continue;
            }
			// Retorna falso caso haja pecas de numeros diferentes
            if (pieces[i][0] != pieces[j][0]) {
                return false;    
            }       
		}
	}
    // Retorna true se passar no teste
    return true;
}


static unsigned get_piece_number (char piece[]) {
    if (piece[0] == '*') {
        return 99;  // Retorna 99 caso a peca seja um coringa
    }
    return strtol (piece, NULL, 16);
}


static bool is_a_sequence (char *pieces[2], unsigned num_of_pieces) {

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
        else if (pieces_num[i+1] - pieces_num[i] == 2) {
            ++non_consecutive_num;
        }
        else if (pieces_num[i+1] - pieces_num[i] == 3) {
            non_consecutive_num += 2;
        }
        else {
            printf ("Pecas nao estao em sequencia!\n");
            return false;
        }
    }
    
    // Verifica se ha coringas suficientes
    if (joker_num < non_consecutive_num) {
        return false;
    }
    return true;
}


Set * new_set (Set *set, bool is_run, char *pieces[2], unsigned num_of_pieces) {
    
    Set *aux_set = set;
    int i = 0;

    if (is_new_set_possible (is_run, pieces, num_of_pieces) == false) {
        printf ("Jogada invalida\n");
        return NULL;
    }
    // Verifica se eh o primeiro set do jogo
    if (set == NULL) {
        aux_set = init_set(is_run, 0, num_of_pieces);	//Como é o primeiro, o index é zero

        // Insere as novas pecas
        aux_set->set_piece = malloc (num_of_pieces);
        for (i = 0; i < num_of_pieces; ++i) {
            aux_set->set_piece[i] = malloc(2);
            aux_set->set_piece[i][0] = pieces[i][0];
            aux_set->set_piece[i][1] = pieces[i][1];
        }
        set = aux_set;	//Aqui o aux_set passa a ser o head dos sets, pois é o primeiro
        return set;
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
    return set;
}


void insert_in_set (Set *dest_set, bool is_run, char *pieces[], unsigned num_of_pieces) {
    
    if (insert_set_possible (dest_set, is_run, pieces, num_of_pieces) == false) {
        printf ("Jogada invalida");
        return;
    }
	
	// Insere as novas pecas no set
	for (int i = 0; i < num_of_pieces; ++i) {
		dest_set->set_piece[i + dest_set->num_of_pieces][0] = pieces[i][0];	
		dest_set->set_piece[i + dest_set->num_of_pieces][1] = pieces[i][1];	
	}	
	// Aumenta o numero de pecas do set
	dest_set->num_of_pieces += num_of_pieces;
}


bool insert_set_possible (Set *dest_set, bool is_run, char *pieces[], unsigned num_of_pieces) {

    // Numero de pecas total apos a insercao
    unsigned total_num_of_pieces = dest_set->num_of_pieces + num_of_pieces;

    // Preenche um novo array de pecas com pecas do set + pecas a serem inseridas
    char *new_pieces[2]; 
    for (int i = 0; i < dest_set->num_of_pieces; ++i) {
        new_pieces[i][0] = dest_set->set_piece[i][0];
        new_pieces[i][1] = dest_set->set_piece[i][1];
    }
    
    for (int i = dest_set->num_of_pieces - 1; i < total_num_of_pieces; ++i) {
        new_pieces[i][0] = pieces[i][0];
        new_pieces[i][1] = pieces[i][1];
    }

    // Primeiro teste: Numero de pecas total < 13
    if (dest_set->num_of_pieces + num_of_pieces > 13) {
        return false;    
    }

	// Segundo teste: Exceto coringa, nao deve haver pecas repetidas
	if (have_same_piece (new_pieces, total_num_of_pieces) == true) {
		return false;
	}
	
	// Terceiro teste: se o set for do tipo run, deve ser uma sequencia
	if (is_run == true) {
		if (is_a_sequence (new_pieces, total_num_of_pieces) == false) {
			return false;
		}
	}

	// Quarto teste: Se o teste for do tipo group, deve ter o mesmo numero
	if (is_run == false) {
		if (have_same_number (new_pieces, total_num_of_pieces) == false) {
			return false;
		}
	}
	
	// Se passar em todos os testes, retorna true
	return true;
}	


bool is_new_set_possible (bool is_run, char *pieces[], unsigned num_of_pieces) {
    
    // Primeiro teste: Numero de pecas > 3
    if (num_of_pieces < 3) {
        printf ("Numero de pecas para formar um set deve ser maior do que 2\n");
        return false;
    }
   
    // Segundo teste: Veririca se o set possui cartas repetidas (exceto coringa)
    if (have_same_piece(pieces, num_of_pieces) == true) {
        printf ("O set possui pecas iguais\n");
        return false;
    }

    // Terceiro teste: Se o set for do tipo run, as pecas devem ser uma sequencia
    if (is_run == true) {
		if (is_a_sequence(pieces, num_of_pieces) == false) {
            printf ("O conjunto de pecas nao forma uma sequencia\n");
			return false;
		}
	}

	// Se o set for do tipo group, veriica se as cartas sao do mesmo numero
	if (is_run == false) {
		if (have_same_number(pieces, num_of_pieces) == false) {
            printf ("As pecas nao possuem o mesmo numero\n");
			return false;
		}
	}
 	
    // Se passar em todos os testes, retorna true
    return true;
}


void show_set (Set *set) {
    Set *aux_set = set;
    while (aux_set != NULL) {
        for (int i = 0; i < aux_set->num_of_pieces; ++i) {
            printf ("%s ", aux_set->set_piece[i]);
        }
        printf ("\n");
        aux_set = aux_set->next;
    }
}
