#ifndef PACK_H_
#define PACK_H_


typedef enum {blue, yellow, black, red, none} Color;	//none is joker's color


struct piece {
	Color color;	// Cor da peca
	char info[2];	// Valor da peca (1 a D) com a cor
	struct piece *next;	// Aponta para a proxima peca da pilha
}; typedef struct piece Piece;


Piece *create_piece(char *newcard, Color color);
Piece *destroy(Piece *Pack);
Piece *push_piece(Piece *head, Piece *New);
Piece *pop_piece(Piece *head, int n);
Piece *create_pack(Piece *Pack);
void show_pack(Piece *pack);
void switch_piece(Piece *Pack, int Posit1, int Posit2);
void shuffle_pack(Piece *Pack, int Len);

#endif // PACK_H_
