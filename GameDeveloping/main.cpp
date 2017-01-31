#include "Header.h" //Подключаем header

using namespace sf; //Убираем использование sf::
using namespace std; //Убираем использование std::

int main() //Главная функция игры
{
	
	RenderWindow window(VideoMode(1280,720), "Reflex Strike",Style::Close); //Инициализируем окно
	view.reset(FloatRect(0, 0, 1280, 720)); //Перезагрузка экрана
	
	
	window.setVerticalSyncEnabled(true); //Включение вертикальной синхронизации
	Level map; //Создаем объект класса карты
	map.LoadFromFile("map.xml"); //Грузим нашу карту
	Player p1("soldier1.png", 500, 500, map, 1); //Создаем объект класса игрок
	Player p2("soldier1.png", 600, 600, map, 2); //Создаем объект класса игрок
	vector <Bullet> bullets1pl; //Вектор пуль
	float time; //Создаем переменную для хранения скорости игры
	Vector2i Pixelpos; //Переменная для получения местонахождения мыши
	Vector2f pos; //Переменная для хранения координат указателя мыши
	Clock clock; //Создаем объект класса времени, для задания скорости игры
	int pressedbut = 0; //Переменная для проверки нажатия кнопки мыши
	
	while (window.isOpen()) //Цикл, пока открыто окно, он действует
	{
		time = clock.getElapsedTime().asMicroseconds(); //Измерение времени в микросекундах
		clock.restart(); //Перезагружаем время
		time = time / 150; //Задаем общую скорость игры
		Bullet bullet("bullet.png", p1.getSpritePos().x, p1.getSpritePos().y, p1.getSpriteOrigin(), pos, time);
		Event event; //Создаем объект класса событие

		Pixelpos = Mouse::getPosition(window); //Получение значений местонахождения мыши
		pos = window.mapPixelToCoords(Pixelpos); //Конвертирование в координаты положения мыши
		if (window.pollEvent(event)) //Проверка закрытия окна
		{
			if (event.type == Event::Closed)
				window.close();
		}
		if (Keyboard::isKeyPressed(Keyboard::Escape)) { window.close(); }
		
		if (Mouse::isButtonPressed(Mouse::Button::Left) && pressedbut == 0) //Проверка единичного нажатия на клавишу мыши
		{
			pressedbut = 1;
			bullets1pl.push_back(bullet);
		}

		if (Mouse::isButtonPressed(Mouse::Button::Left) == false) { pressedbut = 0; } // Проверка единичного нажатия на клавишу

		else pressedbut = 1;

		p1.moving(time, pos, window);


//---Вывод на экран------------------
		window.clear(); //Обновление экрана
		getPosForPlayer(p1.getSpritePos().x, p1.getSpritePos().y);
		window.setView(view);
		map.Draw(window); //Вывод и обновление карты
		window.draw(p1.sprite); //Вывод и обновление первого игрока
		window.draw(p2.sprite); //Вывод и обновление второго игрока
		for(int i=0;i<bullets1pl.size();i++) // Вывод и обновление пуль
			window.draw(bullets1pl[i].sprite);

		for (int i = 0; i<bullets1pl.size(); i++)
		{
			bullets1pl[i].update();
			if (bullets1pl[i].getBulletSprPos().x > 960 || bullets1pl[i].getBulletSprPos().y > 1280)
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

	return 0;
}


