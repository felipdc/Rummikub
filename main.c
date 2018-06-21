#include <stdio.h> 
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "pack.h"
#include "main.h"


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


Piece *create_piece(char *newcard, Color color){	//Cria uma peça nova recebendo qual a peça (ex: 1!) e sua cor (ex: blue)
	Piece *New = (Piece *)malloc(sizeof(Piece));
	New->color = color;
	strcpy(New->info, newcard);
	New->next = NULL;
	return New;
}


/**
 * @desc Insere na pilha uma nova peca
 * @param $head - Endereco de memoria do inicio da pilha
 *	  $New - Peca a ser adicionada na pilha
*/

void push_piece(Piece *head, Piece *New){	//Insere uma peça nova no baralho (precisa estar inicializada)

	Piece *Aux = head;

	if(Aux == NULL){
		printf("O Pack precisa estar inicializado");
		return;
	}

	while(Aux->next != NULL){
		Aux = Aux->next;
	}
	Aux->next = New;
}

void create_pack(Piece *Pack){	//Cria o baralho ordenado (1-D, !-@-#-$)

	int i = 0, number_aux = 0;
	Color color = none;
	char info[2];
	Piece *Aux;

	while(i < NUM_PIECES){	//Insere todas as peças com exceção dos jokers
		number_aux = i / 4;	//Só aumenta uma unidade de 4 em 4
		switch(i % 4){	//Muda a cor ciclicamente, visto que os restos possiveis pra 4 são somente (0,1,2,3)
			case blue:	//blue !
				color = blue;
				strcpy(info, blue_piece[number_aux]);
				break;
			case yellow: //yellow @
				color = yellow;
				strcpy(info, yellow_piece[number_aux]);
				break;
			case black: //black #
				color = black;
				strcpy(info, black_piece[number_aux]);
				break;
			case red: //red $
				color = red;
				strcpy(info, red_piece[number_aux]);
				break;
		}
		Aux = create_piece(info, color);
		push_piece(Pack, Aux);
		++i;
	}
	i = 0;
	color = none;
	while(i < NUM_JOKER){	//Insere os jokers com a cor "none"
		Aux = create_piece("**", color);
		push_piece(Pack, Aux);
		++i;
	}
}

void show_pack(Piece *Pack){	//Exibe o pack

	Piece *Aux = Pack;

	while(Aux != NULL){
		printf("%s\n", Aux->info);
		Aux = Aux->next;
	}
}

void switch_piece(Piece *Pack, int Posit1, int Posit2){	//Troca os dados de duas peças

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
	strcpy(Aux1->info, Aux2->info);
	strcpy(Aux2->info, TempInfo);
	TempColor = Aux1->color;
	Aux1->color = Aux2->color;
	Aux2->color = TempColor;
}

void shuffle_pack(Piece *Pack, int Len){	//Embaralha o pack (já tem que ter sido criado com a funcao create_pack)

	int i = 0;
	int n = 0;

	srand(time(NULL));

	while(i < Len){
		n = i;
		while(i == n){
			n = rand() % Len;
		}
		switch_piece(Pack, i, n);
		++i;
	}
}

Hand *init_hand(){	//Inicializa uma mão de um jogador

	int i = 0;
	Hand *New = (Hand *)malloc(sizeof(Hand));
	New->card_num = 0;
	New->next = NULL;
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

void insert_hand(Hand *Players, Hand *New){	//Insere uma mão nova nas existentes

	Hand *Aux = Players;	

	while(Aux->next != NULL){
		Aux = Aux->next;
	}
	Aux->next = New;
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
void pop_piece(Piece *head, int n){
	int i = 0;
	Piece *Temp = head;

	// Percorre n vezes ate o topo da pilha para remover n pecas do pack
	for(i = 0; i < n; ++i) {
		// Percorre ate o topo da pilha
		while(Temp->next->next != NULL){
			Temp = Temp->next;
		}
		Temp->next = NULL;
		free(Temp->next);
		Temp = head; // Volta para o head da pilha	
	}

}

Hand *hand_out(Piece *Pack, Hand *Player, int NPieces){	//Distribui NPieces do pack para uma mão

	int i = 0;
	Piece *Temp = Pack;

	while(i < NPieces){
		strcpy(Player->piece[i], Temp->info);
		//Player->piece[i] = Temp->info;
		++i;
		Temp = Temp->next;
	}
	Player->card_num = Player->card_num + NPieces;

	return Player;
}

//Inicializa o jogo distribuindo as INITIAL_HAND_SIZE peças
//para NofPlayers jogadores e retorna o tabuleiro
//(o pack já deve ter sido criado e preferencialmente embaralhado)
Board *init_game(Board *board, int NofPlayers){

	int i = 0;
	Hand *AuxHand = NULL;

	while(i < NofPlayers){
		AuxHand = init_hand();
		hand_out(board->p, AuxHand, INITIAL_HAND_SIZE); // Distribui peca para um jogador
		pop_piece(board->p, INITIAL_HAND_SIZE);	// Tira a peca da pilha de pecas
		//insert_hand(board->h, AuxHand);
		++i;
	}
}

void show_hand(Hand *Player){	//Exibe uma mão

	int i = 0;
	Hand *Aux = Player;

	while(Aux->piece[i] != NULL){
		printf("%s\n", Aux->piece[i]);
		++i;
	}
}


int main (int argc, char *argv[]) {

	int i = 0;
	
	Board *NewBoard = init_board();	// Cria e aloca memoria para NewBoard

	NewBoard->p = malloc(sizeof(Piece));	// Aloca memoria para a pilha de pecas

	create_pack(NewBoard->p);	// Insere todos os elementos na pilha de pecas

	shuffle_pack(NewBoard->p, NUM_PIECES + NUM_JOKER);	// Embaralha as pecas

	show_pack(NewBoard->p);	// Imprime na tela as pecas em ordem da pilha



	// init_game(NewBoard, 4);

	// Hand *Aux = NewBoard->h;

	// while(i < 4){
	// 	printf("\n\nHand %d:\n\n", i + 1);
	// 	show_hand(Aux);
	// 	++i;
	// 	Aux = Aux->next;
	// }

	// printf("\n\nPack after hand out (to 4 players):\n\n");
	// //AQUI NAO DA, MAS TEORICAMENTE NAO DEVERIA SER A MESMA COISA??
	// show_pack(NewBoard->p);
	

	return 0;
}
