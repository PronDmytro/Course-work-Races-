#pragma once
#include <string>
#include "Structure.h"
using namespace std;

int game(top[], string);						//запуск гри
bool check_files(string);						//перевірка  наявності текстових файлів
void list_to_str(top []);						//зчитування файлу рекордів
void out_file(top []);							//вивід на екран таблиці рекордів
void save_file(top []);							//зберігання файлів
void tops(top [], int , string);				//корегування топу
void null(top []);								//занулення масиву

int sign_in(reg[]);								//вхід в акаунт
int sign_up(reg[]);								//реєстрація акаунту
void save_data_file(reg[]);						//зберігання файлу данних
void data_to_str(reg[]);						//зчитування файлу данних