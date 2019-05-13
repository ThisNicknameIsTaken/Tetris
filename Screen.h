#include "stdio.h"
#include "Meta.h"
#include "Game.h"


#define CLICKABLE	11112222
#define UNCLICKABLE 22221111

#define CLICKED		 9898899
#define UNCLICKED   -9998889

#define NOTHING_SELECTED -66551122

#define MOVE_TO_BOTTOM_IN_MENU 11221122
#define MOVE_TO_TOP_IN_MENU	   22112211
#define ENTER_IN_MENU		   77777777
#define BACK				   88772112
#define OPEN_MENU			   86272561
#define EXIT				   66666666

typedef struct tagMenu Menu;
typedef struct tagScreen Screen;
typedef struct menuItem Item;

struct menuItem {
	char *content;
	int size;
	int clickable;
	Screen *nextScreen;
};

 struct tagMenu {
	int size;
	int used;
	Item **itemArray;
};

struct tagScreen {
	int size; // min 20
	Menu *menu;
};

Item *createMenuItem(char *content,int size, int clickable, Screen *screen);
Menu *createMenuItemsArray(int length);

int addItemToMenu(Menu *menu,Item *item);
int removeItemFromArr(Menu *menu,int index);
//int setItemByIndex(Menu *menu,Item *item, int index);

Screen *createScreen(int size, Menu *menu);

Screen *createMainMenu();

int calculateCenterX(Screen *screen, Item *item);
int printScreen(Screen *screen, int selectedItem, int clicked);

int deleteScreen(Screen *screen);
int deleteMenu(Menu *menu);
int deleteItem(Item *item);

int delayForGetInputInScreen(int millis);
int updateScreen(Screen *screen);
int getInputInScreen();

int showHighscores(HighscoresList *list);