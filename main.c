#include <stdio.h> 
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "pack.h"
#include "main.h"
#include "interface.h"


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

	//NewBoard->p = malloc(sizeof(Piece));	// Aloca memoria para a pilha de pecas

	NewBoard->p = create_pack(NewBoard->p);	// Insere todos os elementos na pilha de pecas

	// shuffle_pack(NewBoard->p, NUM_PIECES + NUM_JOKER);	// Embaralha as pecas

	// show_pack(NewBoard->p);	// Imprime na tela as pecas em ordem da pilha



	init_game(NewBoard, 4);

	Hand *Aux = NewBoard->h;

	// Testes do Dezan
	int numOfPlayers = startMenu();
	printf("\n");
	int activePlayer = 3; // placeholder

	showAllHands(numOfPlayers, activePlayer);
	// Fim dos testes

	

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
