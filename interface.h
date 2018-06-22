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
void showHand(int playerNumber, bool isTurn);
void showAllHands(int numOfPlayers, int activePlayer);

#endif