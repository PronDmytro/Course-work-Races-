#pragma once
#include <string>
#include "Structure.h"
using namespace std;

int game(top[], string);						//������ ���
bool check_files(string);						//��������  �������� ��������� �����
void list_to_str(top []);						//���������� ����� �������
void out_file(top []);							//���� �� ����� ������� �������
void save_file(top []);							//��������� �����
void tops(top [], int , string);				//����������� ����
void null(top []);								//��������� ������

int sign_in(reg[]);								//���� � ������
int sign_up(reg[]);								//��������� �������
void save_data_file(reg[]);						//��������� ����� ������
void data_to_str(reg[]);						//���������� ����� ������