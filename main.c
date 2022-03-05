#include "Header/pong.h"

typedef enum {
	PONG = '1', SNAKE, SPACE_INVADERS, TETRIS
} ArcadeGames;

int main() {
	srand((unsigned int)time(NULL));
	while(TRUE) {
		printf( "Press 1 to play Pong.\nPress Esc to exit.");
		char choose_game = getch();
		switch(choose_game) {
			case PONG:
				PlayPong();					// play Pong
				break;
			case ESCAPE_KEY:
				return 0;					// exit game
		}
		system("cls");
	}
	return 0;
}
