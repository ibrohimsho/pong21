#ifndef _PONG_H_
#define _PONG_H_

#include "common.h"

// player struct definition
typedef struct {
	unsigned short x, y, score;			// x and y coordinates of the paddle and player score
} Player;

// ball struct definition
typedef struct {
	unsigned short x, y, direction;		// x and y coordinates of the ball's location and the direction where it is headed
} Ball;

typedef enum {
	RIGHT_UP, LEFT_UP, RIGHT_DOWN, LEFT_DOWN
} BallDirection;

#define PONG_BOARD_WIDTH 80
#define PONG_BOARD_HEIGHT 25
#define PADDLE_1_LENGTH 3
#define PADDLE_2_LENGTH 3
#define END_SCORE 21		// game ends if a player reaches this score

Player player1 = (Player){11, (PONG_BOARD_HEIGHT-PADDLE_1_LENGTH)/2 + 6, 0}, player2 = (Player){PONG_BOARD_WIDTH + 9, (PONG_BOARD_HEIGHT - PADDLE_2_LENGTH)/2 + 6, 0};
Ball ball = (Ball){PONG_BOARD_WIDTH/2 + 10, PONG_BOARD_HEIGHT/2 + 5, RIGHT_DOWN};
unsigned short game_on_flag_1 = TRUE;

void OpeningScreen1();
void UpdateFrame1();
void PrintBoard1();
void MoveBall();
void ChangeBallDirection();
unsigned short RecordScore1();
void PlayPong();


// welcome screen of the Pong game where the instructions of the game is presented to the player
void OpeningScreen1() {
	system("cls");
	printf( "Welcome to the mini Pong game!"
			"\n\n\nGame instructions:"
			"\n\n-> Use W and S keys to move Player 1's paddle, up and down arrow keys to move Player 2's paddle."
			"\n\n-> Catch the ball by moving your paddle vertically across the left/right side of the table, and bounce the ball back to your opponent's side. If your opponent fails to return the ball, you earn 1 point."
			"\n\n-> The goal is for each player to reach %d points before the opponent."
			"\n\n-> You can pause the game in its middle by pressing the P key. To continue the paused game press P once again."
			"\n\n-> If you want to exit the game at any point press Esc (you will lose all progress)."
			"\n\n\nPress any key to play the game...", END_SCORE);
	if(getch() == ESCAPE_KEY)
		exit(0);
	system("cls");
}

// updates the frame of the Pong game
void UpdateFrame1() {
	unsigned short i;
	for(i=0;game_on_flag_1;i++) {
		Sleep(16);
		if(kbhit()) {				// FPS (frames per second):  1000 (milliseconds in second) / 16 (time interval between frames in milliseconds) = 62.5
			char key = getch();	
			switch(key) {
				case 'A':			// if hit 'Q', move player 1's paddle up by one unit
				case 'a':
					if(player1.y > 6) {
						MoveCursorToXY(player1.x, player1.y + PADDLE_1_LENGTH - 1);
						printf(" ");
						MoveCursorToXY(player1.x, --player1.y);
						printf("%c", 219);
					}
					break;	
				case 'Z':			// if hit 'A', move player 1's paddle down by one unit
				case 'z':
					if(player1.y + PADDLE_1_LENGTH < 5 + PONG_BOARD_HEIGHT) {
						MoveCursorToXY(player1.x, player1.y);
						printf(" ");
						MoveCursorToXY(player1.x, (++player1.y) + PADDLE_1_LENGTH - 1);
						printf("%c", 219);
					}
					break;
				case 'K':		// if hit 'K', move player 2's paddle up by one unit
				case 'k':
					if(player2.y > 6) {
						MoveCursorToXY(player2.x, player2.y + PADDLE_2_LENGTH - 1);
						printf(" ");
						MoveCursorToXY(player2.x, --player2.y);
						printf("%c", 219);
					}
					break;
				case 'M':
				case 'm':		// if hit 'M', move player 2's paddle down by one unit
					if(player2.y + PADDLE_2_LENGTH < 5 + PONG_BOARD_HEIGHT) {
						MoveCursorToXY(player2.x, player2.y);
						printf(" ");
						MoveCursorToXY(player2.x, (++player2.y) + PADDLE_2_LENGTH - 1);
						printf("%c", 219);
					}
					break;
				case PAUSE_KEY:		// pause the game
					do {
						key = getch();
						if(key == ESCAPE_KEY) {
							MoveCursorToXY(0, 5 + PONG_BOARD_HEIGHT);
							exit(0);
						}
					} while(key != PAUSE_KEY);
					break;
				case ESCAPE_KEY:	// exit the game
					MoveCursorToXY(0, 5 + PONG_BOARD_HEIGHT);
					exit(0);
			}
		}
		if(!(i%6)) {				// the ball will move in every 6 frames
			MoveBall();
			ChangeBallDirection();
		}
	}
	system("cls");
	printf( "Game over Player %d!"				// game over
			"\nBetter luck next time."
			"\n(Press C to continue...)", (player1.score == END_SCORE) + 1);
	char key;
	do {
		key = getch();
		if(key == ESCAPE_KEY)
			exit(0);
	} while(key!='c' && key!='C');
	system("cls");
}

// prints the board of the Pong game, including player scores and paddles
void PrintBoard1() {
	MoveCursorToXY(20, 4);
	printf("PLAYER 1: %hu", player1.score);
	MoveCursorToXY(50, 4);
	printf("PLAYER 2: %hu", player2.score);
	unsigned short i;
	for(i=10;i<11+PONG_BOARD_WIDTH;i++) {
		MoveCursorToXY(i, 5);
		printf("_");
		MoveCursorToXY(i, 5 + PONG_BOARD_HEIGHT);
		printf("_");
	}
	for(i=6;i<6+PONG_BOARD_HEIGHT;i++) {
		MoveCursorToXY(10, i);
		printf("|");
		MoveCursorToXY(10 + PONG_BOARD_WIDTH, i);
		printf("|");
	}
	for(i=0;i<PADDLE_1_LENGTH;i++) {
		MoveCursorToXY(player1.x, player1.y + i);
		printf("%c", 219);
	}
	for(i=0;i<PADDLE_2_LENGTH;i++) {
		MoveCursorToXY(player2.x, player2.y + i);
		printf("%c", 219);
	}
}

// moves the ball by one unit in the direction ball is facing
void MoveBall() {
	MoveCursorToXY(ball.x, ball.y);
	printf(" ");
	switch(ball.direction) {	
		case RIGHT_UP:
			ball.x++;
			ball.y--;
			break;
		case LEFT_UP:
			ball.x--;
			ball.y--;
			break;
		case RIGHT_DOWN:
			ball.x++;
			ball.y++;
			break;
		case LEFT_DOWN:
			ball.x--;
			ball.y++;
	}
	MoveCursorToXY(ball.x, ball.y);
	printf("O");
}

// changes the direction of the wall
void ChangeBallDirection() {
	if(ball.y < 7 || ball.y > 3 + PONG_BOARD_HEIGHT)			// if the ball has hit a board wall
		ball.direction += ball.direction<2 ? 2 : -2;
	if(ball.x <= player1.x + 1) {								// if the ball has hit player 1's paddle
		if(player1.y <= ball.y && ball.y < player1.y + PADDLE_1_LENGTH)
			ball.direction += ball.direction%2 ? -1 : 1;
		else {
			MoveCursorToXY(ball.x, ball.y);
			printf("X");
			Sleep(400);
			printf("\b ");
			ball.x = PONG_BOARD_WIDTH/2 + 10;
			ball.y = rand()%(PONG_BOARD_HEIGHT - 3) + 7;
			ball.direction = rand()%4;
			MoveCursorToXY(60, 4);
			printf("%hu", ++player2.score);
			if(player2.score == END_SCORE)
				game_on_flag_1 = FALSE;
		}
	}
	else if(ball.x >= player2.x - 1) {							// if the ball has hit player 2's paddle
		if(player2.y <= ball.y && ball.y < player2.y + PADDLE_2_LENGTH)
			ball.direction += ball.direction%2 ? -1 : 1;
		else {
			MoveCursorToXY(ball.x, ball.y);
			printf("X");
			Sleep(400);
			printf("\b ");
			ball.x = PONG_BOARD_WIDTH/2 + 10;
			ball.y = rand()%(PONG_BOARD_HEIGHT - 3) + 7;
			ball.direction = rand()%4;
			MoveCursorToXY(30, 4);
			printf("%hu", ++player1.score);
			if(player1.score == END_SCORE)
				game_on_flag_1 = FALSE;
		}
	}
}
// the main function to play Pong
void PlayPong() {
	unsigned short play_again_flag = FALSE;
	do {
		OpeningScreen1();
		PrintBoard1();
		UpdateFrame1();
	} while(play_again_flag);
}

#endif
