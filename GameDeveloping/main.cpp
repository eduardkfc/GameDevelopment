#include "Header.h" //Подключаем header

bool startGame() 
{
	int hostChoosed;
	int gamestate = 1;
	int MapsID = 0;

	RenderWindow window(VideoMode(1280, 720), "Reflex Strike", Style::None); //Инициализируем окно
	view.reset(FloatRect(0, 0, 1280, 720)); //Перезагрузка экрана
	window.setVerticalSyncEnabled(true); //Включение вертикальной синхронизации
	//window.setFramerateLimit(60); //Лимит кадров в секунду

	bool pressedBut = false; //Переменная для проверки нажатия кнопки мыши(
	Vector2f p1Start, p2Start;
	//-----------------------------------Для перезарядки способностей-----------------------
	
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
	float p1posX, p1posY;
	float p2posX, p2posY, p2Rotation, mousePos2pX, mousePos2pY;
	MainGame maingame;
	//Color color(255, 0, 0);
	obj = map.GetObjects("solid");
	
	int enemyHealth, myHealth;
	Vector2f MousePos;
	while (window.isOpen()) //Цикл, пока открыто окно, он действует
	{	
		MousePos = window.mapPixelToCoords(Mouse::getPosition(window));
		if (gamestate == 0) { return false; } //Выход из игры
		else if (gamestate == 1) { menu.render(window, gamestate,pressedBut); } //Главное меню
		else if (gamestate == 2) { choosinghost.render(window, gamestate, hostChoosed, socket, listener,pressedBut, myip, enemyip, MapsID, map, obj); } //Выбор хоста
		else if (gamestate == 3) { waitplayers.render(window, gamestate, pressedBut, socket,listener, myip, enemyip,MapsID,map,obj,p1,hostChoosed); } // Ожидание клиента
		else if (gamestate == 4) { waitserver.render(window, gamestate, socket, pressedBut, myip, enemyip,MapsID,map,p1,obj,hostChoosed); } // Ожидание хоста
		else if (gamestate == 6) { helpwindow.render(window, gamestate, pressedBut); } // Окно помощи
		else if (gamestate == 7) { choosemap.render(window, gamestate, pressedBut, MapsID, map, obj); } //Выбор карты для хоста
		else if (gamestate == 8) { connect.render(window, gamestate, pressedBut, enemyip,stringip,socket,hostChoosed); }
		else if (gamestate == 5) { maingame.render(window, p1, p2, pressedBut, hostChoosed, gamestate, socket, enemyip, map,obj,MousePos); }
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


