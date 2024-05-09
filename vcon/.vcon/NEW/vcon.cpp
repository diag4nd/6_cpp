#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <bits/stdc++.h>
#include <sys/stat.h>
#include <sys/types.h>

//Коды ошибок
//
enum ERR_IDX
{
	SUCCESS    = 0,
	ERR_SYNTAX = 1,
	ERR_INIT   = 2,
	ERR_STRUCT = 3,
	ERR_ADD	   = 4
};

//Словари для вызова функций и вывода ошибок
//
std::map<std::string, void (*)(int _argc, char* _argv[])>	funcList;
std::map<int, std::string>					errMsg;

//Все доступные функции Vcon
//
//Вывод справочной информации со списком используемых комманд для системы контроля версий
void help(int _argc, char* _argv[]);

//Создание специальной директории ".vcon" внутри текущей директории для хранения информации о файлах
void init(int _argc, char* _argv[]);

//Начать отслеживать конкретный файл (конкретные файлы)
void add(int _argc, char* _argv[]);

//Перестать отслеживать конкретный файл (конкретные файлы)
void remove(int _argc, char* _argv[]);

//Записать изменения всех отслеживаемых файлов (конкретных файлов)
void fix(int _argc, char* _argv[]);

//Вывод лога обо всех изменениях, касающихся всех файлов (конкретных файлов)
void log(int _argc, char* _argv[]);

//Вывод различий между двумя версиями всех отслеживаемых файлов (конкретных файлов), когда еще не была вызвана функция "fix"
void diff(int _argc, char* _argv[]);

//Подумать над функциями "status", "log clear", "clear"


//Реализация функций Vcon 
//
void help(int _argc, char* _argv[])
{
	try
	{
		if (_argc == 2)
		{
			std::cout << "\n"
				"Avaliable Vcon commands:\n"
				"\n"
				"  start a working area\n"
					"\tinit\t\tCreate an empty '.vcon' directory or reinitialize an existing one\n"
				"\n"
				"  work on the current change\n"
					"\tadd\t\tAdds given files to start tracking\n"
				"\n"
					"\tremove\t\tRemove files from the working tree\n"
					"\t-rm\n"
				"\n"
				"  examine the history and state\n"
					"\tlog\t\tShow fixes logs\n"
				"\n"
				"  grow, mark and tweak your common history\n"
					"\tfix\t\tRecords changes to the '.vcon' directory\n"
				"\n"
					"\tdiff\t\tShow chages between fixes, etc\n"
				"\n"
				;
		}
		else
		{
			throw ERR_SYNTAX;
		}
	}
	catch (enum ERR_IDX _errIdx)
	{
		std::cerr << errMsg[_errIdx];
		exit(_errIdx);
	}
}

void init(int _argc, char* _argv[])
{
	try
	{
		if (mkdir(".vcon", 0777) == -1)
		{
			throw ERR_INIT;
		}
		std::ofstream fWrite(".vcon/LOG");
		fWrite.close();

		fWrite.open(".vcon/QUEUE");
		fWrite.close();
		mkdir(".vcon/NEW", 0777);
		mkdir(".vcon/VERSIONS", 0777);
	}
	catch (enum ERR_IDX _errIdx)
	{
		std::cerr << errMsg[_errIdx];
		exit(_errIdx);
	}	
}

void add(int _argc, char* _argv[])
{
	try
	{
		//Структура нужна для проверки на наличие соответствующего файла в директории
		struct stat sb;
		if (stat(".vcon", &sb) != 0)
		{
			throw ERR_STRUCT;
		}
		if (_argc < 3)
		{
			throw ERR_SYNTAX;
		}
		else
		{	
			std::string line{}, fPath{}, fName{};
			
			std::ifstream fRead;
			std::ofstream fWrite;

			//Пытаемся выполнить процедуру для каждого переданного имени
			for (int i = 2; i < _argc; i++)
			{
				//Если такой файл в принципе существует
				if (stat(_argv[i], &sb) == 0)
				{
					//Если внутри специальной директории ".vcon" случайно не удален системный файл "QUEUE"
					if (stat(".vcon/QUEUE", &sb) == 0)
					{
						bool exists = false;
						fWrite.open(".vcon/QUEUE", std::ios::app);
						fRead.open(".vcon/QUEUE");

						//Проверяем, стоит ли переданный файл в очереди
						while (std::getline(fRead, line))
						{
							if (line == _argv[i])
							{
								exists = true;
								break;
							}
						}
						fRead.close();

						//Если нет, то добавляем в очередь
						if (not exists)
						{
							fWrite << _argv[i] << std::endl;
						}	
						fWrite.close();
					}
					else
					{
						throw ERR_STRUCT;
					}
					
					//Открываем директорию под хранение новой версии переданного файла
					fPath = ".vcon/NEW/" + std::string(_argv[i]);

					//Записываем копию файла
					fRead.open(_argv[i]);
					fWrite.open(fPath);
					while (std::getline(fRead, line))
					{
						fWrite << line << std::endl;
					}
					fRead.close();
					fWrite.close();
					
					//Записываем соответствующее сообщение в лог
					time_t ttime = time(0);
					tm *loc_t = localtime(&ttime);
					std::string day = std::to_string(loc_t->tm_mday);
					std::string month = std::to_string(1 + loc_t->tm_mon);
					std::string year = std::to_string(1900 + loc_t->tm_year);
					std::string hours = std::to_string(1 + loc_t->tm_hour);
					std::string minutes = std::to_string(1 + loc_t->tm_min);
					std::string seconds = std::to_string(1 + loc_t->tm_sec);
					std::string date = year + "/" + month + "/" + day + " in " + hours + ":" + minutes + ":" + seconds + "\n";

					fWrite.open(".vcon/LOG", std::ios::app);
					fWrite << "\n" 
						"File named '" << _argv[i] <<  "'\n"
						<< date <<
						"Event:\tfile was added\n"
						"\n";
					fWrite.close();
				}
				else
				{
					throw ERR_ADD;
				}	
			}
		}
	}
	catch (enum ERR_IDX _errIdx)
	{
		std::cerr << errMsg[_errIdx];
		exit(_errIdx);
	}
}

void remove(int _argc, char* _argv[])//Доделать
{		
}

void fix(int _argc, char* _argv[])//Доделать подчистку очереди
{	
	try
	{	
		struct stat sb;
		std::ifstream fRead;
		if (stat(".vcon/QUEUE", &sb) == 0)
		{
			fRead.open(".vcon/QUEUE");
		}
		else
		{
			throw ERR_STRUCT;
		}
		
		std::ofstream fWrite;
		std::string line{}, line2{};
		
		while (std::getline(fRead, line))
		{
			if (_argc > 2)
			{
				for (int i = 2; i < _argc; i++)
				{
					if (line == _argv[i])
					{
						std::string fPath = ".vcon/VERSIONS/" + std::string(_argv[i]) + "/";

						if (stat(fPath.c_str(), &sb) != 0)
						{
							mkdir(fPath.c_str(), 0777);
						}	
						
						time_t ttime = time(0);
						tm *loc_t = localtime(&ttime);
						std::string day = std::to_string(loc_t->tm_mday);
						std::string month = std::to_string(1 + loc_t->tm_mon);
						std::string year = std::to_string(1900 + loc_t->tm_year);
						std::string hours = std::to_string(1 + loc_t->tm_hour);
						std::string minutes = std::to_string(1 + loc_t->tm_min);
						std::string seconds = std::to_string(1 + loc_t->tm_sec);
						std::string fName = hours + ":" + minutes + ":" + seconds + "_" + day + "_" + month + "_" + year;
						
						fWrite.open(std::string(fPath + fName));	
						
						std::ifstream fRead2(_argv[i]);
						std::string line2{};

						while(std::getline(fRead2, line2))
						{
							fWrite << line2 << std::endl;
						}
						fWrite.close();
						fRead2.close();

						//Запись в лог
						std::string date = year + "/" + month + "/" + day + " in " 
							+ hours + ":" + minutes + ":" + seconds + "\n";
						fWrite.open(".vcon/LOG", std::ios::app);
						fWrite << "\n"
							"File named '" << _argv[i] <<  "'\n"
							<< date <<
							"Event:\tfile was fixed\n"
							"\n";
						fWrite.close();
					}
				}
			}
			else if (_argc == 2)
			{
				//Повтор кода
				std::string fPath = ".vcon/VERSIONS/" + std::string(line) + "/";
				struct stat sb;
				if (stat(fPath.c_str(), &sb) != 0)
				{
					mkdir(fPath.c_str(), 0777);
				}	
				
				time_t ttime = time(0);
				tm *loc_t = localtime(&ttime);
				std::string day = std::to_string(loc_t->tm_mday);
				std::string month = std::to_string(1 + loc_t->tm_mon);
				std::string year = std::to_string(1900 + loc_t->tm_year);
				std::string hours = std::to_string(1 + loc_t->tm_hour);
				std::string minutes = std::to_string(1 + loc_t->tm_min);
				std::string seconds = std::to_string(1 + loc_t->tm_sec);
				std::string fName = hours + ":" + minutes + ":" + seconds + "_" + day + "_" + month + "_" + year;
				
				fWrite.open(std::string(fPath + fName));
				
				std::ifstream fRead2(line);
				std::string line2{};

				while(std::getline(fRead2, line2))
				{
					fWrite << line2 << std::endl;
				}
				fWrite.close();
				fRead2.close();

				//Запись в лог
				std::string date = year + "/" + month + "/" + day + " in " 
							+ hours + ":" + minutes + ":" + seconds + "\n";
				fWrite.open(".vcon/LOG", std::ios::app);
				fWrite << "\n" 
					"File named '" << line <<  "'\n"
					<< date <<
					"Event:\tfile was fixed\n"
					"\n";
				fWrite.close();

				//Очистка очереди
				fWrite.open(".vcon/QUEUE");
				fWrite.close();
			}
		}
	}
	catch (enum ERR_IDX _errIdx)
	{
		std::cerr << errMsg[_errIdx];
		exit(_errIdx);
	}
}

void log(int _argc, char* _argv[])//Дописать проверку на наличие такого файла
{	
	std::ifstream fRead(".vcon/LOG");
	std::string line{};
	while (std::getline(fRead, line))
	{
		if (_argc == 2)
		{
			std::cout << line << std::endl;
		}
		else
		{
			for (int i = 2; i < _argc; i++)
			{
				std::string strcmp{"'" + std::string(_argv[i]) + "'"};
				if (line.find(strcmp) != std::string::npos)
				{
					//Не универсальный вывод, а костыль
					std::cout << std::endl << line << std::endl;
					std::getline(fRead, line);
					std::cout << line << std::endl;
					std::getline(fRead, line);
					std::cout << line << std::endl << std::endl;	
				}
			}
		}
	}
	fRead.close();
}

void diff(int _argc, char* _argv[])//Доделать
{
}

int main(int _argc, char* _argv[])
{	
	//Инициализация словаря для вызова функций
	//
	funcList["help"]	= help;
	funcList["-h"]		= help;
	funcList["init"]	= init;
	funcList["add"]		= add;
	funcList["fix"] 	= fix;
	funcList["log"]		= log;
	funcList["diff"]	= diff;
	funcList["remove"]	= remove;
	funcList["-rm"]		= remove;
	
	//Инициализация словаря для вывода ошибок
	//
	errMsg[ERR_SYNTAX] = {
			"\n"
			"Unknown command for 'vcon'\n"
			"Use 'vcon help' to show list of commands\n"
			"\n"
			};
	errMsg[ERR_INIT] = {
			"\n"
			"Vcon is already initialized\n"
			"\n"
			};
	errMsg[ERR_STRUCT] = {
			"\n"
			"Vcon structure is broken\n"
			"Remove '.vcon' directory if it exists\n"
			"Then try 'vcon init' command\n"
			"\n"
			};
	errMsg[ERR_ADD] = {
			"\n"
			"Incorrect name of file\n"
			"\n"
			};
	
	try
	{
		if (_argc >= 2)
		{	
			if ( funcList.count(_argv[1]) )
			{
				funcList[ _argv[1] ](_argc, _argv);
				return SUCCESS;
			}
			throw ERR_SYNTAX;
		}
		throw ERR_SYNTAX;
	}
	catch(enum ERR_IDX _errIdx)
	{
		std::cerr << errMsg[_errIdx];
		exit(_errIdx);
	}
}
