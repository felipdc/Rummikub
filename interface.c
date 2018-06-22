#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pack.h"
#include "main.h"

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
    printf("RUMMIKUB\n\n");
    printf("Quantas pessoas irao jogar? ");

    int numOfPlayers = intInput();

    
    return numOfPlayers;
}

// Mostra as mãos de todos os jogadores

void showAllHands(int NofPlayers) {
    char *hand[] = {"##", "##", "##", "##", "##", "##"};
    
    for (int i = 0; i < NofPlayers; i++){
        printf("Player %d\t", i+1);
    }
    printf("\n");
    for (int i = 0; i < NofPlayers; i++){
        printf("[");
        int j = 0;
        while (hand[j] == "##"){
            printf("%s", hand[j]);
        }
        printf("]");
    }
}