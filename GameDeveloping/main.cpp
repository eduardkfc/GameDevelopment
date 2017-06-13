#include "Header.h" //Подключаем header

bool startGame() 
{
	int hostChoosed;
	int gamestate = 1;
	int MapsID = 0;

	RenderWindow window(VideoMode(1280, 720), "Reflex Strike", Style::Close); //Инициализируем окно
	view.reset(FloatRect(0, 0, 1280, 720)); //Перезагрузка экрана
	window.setVerticalSyncEnabled(true); //Включение вертикальной синхронизации
	window.setActive(true);
	Event events; 
	bool pressedBut = false; //Переменная для проверки нажатия кнопки мыши(
	Vector2f p1Start, p2Start;
	Player p1(p1Start); //Создаем объект класса игрок
	Player p2(p2Start); //Создаем объект класса игрок
	TcpSocket socket;
	TcpListener listener;
	socket.setBlocking(false);
	listener.setBlocking(false);
	string stringip;
	IpAddress myip = IpAddress::getLocalAddress();
	IpAddress enemyip(stringip);
	Maps map;
	vector <Object> obj;
	MainMenu menu;
	ChooseHost choosinghost;
	WaitingForPlayers waitplayers;
	WaitingForServer waitserver;
	Help helpwindow;
	ChooseMap choosemap;
	ConnectToIp connect;
	GameLoop gameloop;
	Vector2f MousePos;
	while (window.isOpen()) //Цикл, пока открыто окно, он действует
	{	
		if (window.pollEvent(events))
		{
			if (events.type == Event::Closed)
				gamestate = 0;
			if (events.type == Event::MouseButtonPressed) window.requestFocus();
		}
		MousePos = window.mapPixelToCoords(Mouse::getPosition(window));
		if (gamestate == 0) { return false; } //Выход из игры
		else if (gamestate == 1) { menu.render(window, gamestate,pressedBut); } //Главное меню
		else if (gamestate == 2) { choosinghost.render(window, gamestate, hostChoosed,pressedBut); } //Выбор хоста
		else if (gamestate == 3) { waitplayers.render(window, gamestate, pressedBut, socket,listener, myip,MapsID,map,obj,p1,hostChoosed); } // Ожидание клиента
		else if (gamestate == 4) { waitserver.render(window, gamestate, socket, pressedBut, enemyip,MapsID,map,p1,obj,hostChoosed); } // Ожидание хоста
		else if (gamestate == 6) { helpwindow.render(window, gamestate, pressedBut); } // Окно помощи
		else if (gamestate == 7) { choosemap.render(window, gamestate, listener, pressedBut, MapsID); } //Выбор карты для хоста
		else if (gamestate == 8) { connect.render(window, gamestate, pressedBut, enemyip,stringip,socket,hostChoosed); }
		else if (gamestate == 5) { gameloop.render(window, p1, p2, pressedBut, hostChoosed, gamestate, socket, map, obj, MousePos); }
		else if (gamestate == 9) { return true; } // Рестарт игры
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


