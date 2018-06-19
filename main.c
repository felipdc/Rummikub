#include <stdio.h> 
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>


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


typedef enum {blue, yellow, black, red, none} Color;	//none is joker's color


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


struct piece {
	Color color;	// Cor da peca
<<<<<<< HEAD
	const char *info;	// Valor da peca (1 a D) com a cor
	struct piece *next;	// Aponta para a proxima peca da pilha
}; typedef struct piece Piece;

=======
	unsigned num;	// Valor da peca (1 a D)
	struct piece *next;	// Aponta para a proxima peca da pilha
}; typedef struct piece Piece;


>>>>>>> 8c6784f26f7193c0fe692b9eb5664dfc600307bf
struct board {
	Piece *p;	// Aponta para a pilha de pecas
	Set *s;		// Aponta para a lista de sets formados no jogo
	Hand *h;	// Aponta para a lista de jogadores no jogo
}; typedef struct board Board;

const char *blue_piece[] = {"1!", "2!", "3!", "4!",
				 "5!", "6!", "7!",
				"8!", "9!", "A!",
				"B!", "C!", "D!", "1!", "2!", "3!", "4!",
				 "5!", "6!", "7!",
				"8!", "9!", "A!",
				"B!", "C!", "D!"};

const char *yellow_piece[] = {"1@", "2@", "3@", "4@",
				"5@", "6@", "7@",
				"8@", "9@", "A@",
				"B@", "C@", "D@", "1@", "2@", "3@", "4@",
				"5@", "6@", "7@",
				"8@", "9@", "A@",
				"B@", "C@", "D@"};

const char *black_piece[] = {"1#", "2#", "3#", "4#",
				"5#", "6#", "7#",
				"8#", "9#", "A#",
				"B#", "C#", "D#", "1#", "2#", "3#", "4#",
				"5#", "6#", "7#",
				"8#", "9#", "A#",
				"B#", "C#", "D#"};

const char *red_piece[] = {"1$", "2$", "3$", "4$",
				"5$", "6$", "7$",
				"8$", "9$", "A$",
				"B$", "C$", "D$", "1$", "2$", "3$", "4$",
				"5$", "6$", "7$",
				"8$", "9$", "A$",
				"B$", "C$", "D$"};

const char *joker[] = {"**", "**"};

Piece *create_piece(const char *newcard, Color color){

	Piece *New = NULL;
	New = (Piece *)malloc(sizeof(Piece));
	New->color = color;
	New->info = newcard;
	New->next = NULL;
	return New;
}

Piece *insert(Piece *Pack, Piece *New){

	Piece *Aux = Pack;

	if(Aux == NULL){
		return New;
	}

	while(Aux->next != NULL){
		Aux = Aux->next;
	}
	Aux->next = New;
	return Pack;
}

Piece *create_pack(Piece *Pack){

	int i = 0;
	int number_aux = 0;
	int color_aux = 0;
	Color color = none;
	const char *info = NULL;
	Piece *Aux = NULL;

	while(i < NUM_PIECES){
		number_aux = i / 4;

		switch(i % 4){
			case 0:	//blue !
				color = blue;
				info = blue_piece[number_aux];
				break;
			case 1: //yellow @
				color = yellow;
				info = yellow_piece[number_aux];
				break;
			case 2: //black #
				color = black;
				info = black_piece[number_aux];
				break;
			case 3: //red $
				color = red;
				info = red_piece[number_aux];
				break;
		}
		Aux = create_piece(info, color);
		Pack = insert(Pack, Aux);
		++i;
	}
	i = 0;
	color = none;
	while(i < NUM_JOKER){
		Aux = create_piece("**", color);
		Pack = insert(Pack, Aux);
		++i;
	}

	return Pack;
}

Piece *show_pack(Piece *Pack){

	Piece *Aux = Pack;

	while(Aux != NULL){
		printf("%s\n", Aux->info);
		Aux = Aux->next;
	}
	return Pack;
}

Piece *switch_piece(Piece *Pack, int Posit1, int Posit2){

	int i = 0;
	Piece *Aux1 = Pack;
	Piece *Aux2 = Pack;
	const char *TempInfo = NULL;
	Color TempColor = none;

	while(i < Posit1){
		Aux1 = Aux1->next;
		++i;
	}
	i = 0;
	while(i < Posit2){
		Aux2 = Aux2->next;
		++i;
	}

	TempInfo = Aux1->info;
	Aux1->info = Aux2->info;
	Aux2->info = TempInfo;
	TempColor = Aux1->color;
	Aux1->color = Aux2->color;
	Aux2->color = TempColor;
	return Pack;
}

Piece *shuffle_pack(Piece *Pack, int Len){

	int i = 0;
	int n = 0;

	srand(time(NULL));

	while(i < Len){
		n = i;
		while(i == n){
			n = rand() % Len;
		}
		Pack = switch_piece(Pack, i, n);
		++i;
	}
	return Pack;
}

int main (int argc, char *argv[]) {

	return 0;
}
