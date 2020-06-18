#include <SFML/Graphics.hpp>			//�������� ��� ������ � 2D ��������
#include <SFML/Audio.hpp>				//�������� ��� ������ � ������
#include <sstream>						//�������� ��� ������ � �������
#include <time.h>						//�������� ��� ������ � �����
#include <iomanip>						//�������� ��� ��������� �������
#include "Entity.h"						//���� ������
#include "Player.h"						//���� ������
#include "map.h"						//�����
#include "Structure.h"					//�������� ���������
#include "Functions.h"					//�������� ��������

using namespace sf;						//������������� ����� ���� sf ��� ������ � ���������� SFML
using namespace std;

int game(top top10[],string player_name)
{
	
		//��������� ���� � �������� �������� �� ������
		RenderWindow window(sf::VideoMode(640, 608), "NFS");

	
		SoundBuffer gameOver;									//�������� �����
		gameOver.loadFromFile("audio/game over.ogg");	//��������� ���� �������� � �����
		Sound theEnd(gameOver);									//��������� ����� � ���������� �� ���� �������� ���������� � ��

		int k = 0;												//�������� �����

		Music music;											//��������� ���� ������
		music.openFromFile("audio/nfs.ogg");				//��������� ����
		music.play();											//���������� ������

		Font font;												//�����
		font.loadFromFile("others/CyrilicOld.ttf");		//�������� ������ ������ ���� ������
		Text text("", font, 20);				//��������� ���� �����, ���������� � ���� ����� �����, �����, ����� ������(� �������)
		text.setFillColor(Color::Red);							//��������� ����� � ��������

		Image map_image;										//���� ���������� ��� �����
		map_image.loadFromFile("images/map.png");		//��������� ���� ��� �����
		Texture map;											//�������� �����
		map.loadFromImage(map_image);							//�������� �������� �����������
		Sprite s_map;											//��������� ������ ��� �����
		s_map.setTexture(map);									//�������� �������� ��������

		//���������� ��������� ��������//
		Image end_image;
		end_image.loadFromFile("images/wasted.png");
		Texture end;
		end.loadFromImage(end_image);
		Sprite s_end;
		s_end.setTexture(end);
		s_end.setPosition(30, 150);

		//���������� ��� ����������� �������� �����//
		Image sounds_on, sounds_off;										
		sounds_on.loadFromFile("images/on.png");						
		sounds_off.loadFromFile("images/off.png");
		Texture on, off;													
		sounds_on.createMaskFromColor(Color(255, 255, 255));
		sounds_off.createMaskFromColor(Color(255, 255, 255));
		on.loadFromImage(sounds_on);										
		off.loadFromImage(sounds_off);
		Sprite s_on, s_off;													
		s_on.setTexture(on); s_on.setPosition(580, 550);				
		s_off.setTexture(off); s_off.setPosition(580, 550);


					//��������� ����� ������//
		Player p("pcar.png", player_name, 150, 500, 45, 104);//�������� ����� �����, ��'� ������, �������� ���������� �� ������ �������
					//��������� ����� ������//
		Entity e0("car.png", 50, -150, 45, 104);
		Entity e1("car.png", 100, -400, 45, 104);
		Entity e2("car.png", 150, -600, 45, 104);
		Entity e3("car.png", 200, -600, 45, 104);
		Entity e4("car.png", 250, -750, 45, 104);
		
		
	
		srand(time(NULL));

		bool sounds=true;//�������� �����
		
		Clock clock;

	/*
		 ����'������� ���� ��� SFML,
		 ���� ������ ���������� ��� �������� ��:
		"���� ���� ������� - ������� ��, �� �������� �����",
	 */
		while (window.isOpen())
		{
			Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();
			}
			
			float time = clock.getElapsedTime().asMicroseconds();	//����� � ��������� ����� � ������������
			clock.restart();										//������������� ���
			time = time / 800;										//�������� ���

			//�������� ���������� ������� ������//
			float coordinatePlayerX, coordinatePlayerY = 0;
			coordinatePlayerX = p.get_player_coordinate_x();
			coordinatePlayerY = p.get_player_coordinate_y();
			if (p.life)												//���� ������� ����� �� �� ������ ��� ��������
			{
				if (Keyboard::isKeyPressed(Keyboard::Left)) {
					p.dir = 1; p.speed = 0.1;						//dir =1 - ������ ����, speed =0.1 - �������� ����
				}

				if (Keyboard::isKeyPressed(Keyboard::Right)) {
					p.dir = 0; p.speed = 0.1;;//������ ������
				}

				if (Keyboard::isKeyPressed(Keyboard::Up)) {
					p.dir = 3; p.speed = 0.1;//������ �����
				}

				if (Keyboard::isKeyPressed(Keyboard::Down)) {
					p.dir = 2; p.speed = 0.1;//������ ����
				}
				
				if (Keyboard::isKeyPressed(Keyboard::M)) { music.pause(); sounds = false; }	//���������� �����
				if (Keyboard::isKeyPressed(Keyboard::N)) { music.play(); sounds = true; }   //��������� �����
			}
			else												//������ ��������� ������� ��
			{
				k++;//��� ������������ ������������ �������
				if (k == 1)
				{
					tops(top10, p.playerScore, p.name);			//����������� �������
					if (sounds)									//���� ����� �������, ��
					{
						music.stop();							//��������� ������
						theEnd.play();							//�� ���������� ���� ��������
					}
				}
			}
			
			if (Keyboard::isKeyPressed(Keyboard::Tab)) { return true; }				//���� Tap, �� ��������������� ���
			if (Keyboard::isKeyPressed(Keyboard::Escape)) { return false; }			//���� Esc, �� �������� �� ���


			//update
			{
				p.update(time);
				e0.update(time);
				e1.update(time);
				e2.update(time);
				e3.update(time);
				e4.update(time);
			}

			//++poit
			if (p.life)		//���� ������� �����, �� ���� ���� ���� ���� ������ �������� �� ��� �����
			{
				p.playerScore += e0.point;
				p.playerScore += e1.point;
				p.playerScore += e2.point;
				p.playerScore += e3.point;
				p.playerScore += e4.point;
			}
			
			//getRect
			{
				//���� ����������� ������ ������������ � ������������� ������, �� �� �����
				if (e0.getRect().intersects(p.getRect()))
				{
					p.life = false;	
				}
				if (e1.getRect().intersects(p.getRect()))
				{
					p.life = false;
				}
				if (e2.getRect().intersects(p.getRect()))
				{
					p.life = false;
				}
				if (e3.getRect().intersects(p.getRect()))
				{
					p.life = false;
				}
				if (e4.getRect().intersects(p.getRect()))
				{
					p.life = false;
				}
			}

			window.clear(Color::White);//������� ���� �� ������ ���� ���

					//������ �����//
			for (auto i = 0; i < HEIGHT_MAP; i++)
				for (auto j = 0; j < WIDTH_MAP; j++)
				{
					if (TileMap[i][j] == '0')  s_map.setTextureRect(IntRect(0, 0, 32, 32));//���� ����������� ������ 0, �� ������� 1� ���������
					if (TileMap[i][j] == ' ')  s_map.setTextureRect(IntRect(32, 0, 32, 32));//���� ����������� ������ Space , �� ������� 2� ���������
					if (TileMap[i][j] == '|')  s_map.setTextureRect(IntRect(64, 0, 32, 32));//���� ����������� ������  |, �� ������� 3� ���������

					//�� ��� ������� ����������, ������������ � �����. ����� ���� ������� � ��� �������. ���� ��������, �� ��� ����� ����������� � ������ ������� 32 * 32 � �� �������� ���� �������
					s_map.setPosition(j * 32, i * 32);

					window.draw(s_map);								//������� ���������� �� �����
				}

			ostringstream  playerScoreString;						// ��'����� �����
			playerScoreString << p.playerScore;						//������� � �� ����� ����, ����� ��������� �����
			text.setString("Points: " + playerScoreString.str());	//������ ����� ������ �� �������� ����������� ����� ������� .str()
			text.setPosition(500, 0);							//������ ������� ������
			window.draw(text);										//�������� ����� �� �����
			
			text.setString("N - sounds on\nM - sounds off\nTab - restart\nEsc - exit"); //����� � ������������
			text.setPosition(400, 500);												//������� ������
			window.draw(text);															//�������� ����� �� �����

			if (sounds)					//���� ����� �������, �� 
			{
				window.draw(s_on);		//�������� �������� ����������
			}
			else						//������
			{
				window.draw(s_off);		//�������� �������� ����������
			}
			
			if (p.life)					//���� ������� �����, �� ������� ������ �� ��� ������
			{
				window.draw(e0.sprite);
				window.draw(e1.sprite);
				window.draw(e2.sprite);
				window.draw(e3.sprite);
				window.draw(e4.sprite);
				window.draw(p.sprite);
			}
			else						//������ ������� ������ �������� 
			{
				window.draw(s_end);
			}
			window.display();			//�������� ����
		}
		return 1;
}