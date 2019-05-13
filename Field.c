#include "Field.h"

Field *createField(int size) {
	Field *field = (Field *)malloc(sizeof(Field));
	
	field->cols = size;
	field->rows = size;

	if (size > 0 && size > 0) {
		field->fieldArray = createFieledArray(size);
	}
	else {
		return ERROR;
	}
	return field;
}

int **createFieledArray(int size) {
	if (size > 0 && size > 0) {
		int **array = malloc(sizeof(int) * size);

		for (int i = 0; i < size; i++)
		{
			array[i] = malloc(size * sizeof(int));
		}

		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				array[i][j] = 0;
			}
		}
		return array;
	}
	else {
		return ERROR;
	}
}


int	deleteField(Field *field) {
	free(field);
	return OK;
}

int freeField(Field *field) {
	if (field->fieldArray != NULL) {
		for (int i = 0; i < field->cols; i++)
		{
			for (int j = 0; j < field->rows; j++)
			{
				field->fieldArray[i][j] = 0;
			}
		}
	}
	else {
		return ERROR;
	}
	return OK;
}

int freeFieldRow(Field *field, int row) {
	if (field->fieldArray != NULL && field->rows >= row) {
		for (int i = 0; i < field->cols; i++)
		{
				field->fieldArray[row][i] = 0;
		}
	}
	else {
		return ERROR;
	}
	return OK;
}

int freeFieldColumn(Field *field, int col) {
	if (field->fieldArray != NULL && field->cols >= col) {
		for (int i = 0; i < field->rows; i++)
		{
			field->fieldArray[col][i] = 0;
		}
	}
	else {
		return ERROR;
	}
	return OK;
}

int freeFieldElement(Field *field, int col, int row) {
	if (field->fieldArray != NULL && field->cols >= col && field->rows >= row) {
			field->fieldArray[col][row] = 0;
	}
	else {
		return ERROR;
	}
	return OK;
}

int changeElementInFieldArray(Field *field, int col, int row) {
	if (field->fieldArray != NULL && field->cols >= col && field->rows >= row) {
		if (field->fieldArray[col][row] == 0) {
			field->fieldArray[col][row] = 1;
		}
		else {
			field->fieldArray[col][row] = 0;
		}
	}
	else {
		return ERROR;
	}
	return OK;
}

int moveElementInArray(Field *field, int outCol, int outRow, int toCol, int toRow) {
	int outMovedElement = 0;
	if (field->fieldArray != NULL && field->cols >= outCol && field->rows >= outRow && field->cols >= toCol && field->rows >= toRow) {
		outMovedElement = field->fieldArray[toCol][toRow];
		field->fieldArray[toCol][toRow] = field->fieldArray[outCol][outRow];
		field->fieldArray[outCol][outRow] = 0;
	}
	else {
		return ERROR;
	}
	return outMovedElement;
}

int shiftRowsInArrayToBottom(Field *field, int row) {	
	if (field == NULL || row < 0 || row > field->rows) {
		return ERROR;
	}
	
	int *tempNextRow;
	int *tempCurrentRow;
	if (row >= field) {
		freeFieldRow(field,row);
	}
	else {
		freeFieldRow(field, row);
		for (int i = row; i >= 0; i--)
		{	
			if (i != 0) {
				tempCurrentRow = copyFieldRow(field, i);
				tempNextRow = copyFieldRow(field, i - 1);
				pasteFieldRow(field, tempNextRow, i);
			}

		}
	}

	/*
	int *tempRow= malloc(sizeof(int) * field->cols);
	int *tempRowTwo = malloc(sizeof(int) * field->cols);
	tempRow = copyFieldRow(field, 0);


	for (int i = row; i < field->rows; i++)
	{
		if (row == field->rows){
			freeFieldRow(field, i);
		}
		else {
			tempRowTwo = copyFieldRow(field, row + 1);
			pasteFieldRow(field, tempRow, row + 1);
			tempRow = tempRowTwo;
		}
	}

	*/
	return OK;
}


int *copyFieldRow(Field *field, int row) {
	int *tempRow = malloc(sizeof(int) * field->cols);
	if (field->rows > row) {
		for (int i = 0; i < field->cols; i++)
		{
			tempRow[i] = field->fieldArray[row][i];
		}
		return tempRow;
	}
	else {
		free(tempRow);
		return ERROR;
	}
}


int pasteFieldRow(Field *field, int *outRow, int row) {
	if (field == NULL || outRow == NULL || row  < 0 || row > field->rows) {
		return ERROR;
	}
		for (int i = 0; i < field->cols; i++)
		{
			field->fieldArray[row][i] = outRow[i];
		}
		
		return OK;
}

int fillFieldRowWithOne(Field *field, int row) {
	if (field->fieldArray != NULL) {
		
			for (int i = 0; i < field->cols; i++)
			{
				field->fieldArray[row][i] = 1;
			}
	}
	else {
		return ERROR;
	}
	return OK;
}


void printField(Field *field,Figure *currentFigure, Figure *nextFigure, int score) {
	int okNext = 0;
	int okCurrent = 0;

	if (field->cols < 7) {
		printf("Minimum 7 cols (rows - everything is inverted)\n"); //y == cols
		return ERROR;
	}
	for (int i = -1; i < field->cols + 1; i++) //y
	{
		for (int j = -1; j < field->rows + 8; j++) //x
		{

			if (i >= 2 && j >= field->rows + 1) {
				okNext = printFigureInField(nextFigure, j, i);
			}

			if (i >= 0 && i < field->cols && j >= 0 && j < field->rows) {
				okCurrent = printFigureInField(currentFigure, j, i);
			}

			if (i == -1 || j == -1 || (i == field->cols && j < field->rows) || j == field->rows || (j == field->rows + 7 && i != 0 && i < 6) || (j > field->rows && i == 5))
			{
				printf("*");
			}
			else if (j == field->rows + 2 && i == 0)
			{
				printf("NEXT *");
			}
		   else if (i >= 0 && j >= 0 && i < field->cols && j < field->rows && okCurrent == 0)
			{
				if (field->fieldArray[i][j] == 1) {
					printf("*");
				}
				else {
					printf(" ");
				}
			}
		   else {
				if (okCurrent == 0)
			    {
					printf("");
				}
			    if (okNext == 0 && j >= field->rows) {
					printf(" ");
				}
			   
					okCurrent = 0;
					okNext = 0;
				
			}
			
			
		}
		printf("\n");
	}
	printf("\nSCORE : \x1b[31m%i\x1b[0m \n", score);
}

int checkEndedLine(Field *field) {
	if (field == NULL) {
		return ERROR;
	}
	
	int counter = 0;
	for (int i = field->cols - 1; i >= 0; i--) {
		for (int j = 0; j < field->rows; j++)
		{
			
			if (field->fieldArray[i][j] == 1) {
				counter++;
			}else{
				break;
			}

			if (counter == field->cols) {
				return i;
			}
		}
		counter = 0;
	}

	return OK;
}