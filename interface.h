#ifndef INTERFACE_H_
#define INTERFACE_H_

#ifdef _WIN32
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif

void tStop();
void removeNL(char *input);
int intInput();
float floatInput();
int startMenu();
void showHand(Hand *Player, int playerNumber, bool isTurn);
void showAllHands(Hand* Player, int numOfPlayers, int activePlayer);
void playerSwitcher(Board *game_board, int numOfPlayers);
Set *createSet(Hand *Player, Set *set);
Board *playsMenu(Board *game_board, int playerNumber, int numOfPlayers);
void printSets (int numOfSets);

#endif
