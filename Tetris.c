#include "Tetris.h"

int play() {
	int gameState = 0;
	while (1) {
		gameState = updateScreen(createMainMenu());
		if (gameState == OPEN_MENU ) {
			gameState = updateScreen(createMainMenu());
		}
		if (gameState == EXIT) {
			system("cls");
			return 1;
		}
	}
}