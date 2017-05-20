#include "Header.h" //Подключаем header

using namespace sf; //Убираем использование sf::
using namespace std; //Убираем использование std::

void threadFunction()
{
	while (true)
	{
		cout << "Esli eta huynya rabotaet to edik pidor" << endl;
	}
}


bool startGame() 
{
	int hostChoosed;
	int gamestate = 1;
	RenderWindow window(VideoMode(1280, 720), "Reflex Strike", Style::None); //Инициализируем окно
	view.reset(FloatRect(0, 0, 1280, 720)); //Перезагрузка экрана
	window.setVerticalSyncEnabled(true); //Включение вертикальной синхронизации
	window.setFramerateLimit(60); //Лимит кадров в секунду
	vector <Object> obj;
	Vector2i Pixelpos; //Переменная для получения местонахождения мыши
	Vector2f mousePos1p; //Переменная для хранения координат указателя мыши первого игрока
	Vector2f mousePos2p; //Переменная для хранения координат указателя мыши второго игрока
	int gamePaused = 0;
	int damage = 10;
	bool pressedBut = false;
	int pressedbut = 0; //Переменная для проверки нажатия кнопки мыши(
	Level map; //Создаем объект класса карты
	map.LoadFromFile("map.xml"); //Грузим нашу карту

	//-----------------------------------Для перезарядки способностей-----------------------
	
	Player p1("soldier1.png", 500, 500, map, 1); //Создаем объект класса игрок
	Player p2("soldier1.png", 600, 600, map, 2); //Создаем объект класса игрок
	Bullet bullet("bullet.png");
	vector <Bullet> bulletsvector; //Вектор пуль первого игрока
	vector <Bullet> bulletsvector2p;
	TcpSocket socket;
	TcpListener listener;
	socket.setBlocking(false);
	listener.setBlocking(false);
	float time; //Создаем переменную для хранения скорости игры
	Clock clock; //Создаем объект класса времени, для задания скорости игры
	obj = map.GetAllObjects();
	Event events; //Создаем объект класса событие
	MainMenu menu;
	ChooseHost chosinghost;
	WaitingForPlayers waitplayers;
	WaitingForServer waitserver;
	Color color(255, 0, 0);
	//thread thr(threadFunction);
	//thr.detach();
	
	HUD hud; hud.init();
	Packet packetinput;
	Packet packetoutput;
	float p1posX, p1posY, p1Rotation;
	float p2posX, p2posY, p2Rotation, mousePos2pX,mousePos2pY;
	int enemyHealth, myHealth;
	FloatRect p2Rect;
	while (window.isOpen()) //Цикл, пока открыто окно, он действует
	{	
		if (gamestate == 0) { return false; }
		else if (gamestate == 1) { menu.render(window, gamestate,pressedBut); }
		else if (gamestate == 2) { chosinghost.render(window, gamestate, hostChoosed, socket, listener,pressedBut); }
		else if (gamestate == 3) { waitplayers.render(window, gamestate, listener, pressedBut, socket); }
		else if (gamestate == 4) { waitserver.render(window, gamestate, socket, pressedBut); }
		else if (gamestate == 5)
		{
			
			window.clear(); //Обновление экрана
			time = clock.getElapsedTime().asMilliseconds(); //Измерение времени в микросекундах
			clock.restart(); //Перезагружаем время
			
			time = time * 5.4; //Задаем общую скорость игры
			//--Способности--
			p1.skills(bullet);
			//speed();
			//-------------------------Управление первым игроком-----------------------------
			//cout << ddtime << endl;
			Pixelpos = Mouse::getPosition(window); //Получение значений местонахождения мыши
			mousePos1p = window.mapPixelToCoords(Pixelpos); //Конвертирование в координаты положения мыши
			if (window.pollEvent(events)) //Проверка закрытия окна
				if (events.type == Event::Closed) window.close();
			
			p2Rect = p2.getRect();
			p1.moving(time, mousePos1p, obj, pressedbut,bulletsvector, bullet);
			getPosForPlayer(p1.getSpritePos().x, p1.getSpritePos().y);
			p1posX = p1.getSpritePos().x;
			p1posY = p1.getSpritePos().y;
			//cout << p1posX << " " << p1posY << "First Player" << endl;
			p1Rotation = p1.sprite.getRotation();
			packetoutput << p1posX << p1posY << p1Rotation << mousePos1p.x << mousePos1p.y << p1.getHealth() << p2.getHealth();
			socket.send(packetoutput);
			packetoutput.clear();
			
			bullet.updateDatas(p1.getSpritePos().x, p1.getSpritePos().y, mousePos1p, p1.getSpriteOrigin());
			

			//----------------------Управление вторым игроком----------------------------------
			
			packetinput.clear();
			if (!socket.receive(packetinput))
			{ 
				packetinput >> p2posX >> p2posY >> p2Rotation >> mousePos2pX >> mousePos2pY >> enemyHealth >> myHealth;
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
			if (Keyboard::isKeyPressed(Keyboard::Tab)) { return true; }
			if (Keyboard::isKeyPressed(Keyboard::Escape)) { return false; }
			if (Keyboard::isKeyPressed(Keyboard::T)) { p1.setHealth(bullet.getDamage()); cout << p1.getHealth(); }
			if (Keyboard::isKeyPressed(Keyboard::U)) { p1.setHealth(100); }
			//if (p1.getHealth() == 0 || p2.getHealth() == 0) { return true; }

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
	

			
			

			window.display(); //Инициализация дисплея
			
		}
		if (!Mouse::isButtonPressed(Mouse::Button::Left)) // Проверка на единичное нажатие клавиши
			pressedBut = false;
		
	}
}

void gameRunning() 
{
	if (startGame()) { gameRunning(); }
}

int main() //Главная функция игры
{

	gameRunning();
	return 0;
}


