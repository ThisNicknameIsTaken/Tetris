#include <stdio.h>
#include "Meta.h"
#include "Field.h"
#include <time.h>
#include <conio.h>
#include "Highscores.h"

#define GAME_RUNNING 7700
#define GAME_PAUSED  -8800
#define GAME_OVER	 -6666

#define INFINITY  77777

#define MOVE_TO_RIGHT 245000
#define MOVE_TO_LEFT  255000
#define MOVE_TO_BOTTOM 265000

#define ROTATE_CLOCKWISE	    909000
#define ROTATE_COUNTERCLOCKWISE 808000


#define TOUCH_BOTTOM	34343
#define TOUCH_TOP		43434
#define TOUCH_LEFT		23232
#define TOUCH_RIGHT		32323

#define TOUCH_Y 8888
#define TOUCH_X 7777
#define TOUCH_ELEMENT 5555

int startGame(int size);
int saveResult();
int pauseGame();
int continueGame();
int pauseGame();
int exitGame();

int delay(int millis);
int delayForGetInput(int millis);
int delayAndMove(int millis, Figure *figure, Field *field, Figure *nextFigure, int score);

int checkGameOver(Field *field);

void updateField(Field *field, Figure *currentFigure, Figure *nextFigure, int score);
void gameLoop(Field *field);

Figure *genereteNextFigure(int x, int y);


int saveFigureToField(Field *field, Figure *figure);

int isIntersection(Field *field, Figure *figure);
int getInput();
