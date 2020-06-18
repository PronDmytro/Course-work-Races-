#include <SFML/Graphics.hpp>			//бібліотека для роботи з 2D графікою
#include <SFML/Audio.hpp>				//бібліотека для роботи з звуком
#include <sstream>						//бібліотека для роботи з рядками
#include <time.h>						//бібліотека для роботи з часом
#include <iomanip>						//бібліотека для мніпуляції рядками
#include "Entity.h"						//клас гравця
#include "Player.h"						//клас ворога
#include "map.h"						//карта
#include "Structure.h"					//оголошені структури
#include "Functions.h"					//оголошені функціїї

using namespace sf;						//використовуємо прстір імен sf для роботи з бібліотеками SFML
using namespace std;

int game(top top10[],string player_name)
{
	
		//створюємо вікно з заданими розмірами та назвою
		RenderWindow window(sf::VideoMode(640, 608), "NFS");

	
		SoundBuffer gameOver;									//звуковий буфер
		gameOver.loadFromFile("audio/game over.ogg");	//загружаємо звук програшу в буфер
		Sound theEnd(gameOver);									//створюємо змінну з посиланням на звук програшу загружений в бу

		int k = 0;												//допоміжна змінна

		Music music;											//створюємо обєкт музики
		music.openFromFile("audio/nfs.ogg");				//загружаємо файл
		music.play();											//відтворюємо музику

		Font font;												//шрифт
		font.loadFromFile("others/CyrilicOld.ttf");		//передаем нашему шрифту файл шрифта
		Text text("", font, 20);				//створюємо обєкт текст, закидуваємо в обєкт текст рядок, шрифт, розмір шрифта(в пікселях)
		text.setFillColor(Color::Red);							//покрасили текст в червоний

		Image map_image;										//обєкт зображення для карти
		map_image.loadFromFile("images/map.png");		//загружаємо файл для карти
		Texture map;											//текстура карти
		map.loadFromImage(map_image);							//заряжаем текстуру зоброженням
		Sprite s_map;											//створюємо спрайт для карти
		s_map.setTexture(map);									//заливаємо текстуру спрайтом

		//зображення програшної заставки//
		Image end_image;
		end_image.loadFromFile("images/wasted.png");
		Texture end;
		end.loadFromImage(end_image);
		Sprite s_end;
		s_end.setTexture(end);
		s_end.setPosition(30, 150);

		//зображення для відображення наявності звуку//
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


					//створення класу гравця//
		Player p("pcar.png", player_name, 150, 500, 45, 104);//передаємо назву файла, ім'я гравця, почаикові координати та розміри машинки
					//створення класів ворогів//
		Entity e0("car.png", 50, -150, 45, 104);
		Entity e1("car.png", 100, -400, 45, 104);
		Entity e2("car.png", 150, -600, 45, 104);
		Entity e3("car.png", 200, -600, 45, 104);
		Entity e4("car.png", 250, -750, 45, 104);
		
		
	
		srand(time(NULL));

		bool sounds=true;//наявність звуків
		
		Clock clock;

	/*
		 Обов'язковий цикл для SFML,
		 який можете переводити для розуміння як:
		"Поки вікно відкрите - виконуй те, що всередині циклу",
	 */
		while (window.isOpen())
		{
			Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();
			}
			
			float time = clock.getElapsedTime().asMicroseconds();	//змінна з пройденим часом в мікросекундах
			clock.restart();										//перезавантажує час
			time = time / 800;										//швидкість гри

			//отримуємо координати машинки гравця//
			float coordinatePlayerX, coordinatePlayerY = 0;
			coordinatePlayerX = p.get_player_coordinate_x();
			coordinatePlayerY = p.get_player_coordinate_y();
			if (p.life)												//якщо гравець живий то ми можемо ним керувати
			{
				if (Keyboard::isKeyPressed(Keyboard::Left)) {
					p.dir = 1; p.speed = 0.1;						//dir =1 - напрям вліво, speed =0.1 - швидкість руху
				}

				if (Keyboard::isKeyPressed(Keyboard::Right)) {
					p.dir = 0; p.speed = 0.1;;//напрям вправо
				}

				if (Keyboard::isKeyPressed(Keyboard::Up)) {
					p.dir = 3; p.speed = 0.1;//напрям вверх
				}

				if (Keyboard::isKeyPressed(Keyboard::Down)) {
					p.dir = 2; p.speed = 0.1;//напрям вниз
				}
				
				if (Keyboard::isKeyPressed(Keyboard::M)) { music.pause(); sounds = false; }	//виключення звуків
				if (Keyboard::isKeyPressed(Keyboard::N)) { music.play(); sounds = true; }   //включення звуків
			}
			else												//інакше керування пропадає та
			{
				k++;//для забезпечення одноразового повтору
				if (k == 1)
				{
					tops(top10, p.playerScore, p.name);			//оновлюється рейтинг
					if (sounds)									//якщо звуки включені, то
					{
						music.stop();							//зупиняємо музику
						theEnd.play();							//та відтворюємо звук програшу
					}
				}
			}
			
			if (Keyboard::isKeyPressed(Keyboard::Tab)) { return true; }				//якщо Tap, то перезавантажуємо гру
			if (Keyboard::isKeyPressed(Keyboard::Escape)) { return false; }			//якщо Esc, то виходимо из гри


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
			if (p.life)		//якщо гравець живий, то даємо йому очки коли вороги виходять за межі карти
			{
				p.playerScore += e0.point;
				p.playerScore += e1.point;
				p.playerScore += e2.point;
				p.playerScore += e3.point;
				p.playerScore += e4.point;
			}
			
			//getRect
			{
				//якщо прямокутник ворога перетинається з прямокутником гравця, то він вмирає
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

			window.clear(Color::White);//чистить вікно та робить білий фон

					//будуємо карту//
			for (auto i = 0; i < HEIGHT_MAP; i++)
				for (auto j = 0; j < WIDTH_MAP; j++)
				{
					if (TileMap[i][j] == '0')  s_map.setTextureRect(IntRect(0, 0, 32, 32));//якщо зустрінеться символ 0, то малюємо 1й квадратик
					if (TileMap[i][j] == ' ')  s_map.setTextureRect(IntRect(32, 0, 32, 32));//якщо зустрінеться символ Space , то малюємо 2й квадратик
					if (TileMap[i][j] == '|')  s_map.setTextureRect(IntRect(64, 0, 32, 32));//якщо зустрінеться символ  |, то малюємо 3й квадратик

					//по суті розкидає квадратики, перетворюючи в карту. тобто задає кожному з них позицію. якщо прибрати, то вся карта вималюється в одному квадраті 32 * 32 і ми побачимо один квадрат
					s_map.setPosition(j * 32, i * 32);

					window.draw(s_map);								//малюємо квадратики на екран
				}

			ostringstream  playerScoreString;						// об'явили змінну
			playerScoreString << p.playerScore;						//занесли в неї число очків, тобто створюємо рядок
			text.setString("Points: " + playerScoreString.str());	//задаємо рядок тексту та визиваємо зформований рядок методом .str()
			text.setPosition(500, 0);							//задаємо позицію текста
			window.draw(text);										//виводимо текст на екран
			
			text.setString("N - sounds on\nM - sounds off\nTab - restart\nEsc - exit"); //текст з інструкціями
			text.setPosition(400, 500);												//позиція тексту
			window.draw(text);															//виводимо текст на екран

			if (sounds)					//якщо звуки включені, то 
			{
				window.draw(s_on);		//виводимо відповідне зображення
			}
			else						//інакше
			{
				window.draw(s_off);		//виводимо відповідне зображення
			}
			
			if (p.life)					//якщо гравець живий, то малюємо гравця та всіх ворогів
			{
				window.draw(e0.sprite);
				window.draw(e1.sprite);
				window.draw(e2.sprite);
				window.draw(e3.sprite);
				window.draw(e4.sprite);
				window.draw(p.sprite);
			}
			else						//інакше малюємо кінцеву заставку 
			{
				window.draw(s_end);
			}
			window.display();			//виводимо вікно
		}
		return 1;
}