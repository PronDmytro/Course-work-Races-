#pragma once
#include "Entity.h"
#include <SFML/Graphics.hpp>	//�������� ��� ������ � 2D ��������

using namespace sf;				//������������� ����� ���� sf ��� ������ � ���������� SFML

//��������� ���� Player �������������� ������ ���� ����� Entity
class Player :public Entity {
private: float x, y;
public:
	float dx,speed;
	int dir, playerScore;
	String File, name;
	bool life;
	Player(String F, String Name, float X, float Y, float W, float H) :Entity(F, X, Y, W, H)
	{
		dx = 0; dy = 0; speed = 0; dir = 0, playerScore = 0;
		File = F;
		name = Name;
		life = true;
		w = W; h = H;
		image.loadFromFile("images/" + File);						
		image.createMaskFromColor(Color(255, 255, 255));		
		texture.loadFromImage(image);										
		sprite.setTexture(texture);											
		x = X; y = Y;
	}
	//��������� ��'��� p ����� Player �� ��������� ���� sfml, ��������� ��� �� �������� ������� update. ������� ����� �������� ���� ��������
	void update(float time)
	{
		switch (dir)
		{
		case 0: dx = speed; dy = 0; break;			//�� x ������ ��������� ��������, �� y ��������. ��������, �� ������� ��� ����� ������
		case 1: dx = -speed; dy = 0; break;			//�� x ������ ��������� ��������, �� y ��������. ��������, �� ������� ��� ����� ����
		case 2: dx = 0; dy = speed; break;			//�� x ������ ������ ��������, �� y ���������. ���������, �� ������� ��� ����� ����
		case 3: dx = 0; dy = -speed; break;			//�� x ������ ������ ��������, �� y ���������. ��������, �� ������� ��� ����� �����
		}

		x += dx * time;								// ����������� �� ��� �������� ������� ��������� � �� ������� ���
		y += dy * time;								//���������

		speed = 0;//�������� ��������, ��� ������� ����������
		sprite.setPosition(x, y); //�������� ������ � ������� x y, �� ������. ���������� �������� � ��� �������, ������ � ��� ������ ����� �� �� ����.
		interactionWithMap();//�������� �� ����� �� ��� �����
	}
	void interactionWithMap()
	{
		for (int i = y / 32; i < (y + h) / 32; i++)
			for (int j = x / 32; j < (x + w) / 32; j++)
			{
				//���� ������� �������� �� ���, �� ���� ����������� �����
				if (x > 275)
					x = 275;
				if (x < 32)
					x = 32;
				if (y < 0)
					y = 0;
				if (y > 510)
					y = 510;
			}
	}
	
	FloatRect getRect() {
		return FloatRect(x, y, w, h);
	}
	float get_player_coordinate_x() {
		return x;
	}
	float get_player_coordinate_y() {
		return y;
	}
};