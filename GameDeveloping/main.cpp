#include "Header.h" //Подключаем header

using namespace sf; //Убираем использование sf
using namespace std; //Убираем использование std

int main() //Главная функция игры
{
	RenderWindow window(VideoMode(1366,768), "HUYHUY",Style::None); //Инициализируем окно
	window.setVerticalSyncEnabled(true);
	View view2; //Создаем объект класса Камеры
	Player p1("soldier1.png", 500, 500); //Создаем объект класса игрок
	Player p2("soldier1.png", 600, 600);
	vector <Bullet> bullets1pl;
	float time; //Создаем переменную для хранения скорости игры
	Vector2i Pixelpos; //Переменная для получения местонахождения мыши
	Vector2f pos; //Переменная для хранения координат указателя мыши
	float rotation; //Переменная поворачивающая нашего шероя
	float bulletrot;
	float deX = 0; //Переменная служит для поворота героя вокруг своей оси
	float deY = 0; //Переменная служит для поворота героя вокруг своей оси
	Clock clock; //Создаем объект класса времени, для задания скорости игры
	float СurrentFrame = 0; // Хранение текущей анимации персонажа

	Level map; //Создаем объект класса карты
	map.LoadFromFile("map.xml"); //Грузим нашу карту
	int pressedbut = 0;
	Vector2f heropos = p1.getSpritePos(); //Храним местоположение персонажа
	view2.setCenter(heropos.x, heropos.y); //Ставим положение камеры на позиции героя
	view2.setSize(1366, 768); //Ставим размер вида для камеры
	while (window.isOpen()) //Цикл, пока открыто окно, он действует
	{
		
		time = clock.getElapsedTime().asMicroseconds(); //Измерение времени в микросекундах
		clock.restart(); //Перезагружаем время
		time = time / 150; //Задаем общую скорость игры
		Event event; //Создаем объект класса событие
		
		Pixelpos = Mouse::getPosition(window); //Получение значений местонахождения мыши
		pos = window.mapPixelToCoords(Pixelpos); //Конвертирование в координаты положения мыши
		heropos = p1.getSpritePos(); // Хранение положения персонажа
		deX = pos.x - heropos.x; //- p.x;вектор , колинеарный прямой, которая пересекает спрайт и курсор
		deY = pos.y - heropos.y; //- p.y;он же, координата y
		rotation = (atan2(deY, deX)) * 180 / 3.14159265;//получаем угол в радианах и переводим его в градусы
		
		p1.setSpriteRotation(rotation+85);//поворачиваем спрайт на эти градусы
		
		
		if (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}
		
		
//----------------Движение игроков------------------------------
//----------------Движение Первого игрока-----------------------

		if (Keyboard::isKeyPressed(Keyboard::A) && Keyboard::isKeyPressed(Keyboard::W))
		{
			СurrentFrame += 0.002*time; //служит для прохождения по "кадрам". переменная доходит до трех суммируя произведение времени и скорости. изменив 0.005 можно изменить скорость анимации
			if (СurrentFrame > 6) СurrentFrame -= 6; // если пришли к третьему кадру - откидываемся назад.
			p1.setSpriteRect(int(СurrentFrame));
			p1.moveSprite(((-p1.getSpeed())*time)*0.75 , ((-p1.getSpeed())*time)*0.75 ); view2.move(((-p1.getSpeed())*time)*0.75, ((-p1.getSpeed())*time)*0.75);
			
		}
		else if (Keyboard::isKeyPressed(Keyboard::W) && Keyboard::isKeyPressed(Keyboard::D))
		{
			СurrentFrame += 0.002*time; //служит для прохождения по "кадрам". переменная доходит до трех суммируя произведение времени и скорости. изменив 0.005 можно изменить скорость анимации
			if (СurrentFrame > 6) СurrentFrame -= 6; // если пришли к третьему кадру - откидываемся назад.
			p1.setSpriteRect(int(СurrentFrame));
			p1.moveSprite(((p1.getSpeed())*time) *0.75, ((-p1.getSpeed())*time)*0.75 ); view2.move(((p1.getSpeed())*time)*0.75, ((-p1.getSpeed())*time)*0.75);
			
		}
		else if (Keyboard::isKeyPressed(Keyboard::D) && Keyboard::isKeyPressed(Keyboard::S))
		{
			СurrentFrame += 0.002*time; //служит для прохождения по "кадрам". переменная доходит до трех суммируя произведение времени и скорости. изменив 0.005 можно изменить скорость анимации
			if (СurrentFrame > 6) СurrentFrame -= 6; // если пришли к третьему кадру - откидываемся назад.
			p1.setSpriteRect(int(СurrentFrame));
			p1.moveSprite(((p1.getSpeed())*time)*0.75, ((p1.getSpeed())*time)*0.75); view2.move(((p1.getSpeed())*time)*0.75, ((p1.getSpeed())*time)*0.75);
			
		}
		else if (Keyboard::isKeyPressed(Keyboard::S) && Keyboard::isKeyPressed(Keyboard::A))
		{
			СurrentFrame += 0.002*time; //служит для прохождения по "кадрам". переменная доходит до трех суммируя произведение времени и скорости. изменив 0.005 можно изменить скорость анимации
			if (СurrentFrame > 6) СurrentFrame -= 6; // если пришли к третьему кадру - откидываемся назад.
			p1.setSpriteRect(int(СurrentFrame));
			p1.moveSprite(((-p1.getSpeed())*time)*0.75, ((p1.getSpeed())*time)*0.75); 
			view2.move(((-p1.getSpeed())*time)*0.75, ((p1.getSpeed())*time)*0.75);
			
		}
		else if (Keyboard::isKeyPressed(Keyboard::A))
		{
			СurrentFrame += 0.002*time; //служит для прохождения по "кадрам". переменная доходит до трех суммируя произведение времени и скорости. изменив 0.005 можно изменить скорость анимации
			if (СurrentFrame > 6) СurrentFrame -= 6; // если пришли к третьему кадру - откидываемся назад.
			p1.setSpriteRect(int(СurrentFrame));
			p1.moveSprite(((-p1.getSpeed())*time), 0);
			view2.move(((-p1.getSpeed())*time), 0);
		}
		else if (Keyboard::isKeyPressed(Keyboard::W))
		{
			СurrentFrame += 0.002*time; //служит для прохождения по "кадрам". переменная доходит до трех суммируя произведение времени и скорости. изменив 0.005 можно изменить скорость анимации
			if (СurrentFrame > 6) СurrentFrame -= 6; // если пришли к третьему кадру - откидываемся назад.
			p1.setSpriteRect(int(СurrentFrame));
			p1.moveSprite(0, ((-p1.getSpeed())*time));
			view2.move(0, ((-p1.getSpeed())*time));
		}
		else if (Keyboard::isKeyPressed(Keyboard::S))
		{
			
			СurrentFrame += 0.002*time; //служит для прохождения по "кадрам". переменная доходит до трех суммируя произведение времени и скорости. изменив 0.005 можно изменить скорость анимации
			if (СurrentFrame > 6) СurrentFrame -= 6; // если пришли к третьему кадру - откидываемся назад.
			p1.setSpriteRect(int(СurrentFrame));
			p1.moveSprite(0, ((p1.getSpeed())*time));
			view2.move(0, ((p1.getSpeed())*time));
		}
		else if (Keyboard::isKeyPressed(Keyboard::D))
		{
			СurrentFrame += 0.002*time; //служит для прохождения по "кадрам". переменная доходит до трех суммируя произведение времени и скорости. изменив 0.005 можно изменить скорость анимации
			if (СurrentFrame > 6) СurrentFrame -= 6; // если пришли к третьему кадру - откидываемся назад.
			p1.setSpriteRect(int(СurrentFrame));
			p1.moveSprite(((p1.getSpeed())*time), 0);
			view2.move(((p1.getSpeed())*time), 0);
			
		}
		else
		{
			СurrentFrame = 0;
			p1.setSpriteRect(int(СurrentFrame));
		}
//----------Движение второго игрока--------------------------------------

//----------Стрельба игроков---------------------------------------------
//----------Стрельба первого игрока--------------------------------------
		
		if (Mouse::isButtonPressed(Mouse::Button::Left) && pressedbut == 0)
		{
			pressedbut = 1;
			Bullet bullet("bullet.png", p1.getSpritePos().x, p1.getSpritePos().y,p1.getSpriteOrigin(), pos);
			bullets1pl.push_back(bullet);
			
			
		}
		if (Mouse::isButtonPressed(Mouse::Button::Left) == false) { pressedbut = 0; }
		else pressedbut = 1;
		for (int i = 0; i<bullets1pl.size(); i++)
		{ 
			bullets1pl[i].update();
			if (bullets1pl[i].getBulletSprPos().x > 960 || bullets1pl[i].getBulletSprPos().y > 1280) 
			{ 
				bullets1pl.pop_back(); 
			}
			else if (bullets1pl[i].getBulletSprPos().x < 0 || bullets1pl[i].getBulletSprPos().y < 0)
			{
				bullets1pl.pop_back();
			}
		}
//----------Стрельба второго игрока--------------------------------------

//---Вывод на экран------------------
		
		window.clear();

		map.Draw(window);
		window.setView(view2);
		window.draw(p1.sprite);
		window.draw(p2.sprite);
		for(int i=0;i<bullets1pl.size();i++)
			window.draw(bullets1pl[i].sprite);
		window.display();

	}

	return 0;
}
