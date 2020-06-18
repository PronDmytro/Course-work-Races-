#include <iomanip>
#include <iostream>
#include <fstream>
#include <string>
#include "Structure.h"

using namespace std;

//������� �������� ����� �����
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
//����� ���� ���� � ��������� �����
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
//��������  �� ����� ������ � ������ �������
void out_file(top top10[])
{
	cout << "| � |" << setw(15) << "��'�|" << setw(15) << "�������|"<< endl;
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
//������ ������ � ���������� ���'�� � ���������  ����
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
//������� ������ �������� ������ �������� 
void null(top m[])
{
	for (auto i = 0; i < 10; i++)
	{
		m[i].points = 0;
	}
}
//���� ����� ������� � ����� �������� ������� "��� 10"
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
//������ ������ � ���������� ���'�� � ���������  ���� 
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
//����� ��� ������������ � ��������� �����
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
	cout << "\t\t_-_-=�����������=-_-_" << endl;
	cout << "\n\n\t\t������ ����: ";
	getline(cin,log);
	cout << "\n\n\t\t������ ������: ";
	getline(cin, pass);
	system("cls");
	for (auto i = 0; i < 50; i++)
	{
		if (!data[i].login.empty())
		{
			if(data[i].login==log&&data[i].pass==pass)
			{
				cout << "\t\t_-_-=�����������=-_-_" << endl;
				cout << "\n\n\t\t���� �������� ������!" << endl;
				index = i;
				system("pause");
				return index;
			}
		}
	}
	if (index == 0)
	{
		cout << "\t\t_-_-=�����������=-_-_" << endl;
		cout << "\n\n\t\t����� ����� ���!!!" << endl;
		system("pause");
		return -1;
	}
}

int sign_up(reg data[])
{
	string log, pass;
	cout << "\t\t_-_-=���������=-_-_" << endl;
	cout << "\n\t������� �����, �� � ���������� ���� ����\n\t����������������� �� ��'� �� ������ ���� ���� �� �������!" << endl;
	cout << "\n\n\t\t������ ����: ";
	getline(cin, log);
	cout << "\n\n\t\t������ ������: ";
	getline(cin, pass);
	system("cls");
	for (auto i = 0; i < 50; i++)
	{
		if (!data[i].login.empty())
		{
			if (data[i].login == log)
			{
				cout << "\t\t_-_-=���������=-_-_" << endl;
				cout << "\n\n\t\t������ ���� ��� ���������������!\n\t\t��������� ���� ����!" << endl;
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
			cout << "\t\t_-_-=���������=-_-_" << endl;
			cout << "\n\n\t\t��������� �������� ������" << endl;
			system("pause");
				return i;
		}
	}
	
}