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
	const char *set_piece[NUM_COLOR_PIECES];	// Guarda as pecas do set
	struct set *next;	// Aponta para o proximo set formado no jogo
}; typedef struct set Set;


struct hand {
	unsigned card_num; // Numero total de pecas na mao do jogador
	const char *piece[NUM_PIECES];	// Pecas na mao do jogador
	struct hand *next;	// Aponta para o proximo jogador no jogo	
}; typedef struct hand Hand;


struct piece {
	Color color;	// Cor da peca
	const char *info;	// Valor da peca (1 a D) com a cor
	struct piece *next;	// Aponta para a proxima peca da pilha
}; typedef struct piece Piece;

struct board {
	Piece *p;	// Aponta para a pilha de pecas
	Set *s;		// Aponta para a lista de sets formados no jogo
	Hand *h;	// Aponta para a lista de jogadores no jogo
}; typedef struct board Board;

const char *blue_piece[] = {"1!", "2!", "3!", "4!",
				"5!", "6!", "7!", "8!",
				"9!", "A!", "B!", "C!",
				"D!", "1!", "2!", "3!",
				"4!", "5!", "6!", "7!",
				"8!", "9!", "A!", "B!",
				"C!", "D!"};

const char *yellow_piece[] = {"1@", "2@", "3@", "4@",
				"5@", "6@", "7@", "8@",
				"9@", "A@", "B@", "C@",
				"D@", "1@", "2@", "3@",
				"4@", "5@", "6@", "7@",
				"8@", "9@", "A@", "B@",
				"C@", "D@"};

const char *black_piece[] = {"1#", "2#", "3#", "4#",
				"5#", "6#", "7#", "8#",
				"9#", "A#", "B#", "C#",
				"D#", "1#", "2#", "3#",
 				"4#", "5#", "6#", "7#",
				"8#", "9#", "A#", "B#",
				"C#", "D#"};

const char *red_piece[] = {"1$", "2$", "3$", "4$",
				"5$", "6$", "7$", "8$",
				"9$", "A$", "B$", "C$",
				"D$", "1$", "2$", "3$",
				"4$", "5$", "6$", "7$",
				"8$", "9$", "A$", "B$",
				"C$", "D$"};

const char *joker[] = {"**", "**"};

Piece *create_piece(const char *newcard, Color color){	//Cria uma peça nova recebendo qual a peça (ex: 1!) e sua cor (ex: blue)

	Piece *New = NULL;
	New = (Piece *)malloc(sizeof(Piece));
	New->color = color;
	New->info = newcard;
	New->next = NULL;
	return New;
}

Piece *insert_piece(Piece *Pack, Piece *New){	//Insere uma peça nova no baralho (precisa estar inicializada)

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

Piece *create_pack(Piece *Pack){	//Cria o baralho ordenado (1-D, !-@-#-$)

	int i = 0, number_aux = 0;
	Color color = none;
	const char *info = NULL;
	Piece *Aux = NULL;

	while(i < NUM_PIECES){	//Insere todas as peças com exceção dos jokers
		number_aux = i / 4;	//Só aumenta uma unidade de 4 em 4

		switch(i % 4){	//Muda a cor ciclicamente, visto que os restos possiveis pra 4 são somente (0,1,2,3)
			case blue:	//blue !
				color = blue;
				info = blue_piece[number_aux];
				break;
			case yellow: //yellow @
				color = yellow;
				info = yellow_piece[number_aux];
				break;
			case black: //black #
				color = black;
				info = black_piece[number_aux];
				break;
			case red: //red $
				color = red;
				info = red_piece[number_aux];
				break;
		}
		Aux = create_piece(info, color);
		Pack = insert_piece(Pack, Aux);
		++i;
	}
	i = 0;
	color = none;
	while(i < NUM_JOKER){	//Insere os jokers com a cor "none"
		Aux = create_piece("**", color);
		Pack = insert_piece(Pack, Aux);
		++i;
	}

	return Pack;
}

Piece *show_pack(Piece *Pack){	//Exibe o pack

	Piece *Aux = Pack;

	while(Aux != NULL){
		printf("%s\n", Aux->info);
		Aux = Aux->next;
	}
	return Pack;
}

Piece *switch_piece(Piece *Pack, int Posit1, int Posit2){	//Troca os dados de duas peças

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

Piece *shuffle_pack(Piece *Pack, int Len){	//Embaralha o pack (já tem que ter sido criado com a funcao create_pack)

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

Hand *init_hand(){	//Inicializa uma mão de um jogador

	int i = 0;
	Hand *New = NULL;
	New = (Hand *)malloc(sizeof(Hand));
	New->card_num = 0;
	New->next = NULL;

	while(i < NUM_PIECES){
		New->piece[i] = NULL;
		++i;
	}
	return New;
}

Board *init_board(){	//Inicializa um tabuleiro novo

	Board *NewBoard = NULL;
	NewBoard = (Board *)malloc(sizeof(Board));
	NewBoard->p = NULL;
	NewBoard->s = NULL;
	NewBoard->h = NULL;
	return NewBoard;
}

Hand *insert_hand(Hand *Players, Hand *New){	//Insere uma mão nova nas existentes

	Hand *Aux = Players;

	if(Aux == NULL){
		return New;
	}

	while(Aux->next != NULL){
		Aux = Aux->next;
	}
	Aux->next = New;
	return Players;
}

Piece *destroy(Piece *Pack){	//Apaga o pack

	if(Pack == NULL){
		return Pack;
	}
	Pack->next = destroy(Pack->next);
	free(Pack);
	return NULL;
}

//Apaga as n primeiras peças do pack 
//(quando se tira uma peça nova ou quando as peças sao distribuidas no começo do jogo)
Piece *erase_pieces(Piece *Pack, int n){	

	int i = 0;
	Piece *Temp = Pack;
	Piece *AuxHead = NULL;
	
	while(i < n - 1){
		Temp = Temp->next;
		++i;
	}
	AuxHead = Temp->next;
	Temp->next = NULL;
	Pack = destroy(Pack);
	return AuxHead;
}

Hand *hand_out(Piece *Pack, Hand *Player, int NPieces){	//Distribui NPieces do pack para uma mão

	int i = 0;
	Piece *Temp = Pack;

	while(i < NPieces){
		Player->piece[i] = Temp->info;
		++i;
		Temp = Temp->next;
	}
	Player->card_num = Player->card_num + NPieces;
	return Player;
}

//Inicializa o jogo distribuindo as INITIAL_HAND_SIZE peças
//para NofPlayers jogadores e retorna o tabuleiro
//(o pack já deve ter sido criado e preferencialmente embaralhado)
Board *init_game(Piece *Pack, int NofPlayers){

	int i = 0;
	Board *NewBoard = init_board();
	Hand *AuxHand = NULL;

	while(i < NofPlayers){
		AuxHand = init_hand();
		AuxHand = hand_out(Pack, AuxHand, INITIAL_HAND_SIZE);
		Pack = erase_pieces(Pack, INITIAL_HAND_SIZE);
		NewBoard->h = insert_hand(NewBoard->h, AuxHand);
		++i;
	}
	NewBoard->p = Pack;
	return NewBoard;
}

Hand *show_hand(Hand *Player){	//Exibe uma mão

	int i = 0;
	Hand *Aux = Player;

	while(Aux->piece[i] != NULL){
		printf("%s\n", Aux->piece[i]);
		++i;
	}
	return Player;
}

int main (int argc, char *argv[]) {

	int i = 0;
	Board *NewBoard = NULL;
	Piece *Pack = NULL;
	Hand *Aux = NULL;

	Pack = create_pack(Pack);
	Pack = shuffle_pack(Pack, NUM_PIECES + NUM_JOKER);
	
	printf("\n\nInitial pack:\n\n");
	Pack = show_pack(Pack);
	NewBoard = init_game(Pack, 4);

	Aux = NewBoard->h;
	while(i < 4){
		printf("\n\nHand %d:\n\n", i + 1);
		Aux = show_hand(Aux);
		++i;
		Aux = Aux->next;
	}

	printf("\n\nPack after hand out (to 4 players):\n\n");
	//AQUI DA PROBLEMA
	Pack = show_pack(Pack);

	printf("\n\nPack after hand out (to 4 players):\n\n");
	//AQUI NAO DA, MAS TEORICAMENTE NAO DEVERIA SER A MESMA COISA??
	Pack = show_pack(NewBoard->p);
	

	return 0;
}
