#include <panel.h>
#include <iostream>
#include <fstream>
#include <string>


using namespace std;

int main();
void showTitle();			// Show the title of the game
void showStartMenu(int _idx = 0);	// Show start menu with 4 options
void showGameMenu(int _idx = 0); 	// Show "PLAY" menu with some options
void gameMenu(); 			// Do command in "PLAY" menu due to user's input
void showHelp(int _idx = 0); 		// Show "HELP" window with helpful information
void help(); 				// Do command in "HELP" menu due to user's input
void showHallOfFame(int _idx = 0);	// Show "HALL OF FAME" window with top results of the game
void hallOfFame(); 			// Do command in "HALL OF FAME" menu due to user's input
void showSettings(int _idx = 0);	// Show "SETTINGS" window with 3 different difficulty levels
void settings();			// Do command in "SETTINGS" menu due to user's input
void setParams();			// Set parametres of the game due to difficulty level
void playGame();			// Start a game session with chosen difficulty level ("Easy" by default)


int choice{0};				// A varibale to detect user's behaviour
string difficultyLvl{"EASY"};		// A variable to define difficulty level of the game
int tuneX{2};				// A variable to tune output position on the X-axis
int tuneY{0};				// A variable to tune output position on the Y-axis
int ovrlDel{3};


// Let the monkeys be everywhere:
// User is playing as a monkey in an air baloon and fights against enemy monkeys. And anything might be a monkey...
class Monkey 
{
public:
	WINDOW* win;
       	PANEL* pan;	
	int height, width;		// The dimensions of the object's window	
	int y, x;			// The coordiantes of the top left corner of the object's window
	
	bool isHitted();		// Check all of the cells whether they intersect with external objects

	Monkey()
	{}	
	Monkey(int _y, int _x, int _h, int _w): y{_y}, x{_x}, height{_h}, width{_w}
	{
		win = newwin(height, width, y, x);
		pan = new_panel(win);
		refresh();
	}

	~Monkey()
	{
		del_panel(pan);
		delwin(win);
	}
};


class Screen: public Monkey
{
public:	
	string path;
	
	Screen()
	{}
	Screen(int _y, int _x, int _h, int _w, string _filename): Monkey(_y, _x, _h, _w), path{".game/sprites/" + _filename}
	{
		ifstream fRead;
		string line;
		int idx{0};
		fRead.open(path.c_str());
		while (getline(fRead, line))
		{
			mvwprintw(win, idx, 0, line.c_str());
			idx += 1;
		}
		fRead.close();
		wrefresh(win);
	}
};


class Player: public Monkey
{
private:
	int points;			// The amount of points earned by player
	int fuel; 			// The amount of fuel to move the baloon 
public:
	Player(int _y, int _x, int _h = 6, int _w = 7): Monkey(_y, _x, _h, _w), points{0}, fuel{500}
	{
		ifstream fRead;
		string line;
		int idx{0};
		fRead.open(".game/sprites/player");
		while (getline(fRead, line))
		{
			mvwprintw(win, idx, 0, line.c_str());
			idx += 1;
		}
		fRead.close();
		wrefresh(win);
	}	
	void move();
};

void Player::move()
{
	// Get screen size
	int yMax, xMax;
	getmaxyx(stdscr, yMax, xMax);

	switch (getch())
	{
		case KEY_LEFT:
		case 'a':
			x-=2;
			y+=1;
			break;
		case KEY_RIGHT:
		case 'd':
			x+=2;
			y+=1;
			break;
		case KEY_UP:
		case 'w':
			if (fuel)
			{
				y-=2;
				fuel--;
			}
			break;
		case ERR:
			y+=1;
			break;
	}
	if ((x <= 0) or (x >= xMax - width + 1) or (y <= 0) or (y >= yMax - height + 1))
	{
		this->~Monkey();
		endwin();
		main();
	}
	else
	{
		move_panel(pan, y, x);
		update_panels();
		doupdate();
	}	
}


class Enemy: public Monkey
{
private:
	int reward;			// The reward for destroying
	double delay; 			// The delay of the enenemy's shooting. Can be a chosen due to difficulty levels: "easy", "medium", "hard"
public:
	Enemy(int _y, int _x, int _h, int _w): Monkey(_y, _x, _h, _w), reward{100}, delay{0}
	{};
	~Enemy()
	{};

	void setDelay(int _idx = 0);	// A function to set delay due to user's choice of the difficulty level
};


extern Screen title;
extern Screen startMenu[4];


void showStartMenu(int _idx)
{
	top_panel(startMenu[_idx].pan);
	
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
					//showGameMenu();
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
/*
void showGameMenu(int _idx)
{
	// Get screen size
	int yMax, xMax;
	getmaxyx(stdscr, yMax, xMax);
	
	// Show tittle	
	showTitle();

	// Navigation panel parameters
	int navHeight{20}, navWidth{57}, navY(yMax/2), navX{xMax/3 - 5};
		
	int idx = 1;
	switch (_idx)
	{
		case 0:
			mvprintw(navY + navHeight/5 + idx + tuneY, navX + navWidth/3 + tuneX, ">>      NEW GAME      <<");
			idx += 3;	
			mvprintw(navY + navHeight/5 + idx + tuneY, navX + navWidth/3 + tuneX, "          LOAD          ");
			idx += 3;	
			mvprintw(navY + navHeight/5 + idx + tuneY, navX + navWidth/3 + tuneX, "        SETTINGS        ");
			idx += 3;
			mvprintw(navY + navHeight/5 + idx + tuneY, navX + navWidth/3 + tuneX, "          BACK          ");
			refresh();
			break;
		case 1:
			mvprintw(navY + navHeight/5 + idx + tuneY, navX + navWidth/3 + tuneX, "        NEW GAME        ");
			idx += 3;	
			mvprintw(navY + navHeight/5 + idx + tuneY, navX + navWidth/3 + tuneX, ">>        LOAD        <<");
			idx += 3;	
			mvprintw(navY + navHeight/5 + idx + tuneY, navX + navWidth/3 + tuneX, "        SETTINGS        ");
			idx += 3;
			mvprintw(navY + navHeight/5 + idx + tuneY, navX + navWidth/3 + tuneX, "          BACK          ");
			refresh();
			break;
		case 2:
			mvprintw(navY + navHeight/5 + idx + tuneY, navX + navWidth/3 + tuneX, "        NEW GAME        ");
			idx += 3;	
			mvprintw(navY + navHeight/5 + idx + tuneY, navX + navWidth/3 + tuneX, "          LOAD          ");
			idx += 3;	
			mvprintw(navY + navHeight/5 + idx + tuneY, navX + navWidth/3 + tuneX, ">>      SETTINGS      <<");
			idx += 3;
			mvprintw(navY + navHeight/5 + idx + tuneY, navX + navWidth/3 + tuneX, "          BACK          ");
			refresh();
			break;
		case 3:
			mvprintw(navY + navHeight/5 + idx + tuneY, navX + navWidth/3 + tuneX, "        NEW GAME        ");
			idx += 3;	
			mvprintw(navY + navHeight/5 + idx + tuneY, navX + navWidth/3 + tuneX, "          LOAD          ");
			idx += 3;	
			mvprintw(navY + navHeight/5 + idx + tuneY, navX + navWidth/3 + tuneX, "        SETTINGS        ");
			idx += 3;
			mvprintw(navY + navHeight/5 + idx + tuneY, navX + navWidth/3 + tuneX, ">>        BACK        <<");
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
					playGame();
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

void showHelp(int _idx)
{
	clear();
	refresh();
	
	int yMax, xMax;
	getmaxyx(stdscr, yMax, xMax);
	
	// Navigation panel parameters
	int winHeight{20}, winWidth{57}, winY(yMax/2), winX{xMax/3 - 5};
}

void showSettings(int _idx)
{
	clear();
	refresh();
	
	int yMax, xMax;
	getmaxyx(stdscr, yMax, xMax);
	
	// Show tittle	
	showTitle();

	// Navigation panel parameters
	int navHeight{20}, navWidth{57}, navY(yMax/2), navX{xMax/3 - 5};
	
	int idx = 1;
	switch (_idx)
	{
		case 0:
			mvprintw(navY + navHeight/5 + idx + tuneY, navX + navWidth/3 + tuneX, ">>  DIFFICULTY:     EASY ");
			refresh();
			break;
		case 1:
			
			mvprintw(navY + navHeight/5 + idx + tuneY, navX + navWidth/3 + tuneX, ">>  DIFFICULTY:   MEDIUM ");
			refresh();
			break;
		case 2:
			
			mvprintw(navY + navHeight/5 + idx + tuneY, navX + navWidth/3 + tuneX, ">>  DIFFICULTY:     HARD ");
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
*/

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


/*
void playGame()
{
	clear();
	refresh();
	halfdelay(ovrlDel);	
	
	// Get screen size
	int yMax, xMax;
	getmaxyx(stdscr, yMax, xMax);

	Player baloon(yMax/5, xMax/5);
	
	while(true)
	{
		baloon.move();
	}
}
*/

int main()
{		
	// Setting initial parameters
	initscr();
	noecho();			// To not see what user types
	curs_set(0);			// To make cursor invincible
	keypad(stdscr, true);		// To work with arrows
	clear();
	
	// Get screen size
	int yMax, xMax;
	getmaxyx(stdscr, yMax, xMax);

	// Create title panel
	int titleHeight{10}, titleWidth{59}, titleY(yMax/4), titleX{xMax/3 - 5 + tuneX};	
	title = Screen(titleHeight, titleWidth, titleY, titleX, "title");
	
	// Create start menu panel
	int startHeight{20}, startWidth{57}, startY(yMax/2), startX{xMax/3 - 5};
	for (int i = 0; i < 4; i++)
	{
		startMenu[i] = Screen(startHeight, startWidth, startY, startX, "start" + to_string(i));
	}
	
	showStartMenu();
	
	/*
	// Create game menu panel
	Screen gameMenu[4];
	for (int i = 0; i < 4; i++)
	{
		gameMenu[i] = Screen(startHeight, startWidth, startY, startX, "game" + string(i));
	}
	
	// Main procces	
	showStartMenu();	
	*/
	return 0;
}

