#include "Figures.h"



Figure *createFigure(int x, int y,int figureCode) {
	
	Figure *figure;

	switch (figureCode) {
	case LINE:
		figure = createLine(x,y);
		break;

	case SQUARE:
		figure = createSquare(x, y);
		break;

	case L_RIGHT:
		figure = createLRight(x, y);
		break;

	case L_LEFT:
		figure = createLLeft(x, y);
		break;

	case Z_RIGHT:
		figure = createZRight(x, y);
		break;

	case Z_LEFT:
		figure = createZLeft(x, y);
		break;

	case LINE_D:
		figure = createDLine(x, y);
		break;

	default:
		return ERROR;
		break;
	}
} 


int deleteFigure(Figure *figure) {
	if (figure != NULL) {
		free(figure->dotArray);
		
		free(figure);
		return OK;
	}
	return ERROR;
}




Figure *createLine(int x, int y) {
	Figure *figure = createBlankFigure(4);
	
	figure->line = 1;
	figure->x = x;
	figure->y = y;

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (i == 0) {
				figure->dotArray[j][i] = 1;
			}
			else {
				figure->dotArray[j][i] = 0;
			}
		}
	}

	return figure;
}

Figure *createSquare(int x, int y) {
	Figure *figure = createBlankFigure(2);

	figure->x = x;
	figure->y = y;


	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			figure->dotArray[i][j] = 1;
		}
	}

	return figure;
}

Figure *createLLeft(int x, int y) {
	Figure *figure = createBlankFigure(3);

	figure->x = x;
	figure->y = y;

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (i == 1) {
				figure->dotArray[j][i] = 1; // [y][x]
			}
			else {
				figure->dotArray[j][i] = 0;
			}
		}
	}

	figure->dotArray[2][0] = 1;


	return figure;
}

Figure *createLRight(int x, int y) {
	Figure *figure = createBlankFigure(3);

	figure->x = x;
	figure->y = y;


	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (i == 1) {
				figure->dotArray[j][i] = 1; // [y][x]
			}
			else {
				figure->dotArray[j][i] = 0;
			}
		}
	}

	figure->dotArray[2][2] = 1;


	return figure;
}

Figure *createZLeft(int x, int y) {
	Figure *figure = createBlankFigure(3);

	figure->x = x;
	figure->y = y;


	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (j == 0 && i > 0) {
				figure->dotArray[i][j] = 1;
			}
			else if (j == 1 && i < 2) {
				figure->dotArray[i][j] = 1;
			}
			else {
				figure->dotArray[i][j] = 0;
			}
		}
	}
	return figure;
}

Figure *createZRight(int x, int y) {
	Figure *figure = createBlankFigure(3);

	figure->x = x;
	figure->y = y;


	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (j == 0 && i < 2) {
				figure->dotArray[i][j] = 1;
			}
			else if (j == 1 && i > 0) {
				figure->dotArray[i][j] = 1;
			}
			else {
				figure->dotArray[i][j] = 0;
			}
		}
	}

	return figure;
}

Figure *createDLine(int x, int y) {
	Figure *figure = createBlankFigure(3);

	figure->x = x;
	figure->y = y;

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (i == 0) {
				figure->dotArray[j][i] = 1; //[y][x]
			}
			else {
				figure->dotArray[j][i] = 0;
			}
		}
	}

	figure->dotArray[1][1] = 1;

	return figure;
}

Figure *createBlankFigure(int size) {
    Figure *figure = malloc(sizeof(Figure));
	int **arr = (int *)malloc(sizeof(int)  * size);

	for (int i = 0; i < size; i++)
	{
		arr[i] = malloc(sizeof(int) * size);
	}

	figure->size = size;
	figure->dotArray = arr;
	figure->line = 0;

	return figure;
}

int rotateFigure(Figure *figure, int clockwise) {
	if (figure == NULL && (clockwise != COUNTERCLOCKWISE || clockwise != CLOCKWISE)) {
		return ERROR;
	}
	int size = figure->size;
	int **arr = figure->dotArray;

	if (figure->line == 0) {
		if (clockwise == CLOCKWISE) {
			for (int x = 0; x < size / 2; x++)
			{
				// Consider elements in group of 4 in  
				// current square 
				for (int y = x; y < size - x - 1; y++)
				{
					// store current cell in temp variable 
					int temp = arr[x][y];

					// move values from right to top 
					arr[x][y] = arr[y][size - 1 - x];

					// move values from bottom to right 
					arr[y][size - 1 - x] = arr[size - 1 - x][size - 1 - y];

					// move values from left to bottom 
					arr[size - 1 - x][size - 1 - y] = arr[size - 1 - y][x];

					// assign temp to left 
					arr[size - 1 - y][x] = temp;
				}
			}
		}
		else {
			for (int x = 0; x < size / 2; x++)
			{
				// Consider elements in group of 4 in  
				// current square 
				for (int y = x; y < size - x - 1; y++)
				{
					int temp = arr[y][size - 1 - x];

					// move values from top to right 
					arr[y][size - 1 - x] = arr[x][y];

					// move values from left to top 
					arr[x][y] = arr[size - 1 - y][x];

					// move values from bottom to left 
					arr[size - 1 - y][x] = arr[size - 1 - x][size - 1 - y];

					// assign temp to left 
					arr[size - 1 - x][size - 1 - y] = temp;
				}
			}
		}
	}
	else {
		int temp = 0;
		for (int i = 0; i < 1; i++)
		{
			for (int j = 0; j < size; j++)
			{
				temp = figure->dotArray[i][j];
				figure->dotArray[i][j] = figure->dotArray[j][i];
				figure->dotArray[j][i] = temp;
			}
		}
	}
	
	return OK;
}

Figure *moveFigure(Figure *figure, int deltaX, int deltaY) {
	figure->x += deltaX;
	figure->y += deltaY;
}

void printFigureDEBUG(Figure *figure) {

	for (int i = 0; i < figure->size; i++)
	{
		for (int j = 0; j < figure->size; j++)
		{
			if (figure->dotArray[i][j] == 1) {
				printf("*");
			}
			else {
				printf(" ");
			}
		}
		printf("\n");
	}
		printf("\n");
}

void printFigureDEBUGInCell(Figure *figure) {
	int tempX = 0;
	int tempY = 0;

	for (int x = -4; x < 4; x++)
	{
		for (int y = -4; y < 4; y++)
		{
			if (x - figure->x >= 0 && x - figure->x < figure->size && y - figure->y >= 0 && y - figure->y < figure->size) {
				tempX = x - figure->x;
				tempY = y - figure->y;
				if (figure->dotArray[tempY][tempX] == 1) {
					printf("*");
				}
				else {
					printf("-");
				}
			}
			else {
				printf("-");
			}
		}

		printf("\n");
	}
}


int printFigureInField(Figure *figure, int fieldX, int fieldY) {
	for  (int x = 0; x < figure->size; x++)
	{
		for (int y = 0; y  < figure->size; y++)
		{
			if (figure->x + x == fieldX && figure->y + y == fieldY) {
				if (figure->dotArray[x][y] == 1) {
					printf("\x1b[31m*\x1b[0m"); // redCode*resetCode
					return 1;
				}
			}
		}
	}
	return 0;
}

