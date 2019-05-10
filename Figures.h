#include <stdio.h>
#include "Meta.h"

//rotateCodes

#define CLOCKWISE 252525
#define COUNTERCLOCKWISE 262626

//figureCodes			 Приблизительный вид
#define LINE	11000 // I
#define SQUARE	11001 // II
#define L_RIGHT 11002 // L
#define L_LEFT  11003 // inverse L
#define Z_RIGHT 11004 // Z
#define Z_LEFT  11005 // inverse Z
#define LINE_D	11006 // Line with dot in middle

typedef struct tagFigure {
	int x, y;
	int line;
	int size;
	int **dotArray;
}Figure;

Figure *createFigure(int x, int y, int figureCode); //Позиция при создании всегда вертикальна
int		deleteFigure(Figure *figure);


Figure *createLine(int x, int y);
Figure *createSquare(int x, int y);
Figure *createLLeft(int x, int y);
Figure *createLRight(int x, int y);
Figure *createZLeft(int x, int y);
Figure *createZRight(int x, int y);
Figure *createDLine(int x, int y);

Figure *createBlankFigure(int size);


int rotateFigure(Figure *figure, int clokwise);
Figure *moveFigure(Figure *figure, int deltaX, int deltaY);

int printFigureInField(Figure *figure, int fieldX, int fieldY);
void printFigureDEBUG(Figure *figure); //Debug ONLY!