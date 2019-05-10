#include <stdio.h>
#include "Screen.h"
#include "Highscores.h"
void main() {
	updateScreen(createMainMenu());

	/*
	Score *score1 = createScore("Vetal", 777);
	Score *score2 = createScore("Sasha", 586);
	Score *score3 = createScore("Kolya", 350);
	Score *score4 = createScore("Maxim", 426);

	HighscoresList *list = createHighscoreList();

	addHighsocreToList(score1, list);
	addHighsocreToList(score2, list);
	addHighsocreToList(score3, list);
	addHighsocreToList(score4, list);

	saveHighscoreList(list);

	HighscoresList *resList = createHighscoreList();

	resList = readHighscores();

	printHighscores(resList);
	*/
	system("pause");
}