#pragma once
#include "Entity.h"
#include <SFML/Graphics.hpp>	//бібліотека для роботи з 2D графікою

using namespace sf;				//використовуємо прстір імен sf для роботи з бібліотеками SFML

//створюєма клас Player використовуючи публічні змінні класу Entity
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
	//оживляємо об'єкт p класу Player за допомогою часу sfml, передаючи час як параметр функції update. завдяки цьому персонаж може рухатися
	void update(float time)
	{
		switch (dir)
		{
		case 0: dx = speed; dy = 0; break;			//по x задаємо позитивну швидкість, по y зануляєм. отримуємо, що машинка йде тільки вправо
		case 1: dx = -speed; dy = 0; break;			//по x задаємо негативну швидкість, по y зануляєм. отримуємо, що машинка йде тільки вліво
		case 2: dx = 0; dy = speed; break;			//по x задаємо нулеве значение, по y позитивну. потримуємо, що машинка йде тільки вниз
		case 3: dx = 0; dy = -speed; break;			//по x задаємо нулеве значение, по y негативну. отримуємо, що машинка йде тільки вверх
		}

		x += dx * time;								// прискорення на час отримуємо зміщення координат і як наслідок рух
		y += dy * time;								//аналогічно

		speed = 0;//зануляют швидкість, щоб машинка зупинилася
		sprite.setPosition(x, y); //виводимо спрайт в позицію x y, по центру. нескінченно виводимо в цій функції, інакше б наш спрайт стояв би на місці.
		interactionWithMap();//перевірка на вихід за межі карти
	}
	void interactionWithMap()
	{
		for (int i = y / 32; i < (y + h) / 32; i++)
			for (int j = x / 32; j < (x + w) / 32; j++)
			{
				//якщо машинка виходить за межі, то вона повертається назад
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