#include <stdio.h>
#include "Meta.h"
#include "Figures.h"

typedef struct tagField {
	int rows;
	int cols;

	int** fieldArray;
}Field;

Field *createField(int size);
int   **createFieledArray(int size);
int	  deleteField(Field *field);

int freeField(Field *field);
int freeFieldRow(Field *field, int row);
int freeFieldColumn(Field *field, int col);
int freeFieldElement(Field *field, int col, int row);

int *copyFieldRow(Field *field,int row);
int pasteFieldRow(Field *field, int *outRow, int inRow);

int changeElementInFieldArray(Field *field, int col, int row);
int moveElementInArray(Field *field, int outCol, int outRow, int toCol, int toRow); //Вернёт элемент, который стоял в ячйке в которую передвинули

int shiftRowsInArrayToBottom(Field *field, int row);

int fillFieldRowWithOne(Field *field,int row);
int checkEndedLine(Field *field);

void printField(Field *field,Figure *currentFigure,  Figure *nextFigure, int score);
void updateField(Field *field, Figure *currentFigure, Figure *nextFigure, int score);