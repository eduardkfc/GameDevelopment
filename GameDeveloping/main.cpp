#include "Header.h" //Подключаем header

bool startGame() 
{
	int hostChoosed;
	int gamestate = 1;
	int levelID;

	RenderWindow window(VideoMode(1280, 720), "Reflex Strike", Style::None); //Инициализируем окно
	view.reset(FloatRect(0, 0, 1280, 720)); //Перезагрузка экрана
	window.setVerticalSyncEnabled(true); //Включение вертикальной синхронизации
	window.setFramerateLimit(60); //Лимит кадров в секунду

	bool pressedBut = false; //Переменная для проверки нажатия кнопки мыши(
	bool gameLife = true;
	//-----------------------------------Для перезарядки способностей-----------------------
	
	Player p1(500, 500); //Создаем объект класса игрок
	Player p2(600, 600); //Создаем объект класса игрок
	UdpSocket socket;
	socket.setBlocking(false);
	IpAddress myip = IpAddress::getLocalAddress();
	IpAddress enemyip("192.168.43.232");
	

	MainMenu menu;
	ChooseHost choosinghost;
	WaitingForPlayers waitplayers;
	WaitingForServer waitserver;
	Help helpwindow;
	ChooseMap choosemap;
	MainGame maingame(levelID);
	//Color color(255, 0, 0);
	
	
	float p2posX, p2posY, p2Rotation, mousePos2pX,mousePos2pY;
	int enemyHealth, myHealth;

	while (window.isOpen()) //Цикл, пока открыто окно, он действует
	{	
		if (gamestate == 0) { return false; }
		else if (gamestate == 1) { menu.render(window, gamestate,pressedBut); }
		else if (gamestate == 2) { choosinghost.render(window, gamestate, hostChoosed, socket, pressedBut, myip, enemyip); }
		else if (gamestate == 3) { waitplayers.render(window, gamestate, pressedBut, socket, myip, enemyip); }
		else if (gamestate == 4) { waitserver.render(window, gamestate, socket, pressedBut, myip, enemyip); }
		else if (gamestate == 6) { helpwindow.render(window, gamestate, pressedBut); }
		else if (gamestate == 7) { choosemap.render(window, gamestate, pressedBut,levelID); }
		else if (gamestate == 5) { maingame.render(window, p1, p2, pressedBut, hostChoosed, gamestate, socket, enemyip); }
		if (!Mouse::isButtonPressed(Mouse::Button::Left)) // Проверка на единичное нажатие клавиши
			pressedBut = false;
		if (gameLife == false) { return false; }
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


