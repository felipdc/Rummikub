#ifndef SET_H_
#define SET_H_

#define MAX_SET_PIECES 13

struct set {
	bool run;   // True se o set eh do tipo RUN, false caso tipo GROUP
    unsigned set_idx;   // Index do set para facil visualizacao
	Color color;	// Cor das pecas caso o set for do tipo GROUP
	char set_piece[MAX_SET_PIECES][2];	// Guarda as pecas do set
	struct set *next;	// Aponta para o proximo set formado no jogo
}; typedef struct set Set;


/**
 * @desc Cria um novo set no jogo
 * @param Set *set - Lista de sets atuais do jogo
 *        Hand *Player - Jogador que esta fazendo a jogada
 *        bool is_run - Se o set vai ser do tipo run ou nao
 *        char *pieces[] - Pecas a serem utilizadas no set
 */

void new_set (Set *set, Hand *Player, bool is_run, char *pieces[]);


/**
 * @desc Insere pecas em um set ja formado
 * @param Set *set - Set em que o jogador deseja inserir a carta
 *        Hand *Player - Jogador que esta fazendo a jogada
 *        char *pieces[] - Pecas a serem inseridas no set
 */

void insert_in_set (Set *set, Hand *Player, char *pieces[]);


/**
 * @desc Troca pecas entre sets
 * @param Set *source_set - Set em que as pecas de origem estao
 *        Set *destination_set - Set para onde as pecas vao (caso NULL, um novo set eh criado)
 *        Hand *Player - jogador que esta fazendo a jogada
 *        char *pieces[] - pecas a serem trocadas
 */

void switch_set_piece (Set *source_set, Set *destination_set, Hand *Player, char *pieces[]);


/**
 *  @desc Verifica se um set pode ser feito com certas pecas
 *  @param bool is_run - Se o set eh do tipo run ou nao
 *         char *pieces[] - Pecas a serem usadas para um novo set
 *  @return Retorna true caso seja possivel, falso contrario
 */

bool is_new_set_possible (bool is_run, char *pieces[]);


/**
 *  @desc Verifica se eh possivel inserir uma carta em um set ja na mesa
 *  @param Set *destination_set - Set a ser testado
 *         bool is_run - Se o set eh do tipo run ou nao
 *         char *pieces[] - Pecas a serem inseridas
 *  @return Retorna true caso seja possivel, falso contrario
 */

bool insert_set_possible (Set *destination_set, bool is_run, char *pieces[]);

#endif // SET_H_    
