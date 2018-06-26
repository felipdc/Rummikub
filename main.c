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
	while(i < NUM_PIECES){
		New->piece[i][0] = '0';
		New->piece[i][1] = '0';
		++i;
	}
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
	board->p = create_pack(board->p);	// Insere todos os elementos na pilha de pecas
	shuffle_pack(board->p, NUM_PIECES + NUM_JOKER);	// Embaralha as pecas

	while(i < NofPlayers){
		AuxHand = init_hand();
		AuxHand = hand_out(board->p, AuxHand, INITIAL_HAND_SIZE); // Distribui peca para um jogador
		board->p = pop_piece(board->p, INITIAL_HAND_SIZE);	// Tira a peca da pilha de pecas
		board->h = insert_hand(board->h, AuxHand);
		++i;
	}
	return board;
}

void show_hand(Hand *Player){	//Exibe uma mão

	int i = 0;
	Hand *Aux = Player;

	while(i < Aux->card_num){
		printf("%c%c\n", Aux->piece[i][0], Aux->piece[i][1]);
		++i;
	}
}

void victory(Board *board){

	int i = 0;
	Hand *AuxHand = board->h;

	while(AuxHand != NULL){
		if(AuxHand->card_num == 0){
			printf("O vencedor é o jogador %d.\n", i + 1);
		}
		++i;
		AuxHand = AuxHand->next;
	}
}

int main (int argc, char *argv[]) {

	int i = 0;
	
	Board *NewBoard = init_board();	// Cria e aloca memoria para NewBoard

	int numOfPlayers = startMenu(); // Splash screen do jogo, retorna o numero de jogadores
	printf("\n");

	NewBoard = init_game(NewBoard, numOfPlayers);

	Hand *Aux = NewBoard->h;

	// while(i < numOfPlayers){
	// 	printf("\n\nHand %d:\n\n", i + 1);
	//  	show_hand(Aux);
	// 	++i;
	//  	Aux = Aux->next;
	// }
	
	// printf("\n\nPack after hand out:\n\n");
	// show_pack(NewBoard->p);

	

	// Testes do Dezan
	
	Aux = NewBoard->h;
	playerSwitcher(Aux, 20, numOfPlayers);
    //playerSwitcherAlt(Aux, 20, numOfPlayers);

	
	// Fim dos testes

	return 0;
}
