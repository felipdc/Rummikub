#ifndef SET_H_
#define SET_H_

#define MAX_SET_PIECES 13

struct set {
	bool run;   // True se o set eh do tipo RUN, false caso tipo GROUP
	unsigned set_idx;   // Index do set para facil visualizacao
    unsigned num_of_pieces;
	char set_piece[MAX_SET_PIECES][2];	// Guarda as pecas do set
	struct set *next;	// Aponta para o proximo set formado no jogo
}; typedef struct set Set;


/**
 * @desc Cria um novo set no jogo
 * @param Set *set - Lista de sets atuais do jogo
 *        Hand *Player - Jogador que esta fazendo a jogada
 *        bool is_run - Se o set vai ser do tipo run ou nao
 *        char *pieces[] - Pecas a serem utilizadas no set
 *	  unsigned num_of_pieces - Numero de pecas a colocar no set
 */

void new_set (Set *set, Hand *Player, bool is_run, char *pieces[2], unsigned num_of_pieces);


/**
 * @desc Insere pecas em um set ja formado
 * @param Set *dest_set - Set em que o jogador deseja inserir a carta
 *        Hand *Player - Jogador que esta fazendo a jogada
 *        char *pieces[] - Pecas a serem inseridas no set
 *	  unsigned num_of_pieces - Numero de pecas a colocar no set
 */

void insert_in_set (Set *dest_set, Hand *Player, char *pieces[], unsigned num_of_pieces);


/**
 * @desc Troca pecas entre sets
 * @param Set *src_set - Set em que as pecas de origem estao
 *        Set *dest_set - Set para onde as pecas vao (caso NULL, um novo set eh criado)
 *        Hand *Player - jogador que esta fazendo a jogada
 *        char *pieces[] - pecas a serem trocadas
 *	  unsigned num_of_pieces - Numero de pecas a ser trocadas
 */

void switch_set_piece (Set *src_set, Set *dest_set, Hand *Player, char *pieces[], unsigned num_of_pieces);


/**
 *  @desc Verifica se um set pode ser feito com certas pecas
 *  @param bool is_run - Se o set eh do tipo run ou nao
 *         char *pieces[] - Pecas a serem usadas para um novo set
 *	   unsigned num_of_pieces - Numero de pecas a ser colocadas
 *  @return Retorna true caso seja possivel, falso contrario
 */

bool is_new_set_possible (bool is_run, char *pieces[], unsigned num_of_pieces);


/**
 *  @desc Verifica se eh possivel inserir uma carta em um set ja na mesa
 *  @param Set *dest_set - Set a ser testado
 *         bool is_run - Se o set eh do tipo run ou nao
 *         char *pieces[] - Pecas a serem inseridas
 *	   unsigned num_of_pieces - Numero de pecas a colocar no set
 *  @return Retorna true caso seja possivel, falso contrario
 */

bool insert_set_possible (Set *dest_set, bool is_run, char *pieces[], unsigned num_of_pieces);

/**
 *  @desc Imprime na tela os sets do jogo
 *  @param Set *set - Primeiro set da lista
 */

void show_set (Set *set);

Set *init_set(bool is_run, unsigned idx, unsigned num_pieces);	//Inicializa um tabuleiro novo

#endif // SET_H_    
