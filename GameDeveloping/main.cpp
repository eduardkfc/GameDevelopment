#include "Header.h" //Подключаем header

bool startGame() 
{
	int hostChoosed; //кто выбрал хоста
	int gamestate = 1; //хранение состояние приложения
	int MapsID = 0; //код карты

	RenderWindow window(VideoMode(1280, 720), "Reflex Strike", Style::Close); //Инициализируем окно
	view.reset(FloatRect(0, 0, 1280, 720)); //Перезагрузка экрана
	window.setVerticalSyncEnabled(true); //Включение вертикальной синхронизации
	window.setActive(true); //активное окно
	Event events; //событий над окном
	bool pressedBut = false; //Переменная для проверки нажатия кнопки мыши(
	Vector2f p1Start, p2Start; //стартовые позиции
	Player p1(p1Start); //Создаем объект класса игрок
	Player p2(p2Start); //Создаем объект класса игрок
	TcpSocket socket; //сокет протокола тср для обмена данными
	TcpListener listener; //прослушиватель портов
	socket.setBlocking(false); //блокировка выключена
	listener.setBlocking(false); //блокировка выключена
	string stringip; //строка содержащая айпи хоста
	IpAddress myip = IpAddress::getLocalAddress(); //ваш айпи адрес
	IpAddress enemyip(stringip); //хранит адрес хоста
	Maps map; //содержит карту
	vector <Object> obj; //содержит объекты карты
	MainMenu menu; //объект класса главное меню
	ChooseHost choosinghost; //выбор хоста или клиента
	WaitingForPlayers waitplayers; //ожидание клиента
	WaitingForServer waitserver; //ожидание сервера
	Help helpwindow; //окно помощи
	ChooseMap choosemap; // выбор карты
	ConnectToIp connect; //подключение по айпи адресу
	GameLoop gameloop; //основной цикл игры
	Vector2f MousePos; //хранит позицию мыши на экране
	while (window.isOpen()) //Цикл, пока открыто окно, он действует
	{	
		if (window.pollEvent(events))
		{
			if (events.type == Event::Closed) //если окно закрыто
				gamestate = 0;
			if (events.type == Event::MouseButtonPressed) //если нажато на свернутое окно
				window.requestFocus(); //запрос фокуса
		}
		MousePos = window.mapPixelToCoords(Mouse::getPosition(window));
		if (gamestate == 0) { return false; } //Выход из игры
		else if (gamestate == 1) { menu.render(window, gamestate,pressedBut); } //Главное меню
		else if (gamestate == 2) { choosinghost.render(window, gamestate, hostChoosed,pressedBut); } //Выбор хоста
		else if (gamestate == 3) { waitplayers.render(window, gamestate, pressedBut, socket,listener, myip,MapsID,map,obj,p1,hostChoosed); } // Ожидание клиента
		else if (gamestate == 4) { waitserver.render(window, gamestate, socket, pressedBut, enemyip,MapsID,map,p1,obj,hostChoosed); } // Ожидание хоста
		else if (gamestate == 6) { helpwindow.render(window, gamestate, pressedBut); } // Окно помощи
		else if (gamestate == 7) { choosemap.render(window, gamestate, listener, pressedBut, MapsID); } //Выбор карты для хоста
		else if (gamestate == 8) { connect.render(window, gamestate, pressedBut, enemyip,stringip,socket,hostChoosed); } //подключение по айпи адресу
		else if (gamestate == 5) { gameloop.render(window, p1, p2, pressedBut, hostChoosed, gamestate, socket, map, obj, MousePos,events); } //основн
		else if (gamestate == 9) { return true; } // Рестарт игры
		if (!Mouse::isButtonPressed(Mouse::Left)) // Проверка на единичное нажатие клавиши
			pressedBut = false;
	}
}

void gameRunning() 
{
	if (startGame()) { gameRunning(); } //если возвращается true - перезагрузка, false - конец
}

int main() //Главная функция игры
{
	gameRunning();
	return 0;
}


