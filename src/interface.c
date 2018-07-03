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
    
    printf("%c%c", Aux->piece[i][0], Aux->piece[i][1]);
    printf("]\n\n");
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


Set *createSet(Hand *Player, Set *set) {
    Hand *Aux = Player;
    char cards[50];
    int numOfPieces;
    char **pieces;
    int pieces_index = 0;
    bool isRun;
    bool erased;
    bool counted;
    int equalCount;
    int i = 0;
    int j = 0;
    pieces = malloc (strlen(cards));

    while(1){
        printf("\nEscreva o set com as cartas separadas por \nespaco (Ex: \"4! 5! 6!\") ou \"0\" para voltar.\n");
        fgets(cards, 50, stdin);
        removeNL(cards);
        numOfPieces = 0;
        if(cards[0] == '0'){
            return set;
        }
        for (i = 0; i <= strlen(cards); i++){
            if ((cards[i] == ' ' && cards[i+1] != '\0') || cards[i] == '\0'){
                numOfPieces++;
            } else if (cards[i+1] == ' ' || (cards[i+1] == '\0' && cards[i] != ' ')){
                pieces[pieces_index++] = malloc(3);
                pieces[numOfPieces][0] = cards[i-1];
                pieces[numOfPieces][1] = cards[i];
                pieces[numOfPieces][2] = '\0';
            }
        }
        isRun = true;
        equalCount = 0;
        int start = strtol(pieces[0], NULL, 16);
        int current;
        for (i = 0; i < numOfPieces; i++){
            current = strtol(pieces[i], NULL, 16);
            if((current != start+i) && pieces[i][0] != '*'){
                isRun = false;
            }
            counted = false;
            for(j = 0; j < Aux->card_num; j++){
                if ((pieces[i][0] == Aux->piece[j][0] && pieces[i][1] == Aux->piece[j][1] && (Aux->piece[j][1] != Aux->piece[j+1][1] || Aux->piece[j][0] != Aux->piece[j+1][0])) && counted == false){
                    equalCount++;
                    counted = true;
                }
            }
        }
        if (equalCount != numOfPieces){
            printf("\nVoce nao possui essas cartas.");
            pieces_index = 0;
            tStop();
        } else {
            if(is_new_set_possible(isRun, pieces, numOfPieces) == true){
                for (i = 0; i < numOfPieces; i++){
                    erased = false;
                    for(j = 0; j < Aux->card_num; j++){
                        if (((pieces[i][0] == Aux->piece[j][0]) && (pieces[i][1] == Aux->piece[j][1])) && (erased == false)){
                            Aux->piece[j][0] = '0';
                            Aux->piece[j][1] = '0';
                            erased = true;
                        }
                    }
                }
                sort_single_hand(Aux, NAIPE);
                Aux->card_num -= numOfPieces;
            }
            break;
        }
    }
    
    return new_set(set, isRun, pieces, numOfPieces);
}

Hand *erase_piece(Hand *Player, char **piece, int numOfPieces){

    int i = 0;
    int j = 0;
    bool erased = false;

    while(j < numOfPieces){
        i = 0;
        erased = false;
        while(i < NUM_PIECES){
            if(((Player->piece[i][0] == piece[j][0]) && (Player->piece[i][1] == piece[j][1])) && (erased == false)){
                Player->piece[i][0] = '0';
                Player->piece[i][1] = '0';
                erased = true;
            }
            ++i;
        }
        ++j;
    }

    return Player;
}

Set *insert_occup_set(Board *game_board){

    char cards[50];
    char **pieces;
    int numOfPieces;
    int set_index = 0;
    int pieces_index = 0;
    int i = 0;
    
    if (game_board->s == NULL) {
        printf ("Nao ha nenhum set na mesa");
        return game_board->s;
    }

    printf("Em qual set deseja inserir? ");
    set_index = intInput();
    getchar();
    --set_index;
    printf("\nEscreva a(s) carta(s) que deseja inserir separadas por \nespaco (Ex: \"4! 5! 6!\") ou \"0\" para voltar.\n");
    fgets(cards, 50, stdin);
    removeNL(cards);
    numOfPieces = 0;
    pieces = malloc(strlen(cards));
    
    if(cards[0] == '0'){
        return game_board->s;
    }

    for (i = 0; i <= strlen(cards); i++){
        if ((cards[i] == ' ' && cards[i+1] != '\0') || cards[i] == '\0'){
            numOfPieces++;
        } else if (cards[i+1] == ' ' || (cards[i+1] == '\0' && cards[i] != ' ')){
            pieces[pieces_index++] = malloc(3);
            pieces[numOfPieces][0] = cards[i-1];
            pieces[numOfPieces][1] = cards[i];
            pieces[numOfPieces][2] = '\0';
        }
    }

    //Ainda falta procurar e inserir
    // Procura set pelo index 
    Set *aux_set = game_board->s;
    while (aux_set->set_idx != set_index) {
        if (aux_set == NULL) {
            printf ("Set nao encontrado!\n");
            return game_board->s;
        }
        aux_set = aux_set->next;
    }
    // Insere as cartas no set
    insert_in_set (aux_set, aux_set->run, pieces, numOfPieces);
    if(is_new_set_possible(aux_set->run, pieces, numOfPieces) == true){ 
        game_board->h = erase_piece(game_board->h, pieces, numOfPieces);
    }
    
    return game_board->s;
}

void playerSwitcher(Board *game_board, int numOfPlayers){

    Hand *aux_hand = game_board->h;
    int i = 0;
    int k;
    sort_hands(game_board->h, numOfPlayers);
    int sortMethod = NAIPE;
    bool played = false;
    while(1) {
        system(CLEAR);
        printf("===============================================================\n");
        show_set (game_board->s);
        printf("\n===============================================================\n\n");
        showAllHands(aux_hand, numOfPlayers, (i%numOfPlayers)+1);
        printf("===============================================================\n");
        //game_board = playsMenu(game_board, (i%numOfPlayers)+1, numOfPlayers);
        
        printf("[Jogador %d]", (i%numOfPlayers)+1);
        printf("\n\n[1] Colocar set no tabuleiro"); 
        printf("\n[2] Colocar cartas em outros sets");
        printf("\n[3] Comprar do baralho");
        printf("\n[4] Terminar o turno");
        printf("\n[5] Trocar a organizacao das cartas na mao");
        printf("\n[0] Fechar o programa");

            printf("\n\nEscolha sua jogada: ");
            int prompt = intInput();
            switch(prompt) {
                case 1:
                    game_board->s = createSet(game_board->h, game_board->s);
                    played = true;
                    break;
                case 2:
                    game_board->s = insert_occup_set(game_board);
                    played = true;
                    break;
                case 3:
                    game_board->h = get_from_pack (game_board->p, game_board->h);
                    game_board->p = pop_piece (game_board->p, 1);
                    game_board->h = game_board->h->next;
                    played = false;
                    ++i;
                    break;
                case 4:
                    if(aux_hand->card_num == 0){
                        printf("\n\nO vencedor é o jogador %d!\n", (i%numOfPlayers)+1);
                        return;
                    }
                    if(played == false){
                        printf("Voce ainda nao fez sua jogada!");
                        tStop();
                    } else {
                        game_board->h = game_board->h->next;
                        played = false;
                        ++i;
                    }
                    break;
                case 5:
                    if (sortMethod == NUMERO){
                        sortMethod = NAIPE;
                    } else {
                        sortMethod = NUMERO;
                    }
                    break;
                case 0:
                    return;
                default:
                    printf("Opcao nao encontrada.");
                    tStop();
                    break;
            }
            sort_single_hand(game_board->h, sortMethod);
            k = 0;
            while(aux_hand->piece[k][0] != '0'){
                k++;
            }
            aux_hand->card_num = k;
        
        if (game_board == NULL) {
            return;
        }
        
    }
}