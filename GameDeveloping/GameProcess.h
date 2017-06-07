#pragma once
#include "Header.h"

class GameLoop
{
private:
	int myHealth;
	float time;
	//-Переменные второго игрока
	float p2posX, p2posY, p2Rotation, mousePos2pX, mousePos2pY; //Переменные второго игрока
	Vector2f mousePos2p; //Переменная для хранения координат указателя мыши второго игрока
	int enemyHealth;
	int bulletdmg;
	bool myshot, enemyshot;

	Clock clock; //Класс зафиксированного времени игры
	HUD hud; //Класс интерфейса 

	Packet packetinput;
	Packet packetoutput;
	bool queue = true;
	bool settedqueue = false;

	Text p1win, p2win, restartButton;
	Font font;

	Bullet bullet;
	vector <Bullet> bulletsvector; //Вектор пуль первого игрока
	vector <Bullet> bulletsvector2p;
	float p1rotation;
	int menuNum;
public:
	GameLoop()
	{
		hud.init();
		font.loadFromFile("font.ttf");
		
		p1win.setFont(font);
		p1win.setString("Player 1 WIN!");
		p1win.setCharacterSize(70);
		p1win.setOrigin(p1win.getLocalBounds().width / 2, p1win.getLocalBounds().height / 2);
		p1win.setOutlineThickness(2);

		p2win.setFont(font);
		p2win.setString("You are DEAD!");
		p2win.setCharacterSize(70);
		p2win.setOrigin(p2win.getLocalBounds().width / 2, p2win.getLocalBounds().height / 2);
		p2win.setOutlineThickness(2);

		restartButton.setFont(font);
		restartButton.setString("Restart");
		restartButton.setCharacterSize(30);
		restartButton.setOrigin(restartButton.getLocalBounds().width / 2, restartButton.getLocalBounds().height / 2);
		restartButton.setOutlineThickness(2);
	}
	void render(RenderWindow &window, Player &p1, Player &p2, bool &pressedBut, int &hostChoosed, int &gamestate, TcpSocket &socket, Maps &map, vector <Object> &obj, Vector2f &MousePos)
	{
		if (hostChoosed == 1 && settedqueue == false) { queue = false; settedqueue = true; }
		else if (hostChoosed == 0 && settedqueue == false) { queue = true; settedqueue = true; }

		window.clear(); //Обновление экрана
		time = clock.getElapsedTime().asMilliseconds(); //Измерение времени в микросекундах
		clock.restart(); //Перезагружаем время
		time = time / 80; //Задаем общую скорость игры
		
		//--Способности и управление
		p1rotation = p1.getRotation();
		p1.skills(bullet);
		p1.moving(time, obj, pressedBut, bulletsvector, bullet, map, window, MousePos, myshot, p1rotation);
		getPosForPlayer(p1.getSpritePos().x, p1.getSpritePos().y); //Камера вида

		packetoutput.clear();
		packetinput.clear();
		
		//Отправляем пакеты противнику
		if (queue == false || myshot == true)
		{
			packetoutput << p1.getSpritePos().x << p1.getSpritePos().y << p1rotation << p1.getHealth() << p2.getHealth() << bullet.getDamage() << myshot; //Запаковка пакета
			socket.send(packetoutput); //Отправка пакета
			queue = true; // Дает очередь второму игроку
		}
		if (!socket.receive(packetinput)) //Прием пакетов от противника если они приходят
		{
			packetinput >> p2posX >> p2posY >> p2Rotation >> enemyHealth >> myHealth >> bulletdmg >> enemyshot; // Распаковка
			if ((p2.getSpritePos().x != p2posX) || (p2.getSpritePos().y != p2posY)) { p2.animation(time); } // Анимация второго игрока
			if (p1.getHealth() != myHealth) { p1.setHealth(myHealth); } //Синхронизация здоровья
			p2.setPosition(p2posX, p2posY); //Обновление позиции
			p2.sprite.setRotation(p2Rotation); // Обновление 
			if (enemyshot == true) //Проверка на выстрел противника
			{
				bulletsvector2p.push_back(bullet); // Добавление пули в вектор
				bulletsvector2p[bulletsvector2p.size() - 1].create(p2.getSpritePos().x, p2.getSpritePos().y, p2Rotation); //Выстрел
			}
			queue = false; //Дает очередь первому игроку
		}
	
		if (Keyboard::isKeyPressed(Keyboard::Escape)) { gamestate = 9; } //Рестарт игры по кнопке

		enemyshot = false;
		myshot = false;

		window.setView(view); //Обновление камеры вида
		map.Draw(window); //Вывод и обновление карты
		window.draw(p1.sprite); //Вывод и обновление первого игрока
		window.draw(p2.sprite); //Вывод и обновление второго игрока
		hud.draw(window, p1, p2);
		
	//-----------------------Взаимодействие с объектами и отображение пуль первого игрока-----------------------
		for (int j = 0; j < obj.size(); j++)//проходимся по объектам карты
			for (int i = 0; i < bulletsvector.size(); i++) //проходимся по вектору пуль
			{
				if (bulletsvector[i].getBulletRect().intersects(obj[j].rect)) //Проверяем касание с объектами карты
				{
					if (obj[j].name == "solid")//если встретили препятствие
					{
						bulletsvector.erase(bulletsvector.begin() + i); //Удаление пули
					}
				}
			}
		// Проверка попадания пули в игрока
		for (int i = 0; i < bulletsvector.size(); i++) 
		{
			bulletsvector[i].update(time); // Обновление пули
			if (bulletsvector[i].getBulletRect().intersects(p2.getGlobalBounds())) //Проверяем касание с игроком
			{
				bulletsvector.erase(bulletsvector.begin() + i); //Удаление пули
				p2.setHealth(p2.getHealth() - bullet.getDamage()); // Нанесение урока
			}

		}
		// Вывод и обновление пуль
		for (int i = 0; i < bulletsvector.size(); i++) 
			window.draw(bulletsvector[i].sprite);
	//----------------------Взаимодействие с объектами и отображение пуль второго игрока------------------------
	//проходимся по объектам
		for (int j = 0; j < obj.size(); j++)//проходимся по объектам карты
			for (int i = 0; i < bulletsvector2p.size(); i++)//проходимся по вектору пуль
			{
				if (bulletsvector2p[i].getBulletRect().intersects(obj[j].rect))//проверяем пересечение игрока с объектом
				{
					if (obj[j].name == "solid")//если встретили препятствие
					{
						bulletsvector2p.erase(bulletsvector2p.begin() + i); //Удаление пули
					}
				}
			}

		for (int i = 0; i < bulletsvector2p.size(); i++)
		{
			bulletsvector2p[i].update(time); // Обновление пули
			if (bulletsvector2p[i].getBulletRect().intersects(p1.getGlobalBounds())) //Проверяем касание с игроком
			{
				bulletsvector2p.erase(bulletsvector2p.begin() + i); //Удаление пули
				p1.setHealth(p1.getHealth() - bulletdmg); // Нанесение урока
			}

		}
		// Вывод и обновление пуль
		for (int i = 0; i < bulletsvector2p.size(); i++) // Вывод и обновление пуль
			window.draw(bulletsvector2p[i].sprite);

		//Проверка для окончания игры		
		if (p1.getHealth() <= 0)
		{
			while (true)
			{
				window.clear();
				p2win.setPosition(p1.getSpritePos().x,p1.getSpritePos().y-200);
				restartButton.setPosition(p1.getSpritePos().x, p1.getSpritePos().y);
				restartButton.setFillColor(Color::White);
				menuNum = 0;
				if (restartButton.getGlobalBounds().contains(Vector2f(window.mapPixelToCoords(Mouse::getPosition(window))))) { restartButton.setFillColor(Color::Blue); menuNum = 1; }
				if (Mouse::isButtonPressed(Mouse::Button::Left) && pressedBut == false)
				{
					pressedBut = true;
					if (menuNum == 1) { gamestate = 9; break; }
				}
				window.draw(p2win);
				window.draw(restartButton);
				window.display();
			}
		}
		else if (p2.getHealth() <= 0)
		{
			while (true)
			{
				window.clear();
				p1win.setPosition(p1.getSpritePos().x, p1.getSpritePos().y - 200);
				restartButton.setPosition(p1.getSpritePos().x, p1.getSpritePos().y);
				restartButton.setFillColor(Color::White);
				menuNum = 0;
				if (restartButton.getGlobalBounds().contains(Vector2f(window.mapPixelToCoords(Mouse::getPosition(window))))) { restartButton.setFillColor(Color::Blue); menuNum = 1; }
				if (Mouse::isButtonPressed(Mouse::Button::Left)) //&& pressedBut == false)
				{
					//pressedBut = true;
					if (menuNum == 1) { gamestate = 9; break; }
				}
				window.draw(p1win);
				window.draw(restartButton);
				window.display();
			}
		}

		window.display(); //Инициализация дисплея
	}
};