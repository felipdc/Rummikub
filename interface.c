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

    
    return numOfPlayers;
}

// Mostra as mãos de um jogador
// Recebe o numero do jogador, quantas cartas ele tem na mão, e se é a vez dele
// Ex.: Jogador 2, com 6 cartas e não é seu tuno = showHand(2, 6, false)

void showHand(int playerNumber, bool isTurn) {
    // Valores placeholder
    char *hand[] = {"##", "##", "##", "##", "##", "##", "##"};
    int numOfCards = 6; // Provavelmente será obtida analisando a mão do jogador (a mão provavelmente entrará como parâmetro ao invès de playerNumber)

    // Estava tentando fazer uns testes com gotoxy, mas tava dando problema com a conio.h 

    // int x = (playerNumber-1) * numOfCards*4;
    // int y = -2;
    // gotoxy(x,y);
    
    if (isTurn){
        printf(" -> [PLAYER %d]", playerNumber);
    } else {
        printf("player %d", playerNumber);
    }

    printf("\n[");
    for (int i = 0; i < numOfCards; i++){
        printf("%s, ", hand[i]);
    }
    printf("%s]\n\n", hand[numOfCards]);;
}


// Mostra todas as mãos simultaneamente
// Recebe o numero de jogadores total e o jogador que deve jogar
// Ex.: 5 jogadores, vez do Jogador 3 = showAllHands(5, 3);

void showAllHands(int numOfPlayers, int activePlayer){
    for (int i = 1; i <= numOfPlayers; i++) {
        if (i == activePlayer) {
            showHand(i, true);
        } else {
            showHand(i, false);
        }
    }
}