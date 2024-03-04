#include <unistd.h>
#include <ncurses.h>
#include <iostream>

/*
//Блок прототипов функций
void StartMenu(int _switcher);//Функция главного меню
void GameMenu(int _switcher);//Функция, вызывающаяся из главного меню. Содержит пункты "NEW GAME" и "CONTINUE"
void GameStart(char _scr[14][50], int _lifes, int* _timer);//Функция, определяющая начальный символьный массив
							//при запуске нового игрового сеанса
void Game(int _var);//Функция игрового сеанса
void GameOver(int _score);//Функция, спрашивающая имя игрока и записывающая его результат в файл
void Help(int _swithcer);//Функция помощи игроку
void TopChart();//Функуия "LEADERBOARD" - отображает список лидеров


void StartMenu(int _switcher)
{
	system("cls");
	switch (_switcher)
	{
	case 1:
		std::cout << "\n
			\n
			\n
			\t\t\t\t\t<< PLAY >>\t\t\t\t\t\n
			\n
			\t\t\t\t\t   HELP   \t\t\t\t\t\n
			\n
			\t\t\t\t\t   LEADERBOARD   \t\t\t\t\t\n
			\n
			\t\t\t\t\t   EXIT   \t\t\t\t\t\n
			\n
			\n
			\n";
		break;
	case 2:
		std::cout << "\n
			\n
			\n
			\t\t\t\t\t   PLAY   \t\t\t\t\t\n
			\n
			\t\t\t\t\t<< HELP >>\t\t\t\t\t\n
			\n
			\t\t\t\t\t   LEADERBOARD   \t\t\t\t\t\n
			\n
			\t\t\t\t\t   EXIT   \t\t\t\t\t\n
			\n
			\n
			\n";
		break;
	case 3:
		std::cout << "\n
			\n
			\n
			\t\t\t\t\t   PLAY   \t\t\t\t\t\n
			\n
			\t\t\t\t\t   HELP   \t\t\t\t\t\n
			\n
			\t\t\t\t\t<< LEADERBOARD >>\t\t\t\t\t\n
			\n
			\t\t\t\t\t   EXIT   \t\t\t\t\t\n
			\n
			\n
			\n";
		break;
	case 4:
		
		std::cout << "\n
			\n
			\n
			\t\t\t\t\t   PLAY   \t\t\t\t\t\n
			\n
			\t\t\t\t\t   HELP   \t\t\t\t\t\n
			\n
			\t\t\t\t\t   LEADERBOARD   \t\t\t\t\t\n
			"Write something (ESC to exit): ");\n
			\t\t\t\t\t<< EXIT >>\t\t\t\t\t\n
			\n
			\n
			\n";

		break;
	}
	int choice = _getch();//Получить значение нажатой клавиши
	if (chioce == 224)//Если была нажата стрелка
	{
		choice = _getch();//То определить, какая именно
	}
	if (choice == 72)//Если стрелка ВВЕРХ
	{
		if (_switcher != 1)
		{
			StartMenu(_switcher - 1);
		}
		else
		{
			StartMenu(4);
		}
	}
	if (choice == 80)//Если стрелка ВНИЗ
	{
		if (_switcher != 4)
		{
			StartMenu(_switcher + 1);
		}
		else
		{
			StartMenu(1);
		}

	}
	if (choice == 13 || choice == 32)//Если SPACE или ENTER
	{
		if (_switcher == 1)
		{
			GameMenu(1);
		}
		if (_switcher == 2)
		{
			Help(0);
		}
		if (_switcher == 3)
		{
			TopChart();
		}
		if (_switcher == 4)
		{
			_exit(1);
		}
	}
}

void GameMenu(_switcher)
{
	system("cls");
	if (_switcher == 1)
	{
		std::cout << "\n
			\n
			\n
			\n
			\n
			\t\t\t\t\t<< NEW GAME >>\t\t\t\t\t\n
			\n
			\n
			\t\t\t\t\t   CONTINUE   \t\t\t\t\t\n
			\n
			\n
			\n
			\n
			\n";
	}
	else
	{
		std::cout << "\n
			\n
			\n
			\n
			\n
			\t\t\t\t\t   NEW GAME   \t\t\t\t\t\n
			\n
			\n
			\t\t\t\t\t<< CONTINUE >>\t\t\t\t\t\n
			\n
			\n
			\n
			\n
			\n";
	}
	int choice = _getch();//Получить значение нажатой клавиши
	if (choice == 224)//Если была нажата стрелка
	{
		choice == _getch();//То определить, какая именно
	}
	if (choice == 72 || choice 80)//Если стрелка ВВЕРХ или стрелка ВНИЗ
	{
		GameMenu(3 - _switcher);
	}
	if (choice == 27)//Если ESC
	{
		StartMenu(1);
	}
	if (choice == 13 || choice == 32)//Если ESC или ENTER
	{
		Game(_switcher);
	}
}

void GameStart(char _scr[14][50], int _lifes, int* _timer)
{
	std::cout << "GameStart" << std::endl;
}

void Game(int _var)
{
	std::cout << "Game" << std::endl;
}

void GameOver(int _score)
{
	std::cout << "GameOver" << std::endl;
}

void Help(int _switcher)
{
	std::cout << "Help" << std::endl;
}

void TopChart()
{
	std::cout << "TopChart" << std::endl;
}
*/

int main()
{
	initscr();
	curs_set(0);
	noecho();
	raw();

	int c;
	printw("Write something (ESC to exit): ");
	while( (c = getch()) != 27)
	{
		move(10, 0);
		usleep(1000000);
		printw("Keycode: %d, character: %c", c, c);
		move(0, 0);
		printw("Write something (ESC to exit): ");
		refresh();
	}
	endwin();
	return 0;
}

