#include <ncurses.h>
#include <iostream>
#include <fstream>
#include <string>

// Let the monkeys be everywhere:
// User is playing as a monkey in an air baloon and fights against enemy monkeys
class Monkey 
{
private:
	bool alive;
	int y, x;			// The coordiantes of the top left corner of the object's window
	const int height, width;	// The dimensions of the object's window	
public:
	Monkey(int _y, int _x, int _h, int _w): alive{true}, y{_y}, x{_x}, height{_h}, width{_w}
	{}
	
	bool isHitted();		// Check all of the cells whether they intersect with external objects
	void show();
};

class Player: public Monkey
{
private:
	int points;			// The amount of points earned by player
	int fuel; 			// The amount of fuel to raise the baloon higher 
public:
	Player(int _y, int _x, int _h = 5, int _w = 5): Monkey(_y, _x, _h, _w), points{0}, fuel{100}
	{}
	
	void movePlayer();
};

class Enemy: public Monkey
{
private:
	int reward;			// The reward for destroying
	const double delay; 		// The delay of shooting
public:
	Enemy(int _y, int _x, int _h, int _w): Monkey(_y, _x, _h, _w), reward{100}, delay{0}
	{}
	~Enemy()
	{}
};


void showTitle();			// Show the title of the game
void showStartMenu(int _idx = 0);	// Show start menu with 4 options
void startMenu(); 			// Do command in start menu due to user's input
void showGameMenu(int _idx = 0); 	// Show "PLAY" menu with some options
void gameMenu(); 			// Do command in "PLAY" menu due to user's input
void showHelp(int _idx = 0); 		// Show "HELP" window with helpful information
void help(); 				// Do command in "HELP" menu due to user's input
void showHallOfFame(int _idx = 0);	// Show "HALL OF FAME" window with top results of the game
void hallOfFame(); 			// Do command in "HALL OF FAME" menu due to user's input
void showSettings(int _idx = 0);	// Show "SETTINGS" window with 3 different difficulty levels
void settings();			// Do command in "SETTINGS" menu due to user's input
void setParams();			// Set parametres of the game due to difficulty level

int choice{0};				// A varibale to detect user's behaviour
int tuneX{2};				// A variable to tune output position on the X-axis
int tuneY{0};				// A variable to tune output position on the Y-axis

using namespace std;

int main()
{
	// Setting initial parameters
	initscr();
	noecho();			// To not see what user types
	curs_set(0);			// To make cursor invincible
	keypad(stdscr, true);		// To work with arrows
	
	// Main procces	
	showStartMenu();	

	return 0;
}

void showTitle()
{	
	// Get screen size
	int yMax, xMax;
	getmaxyx(stdscr, yMax, xMax);

	// Read and print a file with the title 
	ifstream fRead;
	string line;
	int idx{0};
	fRead.open(".game/sprites/title");
	while (getline(fRead, line))
	{
		mvprintw(yMax/4 + idx, xMax/3 - 5 + tuneX, line.c_str());
		idx += 1;
	}
	fRead.close();
	refresh();
}

void showStartMenu(int _idx)
{	
	// Get screen size
	int yMax, xMax;
	getmaxyx(stdscr, yMax, xMax);

	// Show title
	showTitle();
		
	// Show navigation panel
	int navHeight{20}, navWidth{57}, navY(yMax/2), navX{xMax/3 - 5};
	WINDOW* navWin = newwin(navHeight, navWidth, navY, navX);
	
	int idx = 1;
	switch (_idx)
	{
		case 0:
			mvprintw(navY + navHeight/5 + idx, navX + navWidth/3 + tuneX, ">>        PLAY        <<");
			idx += 3;	
			mvprintw(navY + navHeight/5 + idx, navX + navWidth/3 + tuneX, "          HELP          ");
			idx += 3;	
			mvprintw(navY + navHeight/5 + idx, navX + navWidth/3 + tuneX, "      HALL OF FAME      ");
			idx += 3;
			mvprintw(navY + navHeight/5 + idx, navX + navWidth/3 + tuneX, "          EXIT          ");
			refresh();
			break;
		case 1:
			mvprintw(navY + navHeight/5 + idx, navX + navWidth/3 + tuneX, "          PLAY          ");
			idx += 3;	
			mvprintw(navY + navHeight/5 + idx, navX + navWidth/3 + tuneX, ">>        HELP        <<");
			idx += 3;	
			mvprintw(navY + navHeight/5 + idx, navX + navWidth/3 + tuneX, "      HALL OF FAME      ");
			idx += 3;
			mvprintw(navY + navHeight/5 + idx, navX + navWidth/3 + tuneX, "          EXIT          ");
			refresh();
			break;
		case 2:
			mvprintw(navY + navHeight/5 + idx, navX + navWidth/3 + tuneX, "          PLAY          ");
			idx += 3;	
			mvprintw(navY + navHeight/5 + idx, navX + navWidth/3 + tuneX, "          HELP          ");
			idx += 3;	
			mvprintw(navY + navHeight/5 + idx, navX + navWidth/3 + tuneX, ">>    HALL OF FAME    <<");
			idx += 3;
			mvprintw(navY + navHeight/5 + idx, navX + navWidth/3 + tuneX, "          EXIT          ");
			refresh();
			break;
		case 3:
			mvprintw(navY + navHeight/5 + idx, navX + navWidth/3 + tuneX, "          PLAY          ");
			idx += 3;	
			mvprintw(navY + navHeight/5 + idx, navX + navWidth/3 + tuneX, "          HELP          ");
			idx += 3;	
			mvprintw(navY + navHeight/5 + idx, navX + navWidth/3 + tuneX, "      HALL OF FAME      ");
			idx += 3;
			mvprintw(navY + navHeight/5 + idx, navX + navWidth/3 + tuneX, ">>        EXIT        <<");
			refresh();
			break;
	}
	while (true)
	{
		startMenu();
	}
}

void startMenu()
{
	switch (getch())
	{
		case KEY_DOWN:
		case 's':
			choice = (1 + choice)%4;
			showStartMenu(choice);
			break;
			
		case KEY_UP:
		case 'w':
			choice = (3 + choice)%4;
			showStartMenu(choice);
			break;

		case KEY_BACKSPACE:
			choice = 3;
			showStartMenu(choice);
			break;

		case 10:
		case ' ':
			switch (choice) // TODO finish "PLAY", "HELP" and "HALL OF FAME"

			{
				case 0:
					choice = 0;
					showGameMenu();
					break;
				case 1:
					//choice = 0;
					//showHelp();
					break;
				case 2:
					//choice = 0;
					//showHallOfFame();
					break;
				case 3:
					endwin();
					exit(0);
			}
	}
}

void showGameMenu(int _idx)
{
	// Get screen size
	int yMax, xMax;
	getmaxyx(stdscr, yMax, xMax);
	
	// Show tittle	
	showTitle();

	// Show navigation panel
	int navHeight{20}, navWidth{57}, navY(yMax/2), navX{xMax/3 - 5};
	WINDOW* navWin = newwin(navHeight, navWidth, navY, navX);
	
	int idx = 1;
	switch (_idx)
	{
		case 0:
			mvprintw(navY + navHeight/5 + idx, navX + navWidth/3 + tuneX, ">>      NEW GAME      <<");
			idx += 3;	
			mvprintw(navY + navHeight/5 + idx, navX + navWidth/3 + tuneX, "          LOAD          ");
			idx += 3;	
			mvprintw(navY + navHeight/5 + idx, navX + navWidth/3 + tuneX, "        SETTINGS        ");
			idx += 3;
			mvprintw(navY + navHeight/5 + idx, navX + navWidth/3 + tuneX, "          BACK          ");
			refresh();
			break;
		case 1:
			mvprintw(navY + navHeight/5 + idx, navX + navWidth/3 + tuneX, "        NEW GAME        ");
			idx += 3;	
			mvprintw(navY + navHeight/5 + idx, navX + navWidth/3 + tuneX, ">>        LOAD        <<");
			idx += 3;	
			mvprintw(navY + navHeight/5 + idx, navX + navWidth/3 + tuneX, "        SETTINGS        ");
			idx += 3;
			mvprintw(navY + navHeight/5 + idx, navX + navWidth/3 + tuneX, "          BACK          ");
			refresh();
			break;
		case 2:
			mvprintw(navY + navHeight/5 + idx, navX + navWidth/3 + tuneX, "        NEW GAME        ");
			idx += 3;	
			mvprintw(navY + navHeight/5 + idx, navX + navWidth/3 + tuneX, "          LOAD          ");
			idx += 3;	
			mvprintw(navY + navHeight/5 + idx, navX + navWidth/3 + tuneX, ">>      SETTINGS      <<");
			idx += 3;
			mvprintw(navY + navHeight/5 + idx, navX + navWidth/3 + tuneX, "          BACK          ");
			refresh();
			break;
		case 3:
			mvprintw(navY + navHeight/5 + idx, navX + navWidth/3 + tuneX, "        NEW GAME        ");
			idx += 3;	
			mvprintw(navY + navHeight/5 + idx, navX + navWidth/3 + tuneX, "          LOAD          ");
			idx += 3;	
			mvprintw(navY + navHeight/5 + idx, navX + navWidth/3 + tuneX, "        SETTINGS        ");
			idx += 3;
			mvprintw(navY + navHeight/5 + idx, navX + navWidth/3 + tuneX, ">>        BACK        <<");
			refresh();
			break;
	}
	while (true)
	{
		gameMenu();
	}
}

void gameMenu()
{
	switch (getch())
	{
		case KEY_DOWN:
		case 's':
			choice = (1 + choice)%4;
			showGameMenu(choice);
			break;
			
		case KEY_UP:
		case 'w':
			choice = (3 + choice)%4;
			showGameMenu(choice);
			break;

		case KEY_BACKSPACE:
			choice = 0;
			showStartMenu();
			break;

		case 10:
		case ' ':
			switch (choice) // TODO

			{
				case 0:
					break;
				case 1:
					break;
				case 2:
					choice  = 0;
					showSettings();
					break;
				case 3:
					choice = 0;
					showStartMenu();
					break;
			}
			clear();
			refresh();
	}	
}

void showSettings(int _idx)
{
	clear();
	refresh();
	
	int yMax, xMax;
	getmaxyx(stdscr, yMax, xMax);
	
	// Show tittle	
	showTitle();

	// Show navigation panel
	int navHeight{20}, navWidth{57}, navY(yMax/2), navX{xMax/3 - 5};
	WINDOW* navWin = newwin(navHeight, navWidth, navY, navX);

	int idx = 1;
	switch (_idx)
	{
		case 0:
			mvprintw(navY + navHeight/5 + idx, navX + navWidth/3 + tuneX, ">>  DIFFICULTY:     EASY ");
			refresh();
			break;
		case 1:
			
			mvprintw(navY + navHeight/5 + idx, navX + navWidth/3 + tuneX, ">>  DIFFICULTY:   MEDIUM ");
			refresh();
			break;
		case 2:
			
			mvprintw(navY + navHeight/5 + idx, navX + navWidth/3 + tuneX, ">>  DIFFICULTY:     HARD ");
			refresh();
			break;
	}
	while (true)
	{
		settings();
	}
}

void settings()
{
	switch (getch())
	{
		case KEY_LEFT:
		case 'a':
			choice = (1 + choice)%3;
			showSettings(choice);
			break;
			
		case KEY_RIGHT:
		case 'd':
			choice = (2 + choice)%3;
			showSettings(choice);
			break;

		case KEY_BACKSPACE:
			//setParams(choice);
			choice = 0;
			showGameMenu();
			break;
	}
}
/*
void setParams(int _idx)
{
	// Read and print a file with the title 
	ifstream fRead;
	string line;
	
	switch (_idx)
	{
		case 0:
			fRead.open(".game/params/easy");	
		case 1:
			fRead.open(".game/params/medium");
		case 2:
			fRead.open(".game/params/hard");	
	}
	fRead.close();

	while (getline(fRead, line))
	{

	}
}
*/
