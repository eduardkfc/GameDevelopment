#include "Header.h" //Подключаем header

using namespace sf; //Убираем использование sf::
using namespace std; //Убираем использование std::




void menu(RenderWindow &window)
{
	Texture mainscreen, buttonStart, buttonSettings, buttonExit;
	mainscreen.loadFromFile("mainscreen.jpg");
	buttonStart.loadFromFile("buttons/startgame.jpg");
	buttonSettings.loadFromFile("buttons/settings.jpg");
	buttonExit.loadFromFile("buttons/exit.jpg");
	Sprite menubg(mainscreen), menu1(buttonStart), menu2(buttonSettings), menu3(buttonExit);
	
	bool isMenu = 1;
	int menuNum = 0;
	menu1.setPosition(540, 310);
	menu2.setPosition(200, 310);
	menu3.setPosition(880, 310);
	while (isMenu)
	{
		menu1.setColor(Color::White);
		menu2.setColor(Color::White);
		menu3.setColor(Color::White);
		menuNum = 0;
		window.clear(Color(129, 181, 221));
		if (IntRect(540, 310, 200, 66).contains(Mouse::getPosition(window))) { menu1.setColor(Color::Blue); menuNum = 1; }
		if (IntRect(200, 310, 200, 66).contains(Mouse::getPosition(window))) { menu2.setColor(Color::Blue); menuNum = 2; }
		if (IntRect(880, 310, 200, 66).contains(Mouse::getPosition(window))) { menu3.setColor(Color::Blue); menuNum = 3; }

		if (Mouse::isButtonPressed(Mouse::Left))
		{
			if (menuNum == 1) isMenu = false;
			if (menuNum == 2) { cout << "sasha pidor"; }
			if (menuNum == 3) { window.close(); isMenu = false; }
		}
		window.clear();
		window.draw(menubg);
		window.draw(menu1);
		window.draw(menu2);
		window.draw(menu3);
		window.display();
	}
	
}

bool startGame() 
{
	RenderWindow window(VideoMode(1280, 720), "Reflex Strike", Style::None); //Инициализируем окно
	view.reset(FloatRect(0, 0, 1280, 720)); //Перезагрузка экрана
	window.setVerticalSyncEnabled(true); //Включение вертикальной синхронизации
	menu(window);
	vector <Object> obj;
	Vector2i Pixelpos; //Переменная для получения местонахождения мыши
	Vector2f pos; //Переменная для хранения координат указателя мыши

	int gamestate = 1;
	int pressedbut = 0; //Переменная для проверки нажатия кнопки мыши(
	Level map; //Создаем объект класса карты
	map.LoadFromFile("map.xml"); //Грузим нашу карту
	vector <Bullet> bullets1pl; //Вектор пуль
	Player p1("soldier1.png", 500, 500, map, 1); //Создаем объект класса игрок
	Player p2("soldier1.png", 600, 600, map, 2); //Создаем объект класса игрок


	float time; //Создаем переменную для хранения скорости игры
	Clock clock; //Создаем объект класса времени, для задания скорости игры

	while (window.isOpen()) //Цикл, пока открыто окно, он действует
	{

		Pixelpos = Mouse::getPosition(window); //Получение значений местонахождения мыши
		pos = window.mapPixelToCoords(Pixelpos); //Конвертирование в координаты положения мыши
		time = clock.getElapsedTime().asMicroseconds(); //Измерение времени в микросекундах
		clock.restart(); //Перезагружаем время
		time = time / 150; //Задаем общую скорость игры
		Bullet bullet("bullet.png", p1.getSpritePos().x, p1.getSpritePos().y, p1.getSpriteOrigin(), pos, time);
		Event event; //Создаем объект класса событие
		if (window.pollEvent(event)) //Проверка закрытия окна
		{
			if (event.type == Event::Closed) window.close();
		}

		if (Mouse::isButtonPressed(Mouse::Button::Left) && pressedbut == 0) //Проверка единичного нажатия на клавишу мыши
		{
			cout << "fire";
			pressedbut = 1;
			bullets1pl.push_back(bullet);
		}

		if (Mouse::isButtonPressed(Mouse::Button::Left)) { pressedbut = 1; } // Проверка единичного нажатия на клавишу
		else pressedbut = 0;

		obj = map.GetAllObjects();

		p1.moving(time, pos, window,obj);
		getPosForPlayer(p1.getSpritePos().x, p1.getSpritePos().y);
		

		if (Keyboard::isKeyPressed(Keyboard::Tab)) { return true; }
		if (Keyboard::isKeyPressed(Keyboard::Escape)) { return false; }
		window.clear(); //Обновление экрана
		window.setView(view);
		map.Draw(window); //Вывод и обновление карты
		window.draw(p1.sprite); //Вывод и обновление первого игрока
		window.draw(p2.sprite); //Вывод и обновление второго игрока
		for (int i = 0; i<bullets1pl.size(); i++) // Вывод и обновление пуль
			window.draw(bullets1pl[i].sprite);
			
		for (int i = 0; i<bullets1pl.size(); i++)
		{
			bullets1pl[i].update();
			if (p2.getRect().contains(bullets1pl[i].getBulletSprPos())) { cout << "POPADANIE"; }
			
			if (bullets1pl[i].getBulletSprPos().x > 960 || bullets1pl[i].getBulletSprPos().y > 1280 || p2.getRect().contains(bullets1pl[i].getBulletSprPos()))
			{
				bullets1pl.erase(bullets1pl.begin() + i); //удаление элемента вектора(пули)
			}
			else if (bullets1pl[i].getBulletSprPos().x < 0 || bullets1pl[i].getBulletSprPos().y < 0)
			{
				bullets1pl.erase(bullets1pl.begin() + i); //удаление элемента вектора(пули)
			}

		}
		window.display(); //Инициализация дисплея
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


