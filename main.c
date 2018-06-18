#include <stdio.h> 
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>


#define NUM_PIECES 106
#define NUM_COLOR 4
#define NUM_COLOR_PIECES 26
#define NUM_JOKER 2

/**
 * O minimo de pecas para formar um set eh 3 pecas
 * Logo, o maximo de combinacoes eh 108/3 = 36
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


typedef enum {blue, yellow, black, red} Color;


struct set {
	bool run;	// True se o set eh do tipo RUN, false caso tipo GROUP
	Color color;	// Cor das pecas caso o set for do tipo GROUP
	char *set_piece[NUM_COLOR_PIECES];	// Guarda as pecas do set
	struct set *next;	// Aponta para o proximo set formado no jogo
}; typedef struct set Set;


struct hand {
	unsigned card_num; // Numero total de pecas na mao do jogador
	char *piece[NUM_PIECES];	// Pecas na mao do jogador
	struct hand *next;	// Aponta para o proximo jogador no jogo	
}; typedef struct hand Hand;


struct board {
	char *piece[NUM_PIECES];	// Guarda as pecas ainda nao distribuidas
	Set *s;		// Aponta para a lista de sets formados no jogo
	Hand *h;	// Aponta para a lista de jogadores no jogo
}; typedef struct board Board;


const char *blue_piece[] = {"1!", "2!", "3!", "4!",
				 "5!", "6!", "7!",
				"8!", "9!", "A!",
				"B!", "C!", "D!"};

const char *yellow_piece[] = {"1@", "2@", "3@", "4@",
				"5@", "6@", "7@",
				"8@", "9@", "A@",
				"B@", "C@", "D@"};

const char *black_piece[] = {"1#", "2#", "3#", "4#",
				"5#", "6#", "7#",
				"8#", "9#", "A#",
				"B#", "C#", "D#"};

const char *red_piece[] = {"1$", "2$", "3$", "4$",
				"5$", "6$", "7$",
				"8$", "9$", "A$",
				"B$", "C$", "D$"};

const char *joker[] = {"**", "**"};


int main (int argc, char *argv[]) {
	return 0;

}
