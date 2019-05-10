#include "Screen.h"

Item *createMenuItem(char *content,int size ,int clickable, Screen *nextScreen)
{
	Item* item = (Item*)malloc(sizeof(Item));

	item->content = content;
	item->clickable = clickable;
	item->nextScreen = nextScreen;
	/*int size = 0;
	char c = content[0];
	char *tmp = content;
	while (c != '\0') {
		size++;
		c = tmp++;
	}*/

	item->size = size;

	return item;
}

Menu* createMenuItemsArray(int length)
{
	Menu* menu = (Menu*)malloc(sizeof(Menu));

	if (length > 0) {
		Item** itemArr = (Item**)malloc(sizeof(Item) * length);
		menu->itemArray = itemArr;
		menu->size = length;
		menu->used = 0;
		return menu;
	}
	else {
		free(menu);
	}
	return NULL;
}

int addItemToMenu(Menu *menu,Item *item)
{
	if (NULL == menu || NULL == item || menu->used >= menu->size) {
		return ERROR;
	}

	menu->itemArray[menu->used] = item;
	menu->used++;

	return OK;
}

int removeItemFromArr(Menu *menu,int index)
{
	if (NULL == menu || index >= menu->size || index < 0) {
		return ERROR;
	}

	menu->used--;
	Item *temp = menu->itemArray[index];
	menu->itemArray = NULL;

	deleteItem(temp);

	return OK;
}

/*
int setItemByIndex(Menu *menu, Item *item, int index) {
	if (NULL == menu || NULL == item || index >= menu->size || index < 0) {
		return ERROR;
	}


	if (menu->itemArray[index] != NULL) {
			removeItemFromArr(menu, index);
	}

	menu->used++;
	menu->itemArray[index] = item;

	return OK;
}
*/
Screen *createScreen(int size, Menu *menu)
{
	if (size < 20) {
		return ERROR;
	}

	Screen *screen = (Screen*)malloc(sizeof(Screen));
	screen->size = size;
	screen->menu = menu;
	
	return screen;
}

Screen *createMainMenu() {
	Item *startGame = createMenuItem("START", 6, CLICKABLE, NULL);
	Item *highscores = createMenuItem("HIGHSCORES",11,CLICKABLE, NULL);
	Item *exit = createMenuItem("EXIT", 5, CLICKABLE, NULL);

	Menu *mainMenu = createMenuItemsArray(3);
	
	addItemToMenu(mainMenu, startGame);
	addItemToMenu(mainMenu, highscores);
	addItemToMenu(mainMenu, exit);

	Screen *mainMenuScreen = createScreen(20, mainMenu);
	
	return mainMenuScreen;
}

int printScreen(Screen *screen, int selectedItem, int clicked)
{
	if (NULL == screen) {
		return ERROR;
	}


	char *selectedColor = "\x1b[31m";
	char *resetCodeForColor = "\x1b[0m";

	int offset = 2;
	int menusItemsPrinted = 0;
	int previousYForItem = 0;
	int centerForItem = 0;

	if (screen->menu->used > 0) {
		centerForItem = calculateCenterX(screen, screen->menu->itemArray[0]);
	}

	for (int y = -1; y < screen->size + 1; y++)
	{
		for (int x = -1; x < screen->size + 1; x++)
		{
			if (y == -1 || x == -1 || y == screen->size || x == screen->size) {
				printf("*");
			}
			else if(menusItemsPrinted < screen->menu->used && y == previousYForItem + offset && x == centerForItem){

				if (menusItemsPrinted == selectedItem) {
					printf("%s%s%s",selectedColor, screen->menu->itemArray[menusItemsPrinted]->content,resetCodeForColor);
					if (screen->menu->itemArray[menusItemsPrinted]->content == "START" && clicked == CLICKED) {
						deleteScreen(screen);
						startGame(20);
						return;
					}
				}
				else {
					printf("%s", screen->menu->itemArray[menusItemsPrinted]->content);
				}
				x += screen->menu->itemArray[menusItemsPrinted]->size - 2;

				previousYForItem = y;

				menusItemsPrinted++;

				if (menusItemsPrinted < screen->menu->used) {
					centerForItem = calculateCenterX(screen, screen->menu->itemArray[menusItemsPrinted]);
				}

			}
			else {
				printf(" ");
			}
			
		}
		printf("\n");
	}
}

int deleteScreen(Screen *screen) {
	if (NULL == screen) {
		return ERROR;
	}

	deleteMenu(screen->menu);
	free(screen);

	return OK;
}

int deleteMenu(Menu *menu) {
	if (NULL == menu) {
		return ERROR;
	}

	for (int i = 0; i < menu->size; i++)
	{
		if (menu->itemArray[i] != NULL) {
			deleteItem(menu->itemArray[i]);
		}
	}

	free(menu);

	return OK;
}

int deleteItem(Item *item) {
	if (NULL == item) {
		return ERROR;
	}

	free(item);

	return OK;
}

int calculateCenterX(Screen *screen, Item *item) {
	int centerForItem = ERROR;

	if (screen != NULL && item != NULL) {
		
			centerForItem = (screen->size - item->size) / 2;

	}

	return centerForItem;
}

int updateScreen(Screen *screen) {
	int transition = 0;

	int selectedItem = NOTHING_SELECTED;
	int clicked = UNCLICKED;

	int input = 0;

	if (screen->menu->used > 0) {
		selectedItem = 0;
	}

	while (transition == 0)
	{
		//system("cls");
		printf("\e[1;1H\e[2J");

		printScreen(screen, selectedItem, clicked);
		input = delayForGetInputInScreen(200);

		if (input != 0) {
			if (input == MOVE_TO_BOTTOM_IN_MENU) {
				if (screen->menu->used > 0) {
					selectedItem++;
					if (selectedItem >= screen->menu->used) {
						selectedItem = 0;
					}
				}
			}
			else if (input == MOVE_TO_TOP_IN_MENU) {
				if (screen->menu->used > 0) {
					selectedItem--;
					if (selectedItem < 0) {
						selectedItem = screen->menu->used - 1;
					}
				}
			}
			else if (input == ENTER_IN_MENU) {
				clicked = CLICKED;
				transition = 1;
				printScreen(screen, selectedItem, clicked);
			}
		}
		else {
			clicked = UNCLICKED;
		}
	}
	

}

int getInputInScreen() {
	char c = 0;

	if (_kbhit())

	{
		c = _getch();
	}

	if (c == 's' || c == 'S') {
		return MOVE_TO_BOTTOM_IN_MENU;
	}

	if (c == 'w' || c == 'W') {
		return MOVE_TO_TOP_IN_MENU;
	}
	
	if (c == 'y' || c == 'Y') {
		return ENTER_IN_MENU;
	}
	return 0;
}

int delayForGetInputInScreen(int millis) {
	int startTime = clock();
	int res = 0;
	while (clock() < startTime + millis) {
		res = getInputInScreen();
		if (res != 0) {
			return res;
		}
	}
	return 0;
}

