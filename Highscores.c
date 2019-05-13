#include "Highscores.h"



int	sortHighscores(HighscoresList *highscores) {
	if (highscores == NULL) {
		return ERROR;
	}

	if (highscores->size <= 1) {
		return OK;
	}
	Score *current;
	Score *next;

	int scoreNum = 0;
	char *name;

	int flag = 1;

	while (flag == 1)
	{
		current = highscores->first;
		next = current->next;
		flag = 0;
		while (next)
		{
			if ((current->score) < (next->score))
			{
				scoreNum = current->score;
				name = current->name;

				current->name = next->name;
				current->score = next->score;

				next->name = name;
				next->score = scoreNum;
				flag = 1;
			}
			current = current->next;
			next = next->next;
		}
	}
	return OK;
}

int printHighscores(HighscoresList *highscores) {
	if (highscores == NULL || highscores->size <= 0) {
		return ERROR;
	}

	sortHighscores(highscores);

	Score *score = highscores->first;

	while (score != highscores->last)
	{
		printScore(score);
		score = score->next;
	}
	printScore(score);


	return OK;
}

int printScore(Score *score) {
	if (score == NULL) {
		return ERROR;
	}
	printf("%s : %i\n", score->name, score->score);
	return OK;
}

HighscoresList *readHighscores() {
	FILE *file = NULL;
    fopen_s(&file, "Highscore.txt", "r+");

	fseek(file, 0l, SEEK_END);		
	int fileSize = ftell(file);
	fseek(file, 0l, SEEK_SET);

	if (fileSize == 0) {
		return NO_HIGHSCORES;
	}

	char *buffer = malloc(sizeof(char) * fileSize);
	char *result;

    fgets(buffer,fileSize,file);
	fclose(file);

	HighscoresList *list = createHighscoreList();
	Score *score = NULL;

	char *nextToken = NULL;
	char *delimeters = " ;";

	result = strtok_s(buffer,delimeters,&nextToken);

	char *name = NULL;
	int scoreNum;

	for (int i = 0; result != NULL; i++)
	{	
		if (i % 2 == 0) {
			name = result;
		}
		else {
			scoreNum = atoi(result);
			score = createScore(name, scoreNum);
			addHighsocreToList(score, list);
		}
		result = strtok_s(NULL, delimeters, &nextToken);
	}


	return list;
}

int addHighsocreToList(Score *score, HighscoresList *highscoreList) {
	if (score == NULL || highscoreList == NULL) {
		return ERROR;
	}

		if (highscoreList->size == 0) {
			highscoreList->first = score;
			highscoreList->last = score;

		}
		else {
			highscoreList->last->next = score;
			score->previous = highscoreList->last;
			highscoreList->last = score;

			score->next = NULL;
		}
		highscoreList->size++;

		saveHighscoreList(highscoreList);

		return OK;
}

int saveHighscoreList(HighscoresList *highscorelist) {
	FILE *fp = NULL;
	fopen_s(&fp, "Highscore.txt", "w+");

	if (highscorelist == NULL || highscorelist->size <= 0) {
		return ERROR;
	}

	Score *score = highscorelist->first;

	while (score != NULL)
	{
		fprintf(fp,"%s ",score->name);
		fprintf(fp,"%i; ",score->score);
		score = score->next;
	}

	fclose(fp);
	return OK;
}

HighscoresList *createHighscoreList() {
	HighscoresList *list = (HighscoresList *)malloc(sizeof(HighscoresList));
	list->first = NULL;
	list->last = NULL;
	list->size = 0;

	return list;
}

Score *createScore(char *name, int scoreNum){
	if (name == NULL || scoreNum <= 0) {
		return ERROR;
	}

	if (strlen(name) < 1) {
		return TOO_SMALL_NAME;
	}

    Score *score = (Score*)malloc(sizeof(Score));
	score->name = name;
	score->score = scoreNum;

	score->next = NULL;
	score->previous = NULL;
	
	return score;

}

int deleteHighscoreList(HighscoresList *list) {
	if (list == NULL) {
		return ERROR;
	}

	if (list->size == 0) {
		free(list);
		return OK;
	}

	Score *score = list->first;
	Score *tmp;
	while (score != list->last)
	{
		tmp = score->next;
		deleteScore(score);
		score = tmp;
	}

	if (score != NULL) {
		deleteScore(score);
	}

	free(list);
	return OK;
}

int deleteScore(Score *score) {
	if (score == NULL) {
		return ERROR;
	}
	free(score);

	return OK;
}