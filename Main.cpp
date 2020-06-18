#include <Windows.h>
#include <iostream>
#include "Functions.h"
#include "Structure.h"

using namespace std;


int main()
{
	system("mode con cols=90 lines=25");			//������������ ������ ���� ������
	system("color F0");							//���� ������� ������(��� - ����, ������� - ����)
	SetConsoleCP(1251);						//����������
	SetConsoleOutputCP(1251);					//������������ ���������� ������ ��������� ����
	
	auto top10 = new top[10];							//��������� ���������� ������ ��������
	auto data = new reg[50];							//��������� ���������� ������ �����
	int player_index=-1;								//����� ������ � ����� �����
	null(top10);										//��������� ��������
	int n,a=0;											//������� ����
	string player_name;									//����� ��'� ������

	//�������� �� ������� ����� �� �� ���������� � ������ ��� ��������� ����� ����� � ��� ����� ���������//
	{
		bool check_file = check_files("top10.txt");
		if (check_file == true)							//���� ���� ����, ��
		{
			list_to_str(top10);							//������� ����
		}
		else											//������
		{
			save_file(top10);							//��������� ����� ������ ���������� � ����� �������
		}
		check_file = check_files("data.txt");			
		if (check_file == true)						//���� ���� ����, ��
		{
			data_to_str(data);						//������� ����
		}
		else										//������
		{
			save_data_file(data);					//��������� ����� ������ ���������� � ����� �������
		}
	}
	
	while (true)
	{
		
			if (a == 0)										//���� ������� ������� ����, ��
			{	//��������� ����
				cout << "\t\t_-_-=���� ��������ֲ�=_-_" << endl;
				cout << "\n\n\t\t\t1 - ����" << endl;
				cout << "\n\n\t\t\t2 - ���������" << endl;

			}
			else											//������ �������� ��� ���� �����������
			{	//���� �����������
				cout << "\t\t\t-_-_-_-_-=NFS=_-_-_-_" << endl;
				cout << "\n\n\t\t\t1 - ��������� ���" << endl;
				cout << "\n\n\t\t\t2 - ����������� ������� �������" << endl;
				cout << "\n\n\t\t\t3 - Sign out" << endl;
			}

			cout << "\n\n\t\t\t0 - �����" << endl;
			cout << "\n\n\t\t>>>  ";
			cin >> n;							//������� ����
		
		cin.ignore();//������� ���������� ������ Enter, �� ��� ���������� ����� �����
		system("cls");															//������� �������
		if(a==0)																		//���� ������� ������� ����, ��
		{
			switch (n)																	//������ ����:
			{
			case 1:																		//���������� �������
				player_index = sign_in(data);											//����� ����������� � ���
				break;//���� ��������	
			case 2:																		//���������� ���������� � ���
				player_index = sign_up(data);											//����� ����������� � ���
				break;//���� ��������
			case 0:exit(0);//����� � ��������
			default://���� ���� �� ���������� �������� ����������� ��� �������
				cout << "Error!" << endl;
				system("pause");//�����
				break;//���� �������� 
			}
			if(player_index!=-1)													//���� �� �������� ���� ���� ������� ���������, ��
			{
				save_data_file(data);												//�������� ���� ������
				player_name = data[player_index].login;								//���������� ��'� ����������� ���� ����
				a++;																//���������� � �������� ����
			}
		}
		else																		//������
		{
			switch (n)																//������ ����:
			{
			case 1:																	//������ ���
				while (game(top10, player_name) == true);							//��� ������ ���� ���������� � �� �� �����
				save_file(top10);													//���� �������� �� �������� �������
				system("pause");//�����
				break;//���� ��������
			case 2:																	//�������� ��������
				out_file(top10);													//���� ������� ��������
				break;//���� ��������
			case 3:
				a = 0;
				break;//���� ��������
			case 0:exit(0);//����� � ��������
			default://���� ���� �� ���������� �������� ����������� ��� �������
				cout << "Error!" << endl;
				system("pause");	//�����
				break;//���� ��������
			}
		}
		system("cls");//������� �������
	}
	return 0;
}
