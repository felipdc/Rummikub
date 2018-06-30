#ifndef INTERFACE_H_
#define INTERFACE_H_

#ifdef _WIN32
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif

void removeNL(char *input);
int intInput();
float floatInput();
int startMenu();
void showHand(Hand *Player, int playerNumber, bool isTurn);
void showAllHands(Hand* Player, int numOfPlayers, int activePlayer);
void playerSwitcher(Hand* Player, Set* set, int numOfTurns, int numOfPlayers);
Set *createSet(Hand *Player, Set *set);
int playsMenu(Hand* Player, Set* set, int playerNumber);
void printSets (int numOfSets);

#endif