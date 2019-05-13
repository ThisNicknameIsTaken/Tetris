#pragma once

#include <stdio.h>
#include <string.h>
#include "Meta.h"


#define TOO_SMALL_NAME 8899887
#define NO_HIGHSCORES  2433221

typedef struct tagScore Score;
typedef struct tagHighscoresList HighscoresList;

struct tagScore
{
	char* name;
	int  score;
	Score* next;
	Score* previous;
};

struct tagHighscoresList
{
	int size;
	Score* first;
	Score* last;
};

int	sortHighscores(HighscoresList *highscores);
int printHighscores(HighscoresList *highscores);
int printScore(Score *score);

HighscoresList *readHighscores();

int addHighsocreToList(Score *score, HighscoresList *highscoreList);

int saveHighscoreList(HighscoresList *highscorelist);


HighscoresList *createHighscoreList();
Score *createScore(char *name, int score);

int deleteHighscoreList(HighscoresList *list);
int deleteScore(Score *score);