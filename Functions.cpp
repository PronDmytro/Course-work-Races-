#include <iomanip>
#include <iostream>
#include <fstream>
#include <string>
#include "Structure.h"

using namespace std;

//провіряє наявність файлів даних
bool check_files(string n)
{
	string name = "others/"+n;
	ifstream fin(name);
	if (fin.is_open())
	{
		fin.close();
		return true;
	}
	else
	{
		return false;
	}
}
//зчитує файл топу в динамічний масив
void list_to_str(top top10[]) {

	ifstream fout("others/top10.txt");
	int pos,point;
	string name = " ";

	string str_temp;
	auto index = 0,i=0;

	getline(fout, str_temp);
	pos = str_temp.find('|');

	do
	{

		pos = str_temp.find('|');
		name = str_temp.substr(0, pos);
		point = stoi(str_temp.substr(pos + 1, str_temp.size()));
		

			pos = str_temp.find('|');
		
			top10[i].name = name;
			top10[i].points = point;


				i++;
	} while (getline(fout, str_temp));
	fout.close();
}
//виводить  на екран записи у вигляді таблиці
void out_file(top top10[])
{
	cout << "| № |" << setw(15) << "Ім'я|" << setw(15) << "Рахунок|"<< endl;
	cout << "|---|--------------|--------------|" << endl;
	for (auto i = 0; i < 10; i++)
	{
		if (!top10[i].name.empty())
		{
			cout << "|" << setw(2) << i + 1 << " |" << setw(14) << top10[i].name;
			cout << "|" << setw(14) << top10[i].points << "|" <<endl;
			cout << "|---|--------------|--------------|" << endl;
		}
	}
	system("pause");
}
//записує записи з оперативної пам'яті в текстовий  файл
void save_file(top top10[])
{
	ofstream fin;
	fin.open("others/top10.txt");

	for (auto i = 0; i < 10; i++) {
		if (!top10[i].name.empty())
		{
			fin << top10[i].name << "|" << top10[i].points<<endl;
		}
		
	}
	fin.close();
}
//зануляє числові значення масиву структур 
void null(top m[])
{
	for (auto i = 0; i < 10; i++)
	{
		m[i].points = 0;
	}
}
//додає нових гравців у масив структур таблиці "Топ 10"
void tops(top top10[], const int point ,string pname)
{
	top m1[10];
	for(auto i=0;i<10;i++)
	{
		m1[i].name = top10[i].name;
		m1[i].points = top10[i].points;
	}

	int i_point=-1;

	for (auto i = 0; i < 10; i++)
	{
		if (point > top10[i].points && pname != top10[i - 1].name)
		{
			i_point = i;
			top10[i].name = pname;
			top10[i].points = point;
			for (auto j = i + 1; j < 10 - i; j++)
			{
				
				if (top10[j].name != pname/* && m1[j].name != pname*/ || m1[j-1].name != pname)
				{
					top10[j].name = m1[j - 1].name;
					top10[j].points = m1[j - 1].points;
				}
			}
			
			break;
		}
	}
	if (i_point != -1)
	{
		
		for (auto i = 0; i < 10; i++)
		{
			m1[i].name = top10[i].name;
			m1[i].points = top10[i].points;
		}
		for (auto i = 0; i < 10; i++)
		{

			if (top10[i].name == pname && top10[i].points != point)
			{
				
				for (auto j = i; j < 10 - i; j++)
				{
						top10[j].name = m1[j + 1].name;
						top10[j].points = m1[j + 1].points;	
				}
				break;
			}
		}
	}
}
//записує записи з оперативної пам'яті в текстовий  файл 
void save_data_file(reg data[])
{
	ofstream fin;
	fin.open("others/data.txt");

	for (auto i = 0; i < 10; i++) {
		if (!data[i].login.empty())
		{
			fin << data[i].login << "|" << data[i].pass << endl;
		}

	}
	fin.close();
}
//зчитує дані користувачів в динамічний масив
void data_to_str(reg data[])
{
	ifstream fout("others/data.txt");
	string log = " ", pass = " ";

	string str_temp;
	auto i = 0, pos = 0;

	getline(fout, str_temp);
	pos = str_temp.find('|');



	do
	{

		pos = str_temp.find('|');
		log = str_temp.substr(0, pos);
		pass =str_temp.substr(pos + 1, str_temp.size());
		pos = str_temp.find('|');

		data[i].login = log;
		data[i].pass = pass;


		i++;
	} while (getline(fout, str_temp));
	fout.close();
}

int sign_in(reg data[])
{
	
	int index=0;
	string log, pass;
	cout << "\t\t_-_-=Авторизація=-_-_" << endl;
	cout << "\n\n\t\tВведіть логін: ";
	getline(cin,log);
	cout << "\n\n\t\tВведіть пароль: ";
	getline(cin, pass);
	system("cls");
	for (auto i = 0; i < 50; i++)
	{
		if (!data[i].login.empty())
		{
			if(data[i].login==log&&data[i].pass==pass)
			{
				cout << "\t\t_-_-=Авторизація=-_-_" << endl;
				cout << "\n\n\t\tВхід виконано успішно!" << endl;
				index = i;
				system("pause");
				return index;
			}
		}
	}
	if (index == 0)
	{
		cout << "\t\t_-_-=Авторизація=-_-_" << endl;
		cout << "\n\n\t\tНевірні вхідні дані!!!" << endl;
		system("pause");
		return -1;
	}
}

int sign_up(reg data[])
{
	string log, pass;
	cout << "\t\t_-_-=Реєстрація=-_-_" << endl;
	cout << "\n\tЗверніть увагу, що в подальшому логін буде\n\tвикористовуватися як ім'я та змінити його буде не можливо!" << endl;
	cout << "\n\n\t\tВведіть логін: ";
	getline(cin, log);
	cout << "\n\n\t\tВведіть пароль: ";
	getline(cin, pass);
	system("cls");
	for (auto i = 0; i < 50; i++)
	{
		if (!data[i].login.empty())
		{
			if (data[i].login == log)
			{
				cout << "\t\t_-_-=Реєстрація=-_-_" << endl;
				cout << "\n\n\t\tДанний логін вже використовується!\n\t\tСпробуйте щось інше!" << endl;
				system("pause");
				return -1;
				
			}
		}
	}

	for (auto i = 0; i < 50; i++)
	{
		if (data[i].login.empty())
		{
			data[i].login = log;
			data[i].pass = pass;
			cout << "\t\t_-_-=Реєстрація=-_-_" << endl;
			cout << "\n\n\t\tРеєстрація виконана успішно" << endl;
			system("pause");
				return i;
		}
	}
	
}