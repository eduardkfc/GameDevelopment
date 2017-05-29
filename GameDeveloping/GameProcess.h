#pragma once
#include "Header.h"

class MainGame
{
private:
	int gamePaused, enemyHealth, myHealth;
	float time;
	float p2posX, p2posY, p2Rotation, mousePos2pX, mousePos2pY;
	Clock clock;
	Event events; 
	HUD hud;
	unsigned short port;
	Vector2f mousePos2p; //Переменная для хранения координат указателя мыши второго игрока
	Packet packetinput;
	Packet packetoutput;
	Text p1win, p2win, restartButton;
	Font font;
	Bullet bullet;
	int menuNum;
	vector <Bullet> bulletsvector; //Вектор пуль первого игрока
	vector <Bullet> bulletsvector2p;
	int bulletdmg;
	bool myshot, enemyshot;
public:
	MainGame(Player &p1,Player &p2,int &MapsID,int &hostChoosed)
	{
		hud.init();
		font.loadFromFile("font.ttf");
		if (MapsID == 1 && hostChoosed == 1)
		{
			p1.setPosition(100, 100);
			p2.setPosition(1113, 1495);
		}
		if (MapsID == 1 && hostChoosed == 0)
		{
			p2.setPosition(100, 100);
			p1.setPosition(1113, 1495);
		}
		if (MapsID == 2 && hostChoosed == 1)
		{
			p1.setPosition(119,107);
			p2.setPosition(813,1154);
		}
		if (MapsID == 2 && hostChoosed == 0)
		{
			p2.setPosition(119, 107);
			p1.setPosition(813, 1154);
		}
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
	void render(RenderWindow &window,Player &p1,Player &p2,bool &pressedBut,int &hostChoosed,int &gamestate,UdpSocket &socket,IpAddress &enemyip,Maps &map,vector <Object> &obj, Vector2f &MousePos)
	{
		
		if (hostChoosed == 1) { port = 55002; }
		else port == 55001;
		cout << p1.getSpritePos().x << p1.getSpritePos().y << endl;

		window.clear(); //Обновление экрана
		time = clock.getElapsedTime().asMilliseconds(); //Измерение времени в микросекундах
		clock.restart(); //Перезагружаем время
		time = time / 80; //Задаем общую скорость игры
		
		//--Способности--
		p1.skills(bullet);
		p1.moving(time, obj, pressedBut, bulletsvector, bullet, map, window, MousePos, myshot);
		getPosForPlayer(p1.getSpritePos().x, p1.getSpritePos().y);
		
		if (window.pollEvent(events)) //Проверка закрытия окна
			if (events.type == Event::Closed) window.close();

		packetoutput << p1.getSpritePos().x << p1.getSpritePos().y << p1.getRotation() << MousePos.x << MousePos.y << p1.getHealth() << p2.getHealth() << bullet.getDamage() << myshot;
		socket.send(packetoutput, enemyip, port);
		packetoutput.clear();

		packetinput.clear();

		if (!socket.receive(packetinput, enemyip, port))
		{
			packetinput >> p2posX >> p2posY >> p2Rotation >> mousePos2pX >> mousePos2pY >> enemyHealth >> myHealth >> bulletdmg >> enemyshot;
			if (p1.getHealth() != myHealth)
			{
				p1.setHealth(myHealth);
			}
			mousePos2p.x = mousePos2pX;
			mousePos2p.y = mousePos2pY;
			if ((p2.getSpritePos().x != p2posX) || (p2.getSpritePos().y != p2posY)) { p2.animation(time); }
			p2.setPosition(p2posX, p2posY);
			p2.sprite.setRotation(p2Rotation);
			cout << p2posX << " " << p2posY << "Second Player" << endl;
		}
		
		if (Keyboard::isKeyPressed(Keyboard::J)) { enemyshot = true; }

		if (enemyshot == true) 
		{ 
			bulletsvector2p.push_back(bullet);
			bulletsvector2p[bulletsvector2p.size()-1].create(p2.getSpritePos().x,p2.getSpritePos().y,mousePos2p);
		}
		if (Keyboard::isKeyPressed(Keyboard::U)) { p1.setHealth(p1.getHealth()-1); }
		if (Keyboard::isKeyPressed(Keyboard::I)) { p2.setHealth(p2.getHealth() - 1); }
		if (Keyboard::isKeyPressed(Keyboard::H)) { p2.sprite.move(0, p1.getSpeed()*time); }

		enemyshot = false;
		myshot = false;

		window.setView(view);
		map.Draw(window); //Вывод и обновление карты
		window.draw(p1.sprite); //Вывод и обновление первого игрока
		window.draw(p2.sprite); //Вывод и обновление второго игрока
		hud.draw(window, p1, p2);
		
		for (int j = 0; j < obj.size(); j++)//проходимся по объектам
			for (int i = 0; i < bulletsvector.size(); i++)
			{
				//cout << "error";

				if (bulletsvector[i].getBulletRect().intersects(obj[j].rect))//проверяем пересечение игрока с объектом
				{
					if (obj[j].name == "solid")//если встретили препятствие
					{
						bulletsvector.erase(bulletsvector.begin() + i);
					}
				}
			}
		for (int i = 0; i < bulletsvector.size(); i++)
		{
			bulletsvector[i].update(time);
			if (bulletsvector[i].getBulletRect().intersects(p2.getGlobalBounds()))
			{
				cout << "POPADANIE"; bulletsvector.erase(bulletsvector.begin() + i);
				p2.setHealth(p2.getHealth() - bullet.getDamage());
			}

		}
		for (int i = 0; i < bulletsvector.size(); i++) // Вывод и обновление пуль
			window.draw(bulletsvector[i].sprite);
		//----------------------------------------------------------------------------------
		for (int j = 0; j < obj.size(); j++)//проходимся по объектам
			for (int i = 0; i < bulletsvector2p.size(); i++)
			{
				if (bulletsvector2p[i].getBulletRect().intersects(obj[j].rect))//проверяем пересечение игрока с объектом
				{
					if (obj[j].name == "solid")//если встретили препятствие
					{

						bulletsvector2p.erase(bulletsvector2p.begin() + i);
					}
				}
			}
		for (int i = 0; i < bulletsvector2p.size(); i++)
		{
			bulletsvector2p[i].update(time);
			if (bulletsvector2p[i].getBulletRect().intersects(p1.getGlobalBounds()))
			{
				cout << "POPADANIE"; bulletsvector2p.erase(bulletsvector2p.begin() + i);
				p1.setHealth(p1.getHealth() - bullet.getDamage());
			}

		}
		for (int i = 0; i < bulletsvector2p.size(); i++) // Вывод и обновление пуль
			window.draw(bulletsvector2p[i].sprite);
		
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
					if (menuNum == 1) { socket.unbind(); gamestate = 9; break; }
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
					if (menuNum == 1) { cout << "kek"; socket.unbind(); gamestate = 9; break; }
				}
				window.draw(p1win);
				window.draw(restartButton);
				window.display();
			}
		}
		window.display(); //Инициализация дисплея
	}
};