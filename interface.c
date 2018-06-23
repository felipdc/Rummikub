#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "pack.h"
#include "main.h"
#include "interface.h"



void removeNL(char *input){                             // Função para remover o \n do fgets
    size_t len = strlen(input);
        if (len > 0 && input[len-1] == '\n') {
            input[--len] = '\0';
    }
}

int intInput() {                                        // Recebe um input com fgets, confere se é
    int number;                                         // um inteiro e o converte com a função strtol
    char inputString[127];
    char *endBuff;
    fgets(inputString, 127, stdin);
    removeNL(inputString);
    number = strtol(inputString, &endBuff, 10);
    while (*endBuff != '\0'){
        printf("Por favor digite um numero valido: ");
        fgets(inputString, 127, stdin);
        removeNL(inputString);
        number = strtol(inputString, &endBuff, 10);
    }
    return number;
}

// Splash Screen
// Retorna o numero de jogadores
// Em construção

int startMenu() {
    system(CLEAR);
    printf("RUMMIKUB\n\n");
    printf("Quantas pessoas irao jogar? ");

    int numOfPlayers = intInput();
    while (numOfPlayers > 5 || numOfPlayers < 1){
        printf("\nO jogo e para 1 a 5 pessoas.\nQuantas pessoas irao jogar? ");
        numOfPlayers = intInput();
    }

    

    
    return numOfPlayers;
}

// Mostra as mãos de um jogador
// Recebe o numero do jogador, quantas cartas ele tem na mão, e se é a vez dele
// Ex.: Jogador 2, com 6 cartas e não é seu tuno = showHand(2, 6, false)

void showHand(Hand *Player, int playerNumber, bool isTurn) {
    
    if (isTurn){
        printf(" -> [PLAYER %d]", playerNumber);
    } else {
        printf("[Player %d]", playerNumber);
    }

    int i = 0;
    printf("\n[");
	Hand *Aux = Player;

	while(i < Aux->card_num-1){
		printf("%c%c, ", Aux->piece[i][0], Aux->piece[i][1]);
		++i;
	}
    printf("%c%c]\n\n", Aux->piece[i][0], Aux->piece[i][1]);
}


// Mostra todas as mãos simultaneamente
// Recebe o numero de jogadores total e o jogador que deve jogar
// Ex.: 5 jogadores, vez do Jogador 3 = showAllHands(5, 3);

void showAllHands(Hand* Player, int numOfPlayers, int activePlayer){
    int i = 1;
    Hand *Aux = Player;
    while(i <= numOfPlayers){
        if(i == activePlayer) {
            showHand(Aux, i, true);
        } else {
            showHand(Aux, i, false);
        }
		++i;
	 	Aux = Aux->next;
	}
}

// Função pra checar se ta passando a vez do jogador
// Apenas um teste

void playerSwitcher(Hand* Player, int numOfTurns, int numOfPlayers){
    Hand *Aux = Player;
    int i = 0;
    while(i < numOfTurns){
        system(CLEAR);
        printf("=========================================================");
        printf("\n\n\n\n\n\tOS SETS FICARIAM AQUI, PROVAVELMENTE\n\n\n\n\n");
        printf("=========================================================\n\n");
        showAllHands(Aux, numOfPlayers, (i%numOfPlayers)+1);
        i++;
        printf("=========================================================\n");
        printf("\nPressione ENTER pra passar de turno (TESTE)\n");
        getchar();
    }
}