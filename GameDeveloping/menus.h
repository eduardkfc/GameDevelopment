#pragma once
#include "Header.h"

class MainMenu
{
private:
	Texture mainscreen; //фоновое фото
	Sprite menubg; //спрайт фонового фото
	int menuNum; //хранит текущий пункт меню
	Text text, startText, helpText, exitText; //объекты класса текста
	Font font; //шрифт
public:
	MainMenu()
	{
		// Загружаем изображение шрифт и настраиваем весь текст на экране
		mainscreen.loadFromFile("mainscreen.jpg");
		font.loadFromFile("font.ttf");
		text.setFont(font);
		text.setString("REFLEX STRIKE");
		text.setCharacterSize(100);
		text.setPosition(640, 150);
		text.setOrigin(text.getLocalBounds().width / 2, text.getLocalBounds().height / 2);
		text.setOutlineThickness(2);

		startText.setFont(font);
		startText.setString("Start Game");
		startText.setCharacterSize(40);
		startText.setOrigin(startText.getLocalBounds().width / 2, startText.getLocalBounds().height / 2);
		startText.setPosition(640, 360);
		startText.setOutlineThickness(2);

		helpText.setFont(font);
		helpText.setString("Help");
		helpText.setCharacterSize(40);
		helpText.setOrigin(helpText.getLocalBounds().width / 2, helpText.getLocalBounds().height / 2);
		helpText.setPosition(200, 360);
		helpText.setOutlineThickness(2);

		exitText.setFont(font);
		exitText.setString("Exit");
		exitText.setCharacterSize(40);
		exitText.setOrigin(exitText.getLocalBounds().width / 2, exitText.getLocalBounds().height / 2);
		exitText.setPosition(1080, 360);
		exitText.setOutlineThickness(2);
		menubg.setTexture(mainscreen);
	}
	void render(RenderWindow &window,int &gamestate,bool &pressedBut)
	{
		menuNum = 0; //обнуление
		window.clear(); //очищение экрана
		startText.setFillColor(Color::White); //заполнение в белый цвет
		helpText.setFillColor(Color::White);
		exitText.setFillColor(Color::White);
		//переход между игровыми состояниями
		if (startText.getGlobalBounds().contains(Vector2f(window.mapPixelToCoords(Mouse::getPosition(window))))) { startText.setFillColor(Color::Blue); menuNum = 1; }
		if (helpText.getGlobalBounds().contains(Vector2f(window.mapPixelToCoords(Mouse::getPosition(window))))) { helpText.setFillColor(Color::Blue); menuNum = 2; }
		if (exitText.getGlobalBounds().contains(Vector2f(window.mapPixelToCoords(Mouse::getPosition(window))))) { exitText.setFillColor(Color::Blue); menuNum = 3; }
		if (Mouse::isButtonPressed(Mouse::Left) && pressedBut == false)
		{
			pressedBut = true;
			if (menuNum == 1) gamestate = 2;
			if (menuNum == 2) gamestate = 6; 
			if (menuNum == 3) gamestate = 0;
		}
		//Вывод элементов меню
		window.draw(menubg);
		window.draw(startText);
		window.draw(helpText);
		window.draw(exitText);
		window.draw(text);
		window.display();
	}
};

class Help
{
private:
	Texture mainscreen, SSicon, DDicon; //текстуры изображений
	Sprite menubg, SSico, DDico; //спрайты текстур
	bool menuNum; //текущий пункт меню
	Text text, backText, ddText, ssText, mainHelpText; //объекты класса текста
	Font font; //шрифт
public:
	Help()
	{
		// Загружаем изображения шрифт и настраиваем весь текст на экране
		mainscreen.loadFromFile("mainscreen.jpg");
		SSicon.loadFromFile("superspeed.jpg");
		DDicon.loadFromFile("doubledamage.jpg");
		menubg.setTexture(mainscreen);
		SSico.setTexture(SSicon);
		DDico.setTexture(DDicon);

		font.loadFromFile("font.ttf");
		text.setFont(font);
		text.setString("REFLEX STRIKE");
		text.setCharacterSize(100);
		text.setOrigin(text.getLocalBounds().width / 2, text.getLocalBounds().height / 2);
		text.setOutlineThickness(2);
		text.setPosition(640, 150);
		
		SSico.setPosition(170, 510);
		DDico.setPosition(170, 410);

		mainHelpText.setFont(font);
		mainHelpText.setString("   \t\t\t\tUse the WASD for moving your soldier.\n\n  \t\t\t\t\t\t\tUse mouse arrow to aim.\n\n\t\t\t\t\t\tUse left mouse button to Shoot.\n\nUse Q-button to Double Damage. Use E-button to Super Speed");
		mainHelpText.setCharacterSize(27);
		mainHelpText.setOrigin(mainHelpText.getLocalBounds().width / 2, mainHelpText.getLocalBounds().height / 2);
		mainHelpText.setPosition(640, 300);
		mainHelpText.setOutlineThickness(2);

		ddText.setFont(font);
		ddText.setString(" - Makes bullet damage twice. Duration - 5 sec. Cooldown - 7 sec.");
		ddText.setCharacterSize(30);
		ddText.setOrigin(ddText.getLocalBounds().width / 2, ddText.getLocalBounds().height / 2);
		ddText.setPosition(730, 445);
		ddText.setOutlineThickness(2);

		ssText.setFont(font);
		ssText.setString(" - Increase soldier speed +40%. Duration - 2 sec. Cooldown - 4 sec.");
		ssText.setCharacterSize(30);
		ssText.setOrigin(ssText.getLocalBounds().width / 2, ssText.getLocalBounds().height / 2);
		ssText.setPosition(740, 545);
		ssText.setOutlineThickness(2);

		backText.setFont(font);
		backText.setString("Back");
		backText.setCharacterSize(40);
		backText.setOrigin(backText.getLocalBounds().width / 2, backText.getLocalBounds().height / 2);
		backText.setPosition(1150, 650);
		backText.setOutlineThickness(2);
	}
	void render(RenderWindow &window, int &gamestate, bool &pressedBut)
	{
		menuNum = false; // обнуление
		window.clear(); //очищение экрана
		backText.setFillColor(Color::White); //окрашивание кнопки в белый
		//переход между игровыми состояниями
		if (backText.getGlobalBounds().contains(Vector2f(window.mapPixelToCoords(Mouse::getPosition(window))))) { backText.setFillColor(Color::Blue); menuNum = true; }
		if (Mouse::isButtonPressed(Mouse::Left) && pressedBut == false)
		{
			pressedBut = true;
			if (menuNum == true) gamestate = 1;
		}
		//Вывод элементов меню
		window.draw(menubg);
		window.draw(DDico);
		window.draw(SSico);
		window.draw(backText);
		window.draw(text);
		window.draw(ddText);
		window.draw(ssText);
		window.draw(mainHelpText);
		window.display();
	}
};

class ChooseHost
{
private:
	Texture mainscreen; //текстура фонового изображения
	Sprite menubg; // спрайт текстуры
	int menuNum; //текущий пункт меню
	Text text, hostText, clientText, backText; //объекты класса текста
	Font font; //шрифт
public:
	ChooseHost()
	{
		// Загружаем изображение шрифт и настраиваем весь текст на экране
		mainscreen.loadFromFile("mainscreen.jpg");
		menubg.setTexture(mainscreen);
		menuNum = 0;
		font.loadFromFile("font.ttf");

		text.setFont(font);
		text.setString("REFLEX STRIKE");
		text.setCharacterSize(100);
		text.setPosition(640, 150);
		text.setOrigin(text.getLocalBounds().width / 2, text.getLocalBounds().height / 2);
		text.setOutlineThickness(2);

		hostText.setFont(font);
		hostText.setString("Host");
		hostText.setCharacterSize(40);
		hostText.setPosition(640, 300);
		hostText.setOrigin(hostText.getLocalBounds().width / 2, hostText.getLocalBounds().height / 2);
		hostText.setOutlineThickness(2);

		clientText.setFont(font);
		clientText.setString("Client");
		clientText.setCharacterSize(40);
		clientText.setPosition(640, 420);
		clientText.setOrigin(clientText.getLocalBounds().width / 2, clientText.getLocalBounds().height / 2);
		clientText.setOutlineThickness(2);

		backText.setFont(font);
		backText.setString("Back");
		backText.setCharacterSize(40);
		backText.setPosition(1150, 650);
		backText.setOrigin(backText.getLocalBounds().width / 2, backText.getLocalBounds().height / 2);
		backText.setOutlineThickness(2);

	}
	void render(RenderWindow &window, int &gamestate, int &hostChoosed,  bool &pressedBut)
	{
		menuNum = 0; //обнуление переменной
		window.clear(); // очищение экрана
		hostText.setFillColor(Color::White); //окрашивание в белый
		clientText.setFillColor(Color::White);
		backText.setFillColor(Color::White);
		//переход между игровыми состояниями
		if (hostText.getGlobalBounds().contains(Vector2f(window.mapPixelToCoords(Mouse::getPosition(window))))) { hostText.setFillColor(Color::Blue); menuNum = 1; }
		if (clientText.getGlobalBounds().contains(Vector2f(window.mapPixelToCoords(Mouse::getPosition(window))))) { clientText.setFillColor(Color::Blue); menuNum = 2; }
		if (backText.getGlobalBounds().contains(Vector2f(window.mapPixelToCoords(Mouse::getPosition(window))))) { backText.setFillColor(Color::Blue); menuNum = 3; }
		if (Mouse::isButtonPressed(Mouse::Left) && pressedBut == false)
		{
			pressedBut = true;
			if (menuNum == 1) { gamestate = 7; hostChoosed = 1; }
			if (menuNum == 2) { gamestate = 8; hostChoosed = 0; }
			if (menuNum == 3) { gamestate = 1; }
		}
		//Вывод элементов меню
		window.draw(menubg);
		window.draw(hostText);
		window.draw(clientText);
		window.draw(backText);
		window.draw(text);	
		window.display();
	}
};

class ChooseMap
{
private:
	Texture mainscreen; //текстура фонового изображения
	Sprite menubg; //спрайт текстуры
	Text mainText, backText, textMapRoads, textMapVillage; //объекты класса текста
	int menuNum; //текущий пункт меню
	Font font; // шрифт
public:
	ChooseMap()
	{
		// Загружаем изображение шрифт и настраиваем весь текст на экране
		mainscreen.loadFromFile("mainscreen.jpg");
		menubg.setTexture(mainscreen);

		font.loadFromFile("font.ttf");
		mainText.setFont(font);
		mainText.setString("MAP CHOOSING");
		mainText.setCharacterSize(100);
		mainText.setPosition(640, 150);
		mainText.setOrigin(mainText.getLocalBounds().width / 2, mainText.getLocalBounds().height / 2);
		mainText.setOutlineThickness(2);

		textMapRoads.setFont(font);
		textMapRoads.setString("Roads");
		textMapRoads.setCharacterSize(40);
		textMapRoads.setPosition(640, 300);
		textMapRoads.setOrigin(textMapRoads.getLocalBounds().width / 2, textMapRoads.getLocalBounds().height / 2);
		textMapRoads.setOutlineThickness(2);

		textMapVillage.setFont(font);
		textMapVillage.setString("Village");
		textMapVillage.setCharacterSize(40);
		textMapVillage.setPosition(640, 420);
		textMapVillage.setOrigin(textMapVillage.getLocalBounds().width / 2, textMapVillage.getLocalBounds().height / 2);
		textMapVillage.setOutlineThickness(2);

		backText.setFont(font);
		backText.setString("Back");
		backText.setCharacterSize(40);
		backText.setPosition(1150, 650);
		backText.setOrigin(backText.getLocalBounds().width / 2, backText.getLocalBounds().height / 2);
		backText.setOutlineThickness(2);
	}
	void render(RenderWindow &window, int &gamestate, TcpListener &listener, bool &pressedBut, int &MapsID)
	{
		menuNum = 0; //обнуление переменной
		window.clear(); //очищение экрана
		textMapRoads.setFillColor(Color::White); //окрашивание кнопки в белый
		textMapVillage.setFillColor(Color::White);
		backText.setFillColor(Color::White);
		//переход между игровыми состояниями
		if (textMapRoads.getGlobalBounds().contains(Vector2f(window.mapPixelToCoords(Mouse::getPosition(window))))) { textMapRoads.setFillColor(Color::Blue); menuNum = 1; }
		if (textMapVillage.getGlobalBounds().contains(Vector2f(window.mapPixelToCoords(Mouse::getPosition(window))))) { textMapVillage.setFillColor(Color::Blue); menuNum = 2; }
		if (backText.getGlobalBounds().contains(Vector2f(window.mapPixelToCoords(Mouse::getPosition(window))))) { backText.setFillColor(Color::Blue); menuNum = 3; }
		if (Mouse::isButtonPressed(Mouse::Left) && pressedBut == false)
		{
			pressedBut = true;
			//прослушивание порта при выборе карты
			if (menuNum == 1) { listener.listen(55001); gamestate = 3; MapsID = 1; }
			if (menuNum == 2) { listener.listen(55001); gamestate = 3; MapsID = 2; }
			if (menuNum == 3) { gamestate = 1; }
			
		}
		//Вывод элементов меню
		window.draw(menubg);
		window.draw(mainText);
		window.draw(textMapRoads);
		window.draw(textMapVillage);
		window.draw(backText);
		window.display();
	}
};
class ConnectToIp
{
private:
	Texture mainscreen; //текстура фонового изображения
	Sprite menubg; //спрайт текстуры
	Text mainText, backText,textIP, textConnect,wordIP; //объекты класса текста
	int menuNum; //текущий пункт меню
	Font font; // шрифт
	bool pressedbut; //для единичного нажатия на клавиши клавиатуры
public:
	ConnectToIp()
	{
		// Загружаем изображение шрифт и настраиваем весь текст на экране
		mainscreen.loadFromFile("mainscreen.jpg");
		menubg.setTexture(mainscreen);

		font.loadFromFile("font.ttf");
		mainText.setFont(font);
		mainText.setString("TYPE IP ADDRESS");
		mainText.setCharacterSize(100);
		mainText.setPosition(640, 150);
		mainText.setOrigin(mainText.getLocalBounds().width / 2, mainText.getLocalBounds().height / 2);
		mainText.setOutlineThickness(2);

		textIP.setFont(font);
		textIP.setCharacterSize(40);
		textIP.setPosition(300, 300);
		textIP.setOrigin(textIP.getLocalBounds().width / 2, textIP.getLocalBounds().height / 2);
		textIP.setOutlineThickness(2);

		wordIP.setFont(font);
		wordIP.setCharacterSize(40);
		wordIP.setString("IP :");
		wordIP.setPosition(250, 320);
		wordIP.setOrigin(wordIP.getLocalBounds().width / 2, wordIP.getLocalBounds().height / 2);
		wordIP.setOutlineThickness(2);

		textConnect.setFont(font);
		textConnect.setString("Connect");
		textConnect.setCharacterSize(40);
		textConnect.setPosition(640, 450);
		textConnect.setOrigin(textConnect.getLocalBounds().width / 2, textConnect.getLocalBounds().height / 2);
		textConnect.setOutlineThickness(2);

		backText.setFont(font);
		backText.setString("Back");
		backText.setCharacterSize(40);
		backText.setPosition(1150, 650);
		backText.setOrigin(backText.getLocalBounds().width / 2, backText.getLocalBounds().height / 2);
		backText.setOutlineThickness(2);
	}
	void render(RenderWindow &window, int &gamestate, bool &pressedBut,IpAddress &enemyip,string &stringip, TcpSocket &socket,int &hostChoosed)
	{
		menuNum = 0; //обнуление переменной
		window.clear(); //очищение экрана
		textIP.setString(stringip); //задаем объекту класса текста string - строку
		textConnect.setFillColor(Color::White); //окрашивание в белый
		backText.setFillColor(Color::White);
		//переход между игровыми состояниями
		if (textConnect.getGlobalBounds().contains(Vector2f(window.mapPixelToCoords(Mouse::getPosition(window))))) { textConnect.setFillColor(Color::Blue); menuNum = 1; }
		if (backText.getGlobalBounds().contains(Vector2f(window.mapPixelToCoords(Mouse::getPosition(window))))) { backText.setFillColor(Color::Blue); menuNum = 2; }
		if (Mouse::isButtonPressed(Mouse::Left) && pressedBut == false)
		{
			pressedBut = true;
			if (menuNum == 1) 
			{ 
				enemyip = stringip; //строка с айпи адресом дается классу IpAddress
				socket.connect(enemyip, 55001); // подключение к хосту по айпи
				gamestate = 4; //переход к ожиданию
			}
			if (menuNum == 2) { gamestate = 2; }
		}
		//единичный ввод каждого символа для айпи адреса
		if (pressedbut == false)
		{
			if (Keyboard::isKeyPressed(Keyboard::Num0) && pressedbut == false) { pressedbut = true; stringip += "0"; }
			else if (Keyboard::isKeyPressed(Keyboard::Num1) && pressedbut == false) { pressedbut = true; stringip += "1"; }
			else if (Keyboard::isKeyPressed(Keyboard::Num2) && pressedbut == false) { pressedbut = true; stringip += "2"; }
			else if (Keyboard::isKeyPressed(Keyboard::Num3) && pressedbut == false) { pressedbut = true; stringip += "3"; }
			else if (Keyboard::isKeyPressed(Keyboard::Num4) && pressedbut == false) { pressedbut = true; stringip += "4"; }
			else if (Keyboard::isKeyPressed(Keyboard::Num5) && pressedbut == false) { pressedbut = true; stringip += "5"; }
			else if (Keyboard::isKeyPressed(Keyboard::Num6) && pressedbut == false) { pressedbut = true; stringip += "6"; }
			else if (Keyboard::isKeyPressed(Keyboard::Num7) && pressedbut == false) { pressedbut = true; stringip += "7"; }
			else if (Keyboard::isKeyPressed(Keyboard::Num8) && pressedbut == false) { pressedbut = true; stringip += "8"; }
			else if (Keyboard::isKeyPressed(Keyboard::Num9) && pressedbut == false) { pressedbut = true; stringip += "9"; }
			else if (Keyboard::isKeyPressed(Keyboard::Period) && pressedbut == false) { pressedbut = true; stringip += "."; }
			else if (Keyboard::isKeyPressed(Keyboard::BackSpace) && pressedbut == false)
			{
				//если массив больше нуля, то удаляем последний символ
				if (stringip.length() > 0)
				{
					stringip.erase(stringip.size()-1);
					pressedbut = true;
				}
			}
		}
		if (!Keyboard::isKeyPressed(Keyboard::Num0) && !Keyboard::isKeyPressed(Keyboard::Num1) &&
			!Keyboard::isKeyPressed(Keyboard::Num2) && !Keyboard::isKeyPressed(Keyboard::Num3) &&
			!Keyboard::isKeyPressed(Keyboard::Num4) && !Keyboard::isKeyPressed(Keyboard::Num5) &&
			!Keyboard::isKeyPressed(Keyboard::Num6) && !Keyboard::isKeyPressed(Keyboard::Num7) &&
			!Keyboard::isKeyPressed(Keyboard::Num8) && !Keyboard::isKeyPressed(Keyboard::Num9) &&
			!Keyboard::isKeyPressed(Keyboard::Period) && !Keyboard::isKeyPressed(Keyboard::BackSpace))
		{
			pressedbut = false;
		}
		//Вывод элементов меню
		window.draw(menubg);
		window.draw(mainText);
		window.draw(textConnect);
		window.draw(backText);
		window.draw(textIP);
		window.draw(backText);
		window.draw(wordIP);
		window.display();
	}
};
class WaitingForPlayers
{
private:
	Texture mainscreen; //текстура для фонового изображения
	Sprite menubg; //спрайт текстуры
	Text text,mainText,backText,waitText; //объекты класса текста
	Font font; //шрифт
	int menuNum; //текущий пункт меню
	Packet packetoutput; //исходящий пакет для клиента
public:
	WaitingForPlayers()
	{
		// Загружаем изображение шрифт и настраиваем весь текст на экране
		mainscreen.loadFromFile("mainscreen.jpg"); //Загрузка главного меню
		menubg.setTexture(mainscreen);
		font.loadFromFile("font.ttf");
		menuNum = 0;
		text.setFont(font);
		
		mainText.setFont(font);
		mainText.setString("REFLEX STRIKE");
		mainText.setCharacterSize(100);
		mainText.setPosition(640, 150);
		mainText.setOrigin(mainText.getLocalBounds().width / 2, mainText.getLocalBounds().height / 2);
		mainText.setOutlineThickness(2);

		backText.setFont(font);
		backText.setString("Back");
		backText.setCharacterSize(40);
		backText.setPosition(1150, 650);
		backText.setOrigin(backText.getLocalBounds().width / 2, backText.getLocalBounds().height / 2);
		backText.setOutlineThickness(2);

		waitText.setFont(font);
		waitText.setString("Wait connection");
		waitText.setCharacterSize(60);
		waitText.setPosition(640, 360);
		waitText.setOrigin(waitText.getLocalBounds().width / 2, waitText.getLocalBounds().height / 2);
		waitText.setOutlineThickness(2);

		text.setPosition(20, 680);
	}
	void render(RenderWindow &window, int &gamestate, bool &pressedBut, TcpSocket &socket,TcpListener &listener, IpAddress &myip,int &MapsID,Maps &map,vector <Object> &obj,Player &p1,int &hostChoosed)
	{
		window.clear(); //очищение экрана
		text.setString("Your IP Address: " + myip.toString()); //вывод айпи адреса на экран хоста
		backText.setFillColor(Color::White); //окрашивание в белый

		menuNum = 0; //обнуление переменной
		//переход между игровыми состояниями
		if (backText.getGlobalBounds().contains(Vector2f(window.mapPixelToCoords(Mouse::getPosition(window))))) { backText.setFillColor(Color::Blue); menuNum = 1; }
		if (Mouse::isButtonPressed(Mouse::Left) && pressedBut == false)
		{
			pressedBut = true;
			if (menuNum == 1) { listener.close(); gamestate = 2;  }
		}
		packetoutput.clear(); //очищаем пакет перед отправкой
		
		packetoutput << MapsID; //заполняем кодом карты
		//ждем подключения клиента
		if (Socket::Done == listener.accept(socket))
		{
			socket.send(packetoutput); //отправляем клиенту
			//карта Roads
			if (MapsID == 1) 
			{ 
				map.LoadFromFile("road.xml"); 
				obj = map.GetObjects("solid"); 
				p1.startPosition(hostChoosed, MapsID);
				gamestate = 5;
			}
			//карта Village
			else if (MapsID == 2) 
			{ 
				map.LoadFromFile("village.xml"); 
				obj = map.GetObjects("solid"); 
				p1.startPosition(hostChoosed, MapsID);
				gamestate = 5;
			}
			
		}
		//Вывод элементов меню
		window.draw(menubg);
		window.draw(waitText);
		window.draw(backText);
		window.draw(text);
		window.draw(mainText);
		window.display();
	}
};

class WaitingForServer
{
private:
	Texture mainscreen; //текстура фонового изображения
	Sprite menubg; //спрайт текстуры
	int menuNum; //текущий пункт меню
	Packet packetinput; //входящий пакет от хоста
	Text mainText, backText, waitText; //объекты класса текста
	Font font; //шрифт
public:
	WaitingForServer()
	{
		// Загружаем изображение шрифт и настраиваем весь текст на экране
		mainscreen.loadFromFile("mainscreen.jpg");
		menubg.setTexture(mainscreen);
		font.loadFromFile("font.ttf");
		menuNum = 0;
		mainText.setFont(font);
		mainText.setString("REFLEX STRIKE");
		mainText.setCharacterSize(100);
		mainText.setPosition(640, 150);
		mainText.setOrigin(mainText.getLocalBounds().width / 2, mainText.getLocalBounds().height / 2);
		mainText.setOutlineThickness(2);

		backText.setFont(font);
		backText.setString("Back");
		backText.setCharacterSize(40);
		backText.setPosition(1150, 650);
		backText.setOrigin(backText.getLocalBounds().width / 2, backText.getLocalBounds().height / 2);
		backText.setOutlineThickness(2);

		waitText.setFont(font);
		waitText.setString("Wait connection");
		waitText.setCharacterSize(60);
		waitText.setPosition(640, 360);
		waitText.setOrigin(waitText.getLocalBounds().width / 2, waitText.getLocalBounds().height / 2);
		waitText.setOutlineThickness(2);
	}
	void render(RenderWindow &window, int &gamestate,TcpSocket &socket, bool &pressedBut, IpAddress &enemyip,int &MapsID,Maps &map,Player &p1,vector <Object> &obj,int &hostChoosed)
	{
		window.clear(); //очищение экрана
		backText.setFillColor(Color::White); //окрашивание в белый
		menuNum = 0; //обнуление переменной
		//переход между игровыми состояниями
		if (backText.getGlobalBounds().contains(Vector2f(window.mapPixelToCoords(Mouse::getPosition(window))))) { backText.setFillColor(Color::Blue); menuNum = 1; }
		if (Mouse::isButtonPressed(Mouse::Left) && pressedBut == false)
		{
			pressedBut = true;
			if (menuNum == 1) { socket.disconnect(); gamestate = 2; MapsID = 0; }
		}

		packetinput.clear(); //очищение пакеты перед приемом
		//ожидание подключения хоста
		if (Socket::Done == socket.connect(enemyip, 55001))
		{
			//прием пакета
			if (!socket.receive(packetinput))
			{
				packetinput >> MapsID; //распаковка
				if (MapsID == 1)
				{
					gamestate = 5; //начало игры
					map.LoadFromFile("road.xml");
					obj = map.GetObjects("solid");
					p1.startPosition(hostChoosed, MapsID);
				}
				else if (MapsID == 2)
				{
					gamestate = 5; //начало игры
					map.LoadFromFile("village.xml");
					obj = map.GetObjects("solid");
					p1.startPosition(hostChoosed, MapsID);
				}
			}
		}
		//Вывод элементов меню
		window.draw(menubg);
		window.draw(mainText);
		window.draw(waitText);
		window.draw(backText);
		window.display();
	}
};