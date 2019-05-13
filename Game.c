#include "Game.h"


int GameState = GAME_PAUSED;

int gameLoop(Field *field) {
	
	int width = field->rows;
	int height = field->cols;

	int nextFigureX = width + 2;
	int nextFigureY = 2;

	int currentFigureX = width / 2 - 2;
	int currentFigureY = 0;

	int firstStart = 0;

	Figure *nextFigure = genereteNextFigure(nextFigureX, nextFigureY);
	Figure *currentFigure = genereteNextFigure(currentFigureX, currentFigureY);


	int dy = 1;
	int dx = 0;

	int  movementRes = 0;
	int  intersectionRes = 0;
	int  checkLineRes = OK;
	
	int score = 0;
	int isGameOver = 0;
	int isGameExit = 0;

	while (INFINITY) {
		if (GameState == GAME_OVER) {
			deleteField(field);

			if (currentFigure != NULL) {
				deleteFigure(currentFigure);
			}

			if (nextFigure != NULL) {
				deleteFigure(nextFigure);
			}
			system("cls");
			return score;
		}

		if (GameState == GAME_EXIT) {
			deleteField(field);

			if (currentFigure != NULL) {
				deleteFigure(currentFigure);
			}

			if (nextFigure != NULL) {
				deleteFigure(nextFigure);
			}
			system("cls");
			return GAME_EXIT;
		}

		while (GameState == GAME_RUNNING) {
			isGameOver = checkGameOver(field);

			if (isGameOver == 1) {
				GameState = GAME_OVER;
				break;
			}

			if (isGameExit == 1) {
				GameState = GAME_EXIT;
				return GameState;
				break;
			}

			updateField(field, currentFigure, nextFigure, score);

			if (firstStart == 0) {
				deleteFigure(nextFigure);
				nextFigure = genereteNextFigure(nextFigureX, nextFigureY);
				firstStart = 1;
			}

			intersectionRes = isIntersection(field, currentFigure);

			if (intersectionRes == TOUCH_BOTTOM || intersectionRes == TOUCH_ELEMENT) {
				saveFigureToField(field, currentFigure);

				deleteFigure(currentFigure);
				currentFigure = nextFigure;

				currentFigure->x = currentFigureX;
				currentFigure->y = currentFigureY;

				nextFigure = genereteNextFigure(nextFigureX, nextFigureY);
			}

			
			if (delayAndMove(500, currentFigure, field, nextFigure, score) == GAME_EXIT) {
				isGameExit = 1;
			}

			checkLineRes = checkEndedLine(field);

			if (checkLineRes != OK && checkLineRes != ERROR) {
				shiftRowsInArrayToBottom(field, checkLineRes);
				score += 10;
			}
		}
		
	}

	return score;
}

int startGame(int size) {
	Field *field = createField(size);
	GameState = GAME_RUNNING;
	int score;
	score = gameLoop(field);
	
	return score;
}

int pauseGame() {
	GameState = GAME_PAUSED;
	return GameState;
}

int continueGame() {
	GameState = GAME_RUNNING;
	return GameState;
}

Figure *genereteNextFigure(int x, int y) {
	srand(time(NULL));

	int max = LINE_D;
	int min = LINE;
	Figure *figure;

	int figureType = (rand() % (max - min + 1)) + min;

	figure = createFigure(x, y, figureType);
	return figure;
}

int isIntersection(Field *field, Figure *figure) {
		if (field == NULL || figure == NULL) {
			return ERROR;
		}


		for (int y = figure->y; y < figure->y + figure->size; y++) // y
		{
			for (int x = figure->x; x < figure->x + figure->size; x++) //x
			{
				
				
				if (y + 1 < field->cols && (field->fieldArray[y + 1][x] == 1 && figure->dotArray[x - figure->x][y - figure->y] == 1)) {
					return TOUCH_ELEMENT;
				}
				else if (figure->dotArray[x - figure->x][y - figure->y] == 1 && x <= -1) {
					return TOUCH_LEFT;
				}
				else if (figure->dotArray[x - figure->x][y - figure->y] == 1 && x >= field->rows) {
					return TOUCH_RIGHT;
				}else if (figure->dotArray[x - figure->x][y - figure->y] == 1 && (y >= field->cols - 1)) {
					return TOUCH_BOTTOM;
				}
			}
		}
		

	
	return 0;
}

int saveFigureToField(Field *field, Figure *figure) {
	if (field == NULL || figure == NULL) {
		return ERROR;
	}


	for (int y = figure->y; y < figure->y + figure->size; y++) // y
	{
		for (int x = figure->x; x < figure->x + figure->size; x++) //x
		{
			if (figure->dotArray[x - figure->x][y - figure->y] == 1 && y < field->rows) {
				field->fieldArray[y][x] = figure->dotArray[x - figure->x][y - figure->y];
			}
		}
	}

	return OK;
}

int getInput() {
	char c = 0;

	if (_kbhit())

	{
		c = _getch();
	}

	if (c == 's' || c == 'S') {
		return MOVE_TO_BOTTOM;
	}
	
	if (c == 'a' || c == 'A') {
		return MOVE_TO_LEFT;
	}

	if (c == 'd' || c == 'D') {
		return MOVE_TO_RIGHT;
	}

	if (c == 'e' || c == 'E') {
		return ROTATE_CLOCKWISE;
	}

	if (c == 'q' || c == 'Q') {
		return ROTATE_COUNTERCLOCKWISE;
	}

	if (c == 'b' || c == 'B') {
		return GAME_EXIT;
	}
	return 0;
}

int delay(int millis) {
	int startTime = clock();
	while (clock() < startTime + millis) {
	}
	return 1;
}

int delayForGetInput(int millis) {
	int startTime = clock();
	int res = 0;
	while (clock() < startTime + millis) {
		res = getInput();
		if (res != 0) {
			return res;
	  }
	}
	return 0;
}

int delayAndMove(int millis, Figure *figure, Field *field, Figure *nextFigure, int score) {
	int movementRes = 0;
	int dx = 0;
	int dy = 0;

	int rotation = 0;

	int intersection = 0;
	int startTime = clock();

	int loopEnd = 0;

	while (clock() < startTime + millis) {
		movementRes = getInput();
		if (movementRes!= 0) {
					
				if (movementRes == GAME_EXIT) {
					return movementRes;
				}

				if (movementRes == MOVE_TO_BOTTOM) {
					dx = 0;
					dy = 1;
				}

				if (movementRes == MOVE_TO_LEFT) {
					dx = -1;
					dy = 0;
				}

				if (movementRes == MOVE_TO_RIGHT) {
					dx = 1;
					dy = 0;
				}

				if (movementRes == ROTATE_CLOCKWISE) {
					rotation = CLOCKWISE;
					dy = 0;
				}

				if (movementRes == ROTATE_COUNTERCLOCKWISE) {
					rotation = COUNTERCLOCKWISE;
					dy = 0;
				}

				moveFigure(figure, dx, dy);
				if (rotation != 0) {
					rotateFigure(figure, rotation);
				}
				
				intersection = isIntersection(field, figure);
				if (intersection == TOUCH_BOTTOM|| intersection == TOUCH_ELEMENT || intersection == TOUCH_LEFT || intersection == TOUCH_RIGHT) {
					moveFigure(figure, dx * (-1), dy * (-1));

					if (intersection == TOUCH_RIGHT) {
						for (int y = figure->y; y < figure->y + figure->size; y++) {
								for (int x = figure->x + figure->size; x > figure->x; x--)
								{
									if (figure->dotArray[figure->x + figure->size - x][y - figure->y] == 1 && x >= field->rows) {
										moveFigure(figure,(x - field->rows) * (-1), 0);
										loopEnd = 1;
										break;
									}
								}
								if (loopEnd == 1) break;
						}
					}else if (intersection == TOUCH_LEFT) {
						for (int y = figure->y; y < figure->y + figure->size; y++) {
							for (int x = figure->x; x < figure->x + figure->size; x++)
							{
								if (figure->dotArray[x - figure->x][y - figure->y] == 1 && x <= -1) {
									moveFigure(figure,x * -1, 0);
									loopEnd = 1;
									break;
								}
							}
							if (loopEnd == 1) break;
						}
					}
					else if (intersection == TOUCH_BOTTOM) {
							for (int x = figure->x; x < figure->x + figure->size; x++)
							{
								for (int y = figure->y + figure->size; y > figure->y; y--) {
								if (figure->dotArray[x - figure->x][y - figure->y] == 1 && y >= field->cols - 1) {
									moveFigure(figure, 0, (y - field->cols + 1) * - 1);
									loopEnd = 1;
									break;
								}
							}
							if (loopEnd == 1) break;
						}
					}

					loopEnd = 0;
					

				}

				updateField(field, figure, nextFigure, score);
				

				movementRes = 0;
				rotation = 0;
			}
	}
	dy = 1;
	dx = 0;
	moveFigure(figure, dx, dy);

	return 0;
}

int checkGameOver(Field * field)
{
	for (int x = 0; x < field->rows; x++)
	{
		if (field->fieldArray[1][x] == 1) return 1;
	}
	return 0;
}

Score *saveResult(int scoreNum) {
	system("cls");
	if (scoreNum <= 0) {
		return NULL;
	}
	char name[256];
	while (strlen(name) < 3) {
		printf("Your score \x1b[31m%i\x1b[0m \n\n\n Please, input your name, min 3, max 255 letters:", scoreNum);
		scanf_s("%s", &name,256);
	}

	Score *score = createScore(name, scoreNum);
	return score;
}

void updateField(Field *field, Figure *currentFigure, Figure *nextFigure, int score) {
	system("cls");
	printField(field, currentFigure, nextFigure, score);
}