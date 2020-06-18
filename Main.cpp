#include <Windows.h>
#include <iostream>
#include "Functions.h"
#include "Structure.h"

using namespace std;


int main()
{
	system("mode con cols=90 lines=25");			//встановлення розміру вікна консолі
	system("color F0");							//зміна кольору консолі(фон - білий, символи - чорні)
	SetConsoleCP(1251);						//локалізація
	SetConsoleOutputCP(1251);					//забезпечення коректного виводу української мови
	
	auto top10 = new top[10];							//створення динамічного масиву рейтингу
	auto data = new reg[50];							//створення динамічного масиву даних
	int player_index=-1;								//номер гравця в масиві даних
	null(top10);										//занулення рейтингу
	int n,a=0;											//допоміжні змінні
	string player_name;									//змінна ім'я гравця

	//перевірка на наявніть файлів та їх зчитування в масиви або створення нових файлів в разі їхньої відсутності//
	{
		bool check_file = check_files("top10.txt");
		if (check_file == true)							//якщо файл існує, то
		{
			list_to_str(top10);							//зчитуємо його
		}
		else											//інакше
		{
			save_file(top10);							//створюємо новий шлахом збереження в нього пустоти
		}
		check_file = check_files("data.txt");			
		if (check_file == true)						//якщо файл існує, то
		{
			data_to_str(data);						//зчитуємо його
		}
		else										//інакше
		{
			save_data_file(data);					//створюємо новий шлахом збереження в нього пустоти
		}
	}
	
	while (true)
	{
		
			if (a == 0)										//якщо активне головне меню, то
			{	//початкове меню
				cout << "\t\t_-_-=МЕНЮ АВТОРИЗАЦІЇ=_-_" << endl;
				cout << "\n\n\t\t\t1 - Вхід" << endl;
				cout << "\n\n\t\t\t2 - Реєстрація" << endl;

			}
			else											//інакше активним стає меню користувача
			{	//меню користувача
				cout << "\t\t\t-_-_-_-_-=NFS=_-_-_-_" << endl;
				cout << "\n\n\t\t\t1 - Розпочати гру" << endl;
				cout << "\n\n\t\t\t2 - Переглянути таблицю рекордів" << endl;
				cout << "\n\n\t\t\t3 - Sign out" << endl;
			}

			cout << "\n\n\t\t\t0 - Вихід" << endl;
			cout << "\n\n\t\t>>>  ";
			cin >> n;							//вводимо вибір
		
		cin.ignore();//пропуск натиснення клавіші Enter, за для коректного вводу рядків
		system("cls");															//чистимо консоль
		if(a==0)																		//якщо активне головне меню, то
		{
			switch (n)																	//робимо вибір:
			{
			case 1:																		//користувач входить
				player_index = sign_in(data);											//номер користувача в базі
				break;//вибір зроблено	
			case 2:																		//користувач реєструється в базі
				player_index = sign_up(data);											//номер користувача в базі
				break;//вибір зроблено
			case 0:exit(0);//вихід з програми
			default://якщо вибір не правильний виводимо повідомлення про помилку
				cout << "Error!" << endl;
				system("pause");//пауза
				break;//вибір зроблено 
			}
			if(player_index!=-1)													//якщо всі попередні данні були введено правильно, то
			{
				save_data_file(data);												//зберігаємо базу данних
				player_name = data[player_index].login;								//присвоюємо ім'ю користувача його логін
				a++;																//переходимо в наступне меню
			}
		}
		else																		//інакше
		{
			switch (n)																//робимо вибір:
			{
			case 1:																	//запуск гри
				while (game(top10, player_name) == true);							//гра робить доки користувач з неї не вийде
				save_file(top10);													//коли виходить то зберігаємо рейтинг
				system("pause");//пауза
				break;//вибір зроблено
			case 2:																	//перегляд рейтингу
				out_file(top10);													//вивід таблиці рейтингів
				break;//вибір зроблено
			case 3:
				a = 0;
				break;//вибір зроблено
			case 0:exit(0);//вихід з програми
			default://якщо вибір не правильний виводимо повідомлення про помилку
				cout << "Error!" << endl;
				system("pause");	//пауза
				break;//вибір зроблено
			}
		}
		system("cls");//чистимо консоль
	}
	return 0;
}
