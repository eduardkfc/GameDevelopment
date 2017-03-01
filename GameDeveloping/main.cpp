#include "Header.h" //Подключаем header

using namespace sf; //Убираем использование sf::
using namespace std; //Убираем использование std::
Vector2i Pixelpos; //Переменная для получения местонахождения мыши
Vector2f pos; //Переменная для хранения координат указателя мыши
int gamestate = 1;
int pressedbut = 0; //Переменная для проверки нажатия кнопки мыши(



void mainmenu(RenderWindow &window)
{
	Texture mainscreen;
	Texture buttonStart;
	Texture buttonSettings;
	Texture buttonExit;
	mainscreen.loadFromFile("mainscreen.jpg");
	buttonStart.loadFromFile("buttons/startgame.jpg");
	buttonSettings.loadFromFile("buttons/settings.jpg");
	buttonExit.loadFromFile("buttons/exit.jpg");
	Sprite mainscreene;
	Sprite butStart;
	Sprite butSettings;
	Sprite butExit;
	mainscreene.setTexture(mainscreen);
	butStart.setTexture(buttonStart);
	butSettings.setTexture(buttonSettings);
	butExit.setTexture(buttonExit);
	butSettings.setPosition(200, 310);
	butStart.setPosition(540, 310);
	butExit.setPosition(880, 310);
	window.clear();
	window.draw(mainscreene);
	window.draw(butStart);
	window.draw(butSettings);
	window.draw(butExit);
	window.display();
}

void methodchoose()
{
	
}
void startedgame(RenderWindow &window)
{
	Level map; //Создаем объект класса карты
	map.LoadFromFile("map.xml"); //Грузим нашу карту
	Player p1("soldier1.png", 500, 500, map, 1); //Создаем объект класса игрок
	Player p2("soldier1.png", 600, 600, map, 2); //Создаем объект класса игрок
	vector <Bullet> bullets1pl; //Вектор пуль
	float time; //Создаем переменную для хранения скорости игры
	Clock clock; //Создаем объект класса времени, для задания скорости игры
	Pixelpos = Mouse::getPosition(window); //Получение значений местонахождения мыши
	pos = window.mapPixelToCoords(Pixelpos); //Конвертирование в координаты положения мыши
	time = clock.getElapsedTime().asMicroseconds(); //Измерение времени в микросекундах
	clock.restart(); //Перезагружаем время
	time = time / 150; //Задаем общую скорость игры
	Bullet bullet("bullet.png", p1.getSpritePos().x, p1.getSpritePos().y, p1.getSpriteOrigin(), pos, time);
	if (Mouse::isButtonPressed(Mouse::Button::Left) && pressedbut == 0) //Проверка единичного нажатия на клавишу мыши
	{
		pressedbut = 1;
		bullets1pl.push_back(bullet);
	}
	p1.moving(time, pos, window);
	window.clear(); //Обновление экрана
	getPosForPlayer(p1.getSpritePos().x, p1.getSpritePos().y);
	window.setView(view);
	map.Draw(window); //Вывод и обновление карты
	window.draw(p1.sprite); //Вывод и обновление первого игрока
	window.draw(p2.sprite); //Вывод и обновление второго игрока
	for (int i = 0; i<bullets1pl.size(); i++) // Вывод и обновление пуль
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

int main() //Главная функция игры
{
	//gamestate = 1 MainMenu
	//gamestate = 2 Choose Host
	//gamestate = 3 Settings
	//gamestate = 4 Start Game
	RenderWindow window(VideoMode(1280,720), "Reflex Strike",Style::None); //Инициализируем окно
	view.reset(FloatRect(0, 0, 1280, 720)); //Перезагрузка экрана
	window.setVerticalSyncEnabled(true); //Включение вертикальной синхронизации
	
	
	
	while (window.isOpen()) //Цикл, пока открыто окно, он действует
	{
		if (gamestate == 1) { mainmenu(window); }
		if (gamestate == 4) { startedgame(window); }
		Pixelpos = Mouse::getPosition(window); //Получение значений местонахождения мыши
		pos = window.mapPixelToCoords(Pixelpos); //Конвертирование в координаты положения мыши
		if (Mouse::isButtonPressed(Mouse::Button::Left))
			if ((740 > pos.x) && (pos.x > 540) && (377 > pos.y) && (pos.y > 310)) { cout << " ti pidor "; gamestate = 4; } //Начало игры
		if (Mouse::isButtonPressed(Mouse::Button::Left))
			if ((400 > pos.x) && (pos.x > 200) && (377 > pos.y) && (pos.y > 310)) { cout << " ti pidor "; } //Настройки
		if (Mouse::isButtonPressed(Mouse::Button::Left))
			if ((1080 > pos.x) && (pos.x > 880) && (377 > pos.y) && (pos.y > 310)) { window.close(); } //Выход из игры
	
		Event event; //Создаем объект класса событие
		if (window.pollEvent(event)) //Проверка закрытия окна
		{
			if (event.type == Event::Closed) window.close();
		}
		if (Keyboard::isKeyPressed(Keyboard::Escape)) { window.close(); }
		if (Mouse::isButtonPressed(Mouse::Button::Left) == false) { pressedbut = 0; } // Проверка единичного нажатия на клавишу
		else pressedbut = 1;
	}
	return 0;
}


