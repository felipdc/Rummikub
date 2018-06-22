#ifndef MAIN_H_
#define MAIN_H_

#include "pack.h"

#define NUM_PIECES 104
#define NUM_COLOR 4

/*
 * O número de peças em cada set é de até 13 peças, pois
 * nos sets do tipo run, o máximo de peças é 4, pois são somente
 * 4 cores; já no set tipo group, o máximo é 13, pois as peças vão de 1-13 
*/

#define NUM_COLOR_PIECES 13
#define NUM_JOKER 2

/**
 * O minimo de pecas para formar um set eh 3 pecas
 * Logo, o maximo de combinacoes eh 106/3 ~ 36
*/

#define MAX_SETS 36

/**
 * Ha dois tipos de sets (combinacoes) no jogo:
 * O run (ex: 2! 3! 4!) - maximo de 26
 * O group (ex: 1! 1@ 1#) - maximo de 13
*/

#define MAX_RUN_SETS 26
#define MAX_GROUP_SETS 26

/**
 * No inicio do jogo, cada jogador recebe na sua mao 14 pecas
*/ 

#define INITIAL_HAND_SIZE 14


struct set {
	bool run;	// True se o set eh do tipo RUN, false caso tipo GROUP
	Color color;	// Cor das pecas caso o set for do tipo GROUP
	char *set_piece[NUM_COLOR_PIECES];	// Guarda as pecas do set
	struct set *next;	// Aponta para o proximo set formado no jogo
}; typedef struct set Set;


struct hand {
	unsigned card_num; // Numero total de pecas na mao do jogador
	char piece[NUM_PIECES][2];	// Pecas na mao do jogador
	struct hand *next;	// Aponta para o proximo jogador no jogo	
}; typedef struct hand Hand;


struct board {
	Piece *p;	// Aponta para a pilha de pecas
	Set *s;		// Aponta para a lista de sets formados no jogo
	Hand *h;	// Aponta para a lista de jogadores no jogo
}; typedef struct board Board;


// Aloca e retorna board
Board *init_board();

Hand *insert_hand(Hand *Players, Hand *New);

Hand *hand_out(Piece *Pack, Hand *Player, int NPieces);

Board *init_game(Board *board, int NofPlayers);

void show_hand(Hand *Player);


#endif // PACK_H_
