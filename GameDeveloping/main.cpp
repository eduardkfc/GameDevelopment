#include "Header.h" //Подключаем header

using namespace sf; //Убираем использование sf::
using namespace std; //Убираем использование std::

int main() //Главная функция игры
{
	RenderWindow window(VideoMode(1366,768), "HUYHUY",Style::None); //Инициализируем окно
	window.setVerticalSyncEnabled(true); //Включение вертикальной синхронизации
	View view2; //Создаем объект класса Камеры
	Player p1("soldier1.png", 500, 500,1); //Создаем объект класса игрок
	Player p2("soldier1.png", 600, 600,2); //Создаем объект класса игрок
	vector <Bullet> bullets1pl; //Вектор пуль
	float time; //Создаем переменную для хранения скорости игры
	Vector2i Pixelpos; //Переменная для получения местонахождения мыши
	Vector2f pos; //Переменная для хранения координат указателя мыши

	float bulletrot; //Переменная поворачивающая нашу пулю
	Clock clock; //Создаем объект класса времени, для задания скорости игры

	Level map; //Создаем объект класса карты
	map.LoadFromFile("map.xml"); //Грузим нашу карту
	int pressedbut = 0; //Переменная для проверки нажатия кнопки мыши
	Vector2f heropos;
	view2.setSize(1366, 768); //Ставим размер вида для камеры
	while (window.isOpen()) //Цикл, пока открыто окно, он действует
	{
		
		time = clock.getElapsedTime().asMicroseconds(); //Измерение времени в микросекундах
		clock.restart(); //Перезагружаем время
		time = time / 150; //Задаем общую скорость игры
		Bullet bullet("bullet.png", p1.getSpritePos().x, p1.getSpritePos().y, p1.getSpriteOrigin(), pos, time);
		Event event; //Создаем объект класса событие
		
		Pixelpos = Mouse::getPosition(window); //Получение значений местонахождения мыши
		pos = window.mapPixelToCoords(Pixelpos); //Конвертирование в координаты положения мыши
		heropos = p1.getSpritePos(); // Хранение положения персонажа
		view2.setCenter(heropos.x, heropos.y); //Ставим положение камеры на позиции героя
		
		
		if (window.pollEvent(event)) //Проверка закрытия окна
		{
			if (event.type == Event::Closed)
				window.close();
		}
		
		
//----------------Движение игроков------------------------------
//----------------Движение Первого игрока-----------------------
		
		p1.moving(time,pos);
//----------Движение второго игрока--------------------------------------

//----------Стрельба игроков---------------------------------------------
//----------Стрельба первого игрока--------------------------------------
		
		if (Mouse::isButtonPressed(Mouse::Button::Left) && pressedbut == 0)
		{
			pressedbut = 1;
			
			bullets1pl.push_back(bullet);
			
			
		}
		if (Mouse::isButtonPressed(Mouse::Button::Left) == false) { pressedbut = 0; }
		else pressedbut = 1;
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
//----------Стрельба второго игрока--------------------------------------

//---Вывод на экран------------------
		
		window.clear(); //Обновление экрана
		map.Draw(window); //Вывод и обновление карты
		window.setView(view2); // Вывод и обновление камеры вида
		window.draw(p1.sprite); //Вывод и обновление первого игрока
		window.draw(p2.sprite); //Вывод и обновление второго игрока
		for(int i=0;i<bullets1pl.size();i++) // Вывод и обновление пуль
			window.draw(bullets1pl[i].sprite);
		window.display(); //Инициализация дисплея

	}

	return 0;
}
