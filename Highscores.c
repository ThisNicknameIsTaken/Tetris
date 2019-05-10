#include "Highscores.h"



int	sortHighscores(HighscoresList *highscores);

int printHighscores(HighscoresList *highscores) {
	if (highscores == NULL || highscores->size <= 0) {
		return ERROR;
	}

	Score *score = highscores->first;

	while (score != highscores->last)
	{
		printf("%s : %i\n", score->name, score->score);
		score = score->next;
	}
	printf("%s : %i\n", score->name, score->score);


	return OK;
}

HighscoresList *readHighscores() {
	FILE *file = NULL;
    fopen_s(&file, "Highscore.txt", "r+");
	int fileSize = fseek(file,0l,SEEK_END) - fseek(file,0l,SEEK_SET);

	char *buffer = malloc(sizeof(char) * fileSize);
	char *result;

    fgets(buffer,fileSize,file);
	fclose(file);

	char *nextToken = NULL;

	result = strtok_s(buffer, "\n", &nextToken);
	result = strtok_s(result, " ",&nextToken);

	HighscoresList *list = createHighscoreList();
	Score *score = NULL;

	char *name = NULL;
	int scoreNum;

	for (int i = 0; i < strlen(result); i++)
	{
		printf("%s\n",&result);
	}


	for (int i = 0; i < strlen(result); i++)
	{	
		if (i % 2 == 0) {
			name = result[i];
		}
		else {
			scoreNum = atoi(result[i]);
			score = createScore(name, score);
			addHighsocreToList(score, list);
		}
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
		return OK;
}

int saveHighscoreList(HighscoresList *highscorelist) {
	FILE *fp = NULL;
	fopen_s(&fp, "Highscore.txt", "w+");

	if (highscorelist == NULL || highscorelist->size <= 0) {
		return ERROR;
	}

	Score *score = highscorelist->first;

	while (score != highscorelist->last)
	{
		fprintf(fp,"%s ",score->name);
		fprintf(fp,"%i\n",score->score);
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
	while (score != list->last);
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

	free(score->name);
	free(score);

	return OK;
}