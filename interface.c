#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include "pack.h"
#include "main.h"
#include "interface.h"
#include "set.h"

void tStop(){
    printf("\n\nPressione ENTER para continuar ");
    getchar();
}

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
    printf("\n\n\t##################\n");
    printf(    "\t#                #\n");
    printf(    "\t#    RUMMIKUB    #\n");
    printf(    "\t#                #\n");
    printf(    "\t##################\n\n");
    printf("  Quantas pessoas irao jogar? ");

    int numOfPlayers = intInput();
    while (numOfPlayers > 5 || numOfPlayers < 1){
        printf("\n  O jogo e para 1 a 5 pessoas.\n\n  Quantas pessoas irao jogar? ");
        numOfPlayers = intInput();
    }

    

    
    return numOfPlayers;
}

// Mostra as mãos de um jogador
// Recebe o numero do jogador, quantas cartas ele tem na mão, e se é a vez dele
// Ex.: Jogador 2, com 6 cartas e não é seu tuno = showHand(2, 6, false)

void showHand(Hand *Player, int playerNumber, bool isTurn) {
    
    if (isTurn){
        printf("-> [Jogador %d]", playerNumber);
    } else {
        printf("[Jogador %d]", playerNumber);
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


// Função para teste de impressão de sets
void printSets (int numOfSets) {
    srand(time(NULL));
    int cCount = 0;
    for (int i = 0; i < numOfSets; i++){
        int numOfPieces = (rand() % 13) + 1;
        cCount += numOfPieces*5;
        if (cCount > 60){
            printf("\n\n");
            cCount = numOfPieces*5;   
        } 
        printf(" [");
        for (int j = 0; j < numOfPieces - 1; j++){
            printf("##, ");
        }
        printf("##]  ");
    }
}

void createSet(Hand *Player) {
    Hand *Aux = Player;
    printf("\nEscreva o set com as cartas separadas \npor espaco (Ex: \"4! 5! 6!\")\n");
    char cards[50];
    fgets(cards, 50, stdin);
    removeNL(cards);
    int numOfPieces = 0;
    char **pieces;
    int pieces_index = 0;
    pieces = malloc (strlen(cards));
    for (int i = 0; i <= strlen(cards); i++){
        if (cards[i] == ' ' || cards[i] == '\0'){
            numOfPieces++;
        } else if (cards[i+1] == ' ' || cards[i+1] == '\0'){
            pieces[pieces_index++] = malloc(2);
            pieces[numOfPieces][0] = cards[i-1];
            pieces[numOfPieces][1] = cards[i];
        }
    }
    bool isRun = true;
    for (int i = 0; i < numOfPieces; i++){
        if(pieces[i][0] != (pieces[0][0]+i) && pieces[i][0] != '*'){
            isRun = false;
        }
    }
    is_new_set_possible(isRun, pieces, numOfPieces);
    tStop();
}


int playsMenu(Hand* Player, int playerNumber){
    printf("[Jogador %d]", playerNumber);
    printf("\n\n[1] Colocar set no tabuleiro"); 
    printf("\n[2] Colocar cartas em outros sets");
    printf("\n[3] Comprar do baralho");
    printf("\n[4] Terminar o turno");
    while(1){
        printf("\n\nEscolha sua jogada: ");
        int prompt = intInput();
        switch(prompt) {
            case 1:
                createSet(Player);
            case 2:
                return 2;
            case 3:
                return 3;
            case 4:
                return 4;
                break;
            default:
                printf("Opcao nao encontrada.");
        }
    }
}

// Função pra checar se ta passando a vez do jogador
// Apenas um teste

void playerSwitcher(Hand* Player, int numOfTurns, int numOfPlayers){
    Hand *Aux = Player;
    int i = 0;
    while(i < numOfTurns){
        system(CLEAR);
        printf("=========================================================\n");
        //printf("\n\n\n\n\tOS SETS FICARIAM AQUI, PROVAVELMENTE\n\n\n\n\n");
        printSets(9);
        printf("\n=========================================================\n\n");
        showAllHands(Aux, numOfPlayers, (i%numOfPlayers)+1);
        printf("=========================================================\n");
        playsMenu(Aux, (i%numOfPlayers)+1);
        i++;
    }
}
