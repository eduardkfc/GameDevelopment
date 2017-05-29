#pragma once
#include "Header.h"

class MainMenu
{
private:
	Texture mainscreen;
	Sprite menubg;
	int menuNum;
	bool isMenu;
	Text text, startText, helpText, exitText;
	Font font;
public:
	MainMenu()
	{
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
		
		menuNum = 0;
		
	}
	void render(RenderWindow &window,int &gamestate,bool &pressedBut)
	{
		menuNum = 0;
		window.clear();
		startText.setFillColor(Color::White);
		helpText.setFillColor(Color::White);
		exitText.setFillColor(Color::White);
		if (startText.getGlobalBounds().contains(Vector2f(window.mapPixelToCoords(Mouse::getPosition(window))))) { startText.setFillColor(Color::Blue); menuNum = 1; }
		if (helpText.getGlobalBounds().contains(Vector2f(window.mapPixelToCoords(Mouse::getPosition(window))))) { helpText.setFillColor(Color::Blue); menuNum = 2; }
		if (exitText.getGlobalBounds().contains(Vector2f(window.mapPixelToCoords(Mouse::getPosition(window))))) { exitText.setFillColor(Color::Blue); menuNum = 3; }
		if (Mouse::isButtonPressed(Mouse::Button::Left) && pressedBut == false)
		{
			pressedBut = true;
			if (menuNum == 1) gamestate = 2;
			if (menuNum == 2) gamestate = 6; 
			if (menuNum == 3) gamestate = 0;
		}
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
	Texture mainscreen, SSicon, DDicon;
	Sprite menubg, SSico, DDico;
	bool menuNum;
	bool isMenu;
	Text text, backText, ddText, ssText, mainHelpText;
	Font font;
public:
	Help()
	{
		mainscreen.loadFromFile("mainscreen.jpg");
		SSicon.loadFromFile("images/superspeed.jpg");
		DDicon.loadFromFile("images/doubledamage.jpg");
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
		
		menuNum = false;
		SSico.setPosition(200, 510);
		DDico.setPosition(200, 410);

		mainHelpText.setFont(font);
		mainHelpText.setString("   \t\t\t\tUse the WASD for moving your soldier.\n  \t\t\t\t\t\t\tUse mouse arrow to aim.\n\t\t\t\t\t\tUse left mouse button to Shoot.\nUse Q-button to Double Damage. Use E-button to Super Speed");
		mainHelpText.setCharacterSize(40);
		mainHelpText.setOrigin(mainHelpText.getLocalBounds().width / 2, mainHelpText.getLocalBounds().height / 2);
		mainHelpText.setPosition(640, 300);
		mainHelpText.setOutlineThickness(2);

		ddText.setFont(font);
		ddText.setString(" - Makes bullet damage twice. Duration - 5 sec. Cooldown - 7 sec.");
		ddText.setCharacterSize(30);
		ddText.setOrigin(ddText.getLocalBounds().width / 2, ddText.getLocalBounds().height / 2);
		ddText.setPosition(760, 445);
		ddText.setOutlineThickness(2);

		ssText.setFont(font);
		ssText.setString(" - Increase soldier speed +40%. Duration - 2 sec. Cooldown - 4 sec.");
		ssText.setCharacterSize(30);
		ssText.setOrigin(ssText.getLocalBounds().width / 2, ssText.getLocalBounds().height / 2);
		ssText.setPosition(770, 545);
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
		menuNum = 0;
		window.clear();
		backText.setFillColor(Color::White);

		if (backText.getGlobalBounds().contains(Vector2f(window.mapPixelToCoords(Mouse::getPosition(window))))) { backText.setFillColor(Color::Blue); menuNum = true; }
		if (Mouse::isButtonPressed(Mouse::Button::Left) && pressedBut == false)
		{
			pressedBut = true;
			if (menuNum == true) gamestate = 1;
		}
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
	Texture mainscreen;
	Sprite menubg;

	int menuNum = 0;
	bool isMenu;
	Text text, hostText, clientText, backText, offlineText, offlineTextVillage;
	Font font;
public:
	ChooseHost()
	{
		mainscreen.loadFromFile("mainscreen.jpg");
		menubg.setTexture(mainscreen);
		hostText.setPosition(540, 250);
		clientText.setPosition(540, 450);
		backText.setPosition(1000, 580);
		offlineText.setPosition(1006, 660);
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

		offlineText.setFont(font);
		offlineText.setString("Offline Roads");
		offlineText.setCharacterSize(40);
		offlineText.setPosition(640, 540);
		offlineText.setOrigin(offlineText.getLocalBounds().width / 2, offlineText.getLocalBounds().height / 2);
		offlineText.setOutlineThickness(2);

		offlineTextVillage.setFont(font);
		offlineTextVillage.setString("Offline Village");
		offlineTextVillage.setCharacterSize(40);
		offlineTextVillage.setPosition(640, 660);
		offlineTextVillage.setOrigin(offlineTextVillage.getLocalBounds().width / 2, offlineTextVillage.getLocalBounds().height / 2);
		offlineTextVillage.setOutlineThickness(2);
	}
	void render(RenderWindow &window, int &gamestate, int &hostChoosed, UdpSocket &socket, bool &pressedBut, IpAddress &myip, IpAddress &enemyip, int &MapsID, Maps &map, vector <Object> &obj)
	{
		menuNum = 0;
		window.clear();
		hostText.setFillColor(Color::White);
		clientText.setFillColor(Color::White);
		backText.setFillColor(Color::White);
		offlineText.setFillColor(Color::White);
		offlineTextVillage.setFillColor(Color::White);
		if (hostText.getGlobalBounds().contains(Vector2f(window.mapPixelToCoords(Mouse::getPosition(window))))) { hostText.setFillColor(Color::Blue); menuNum = 1; }
		if (clientText.getGlobalBounds().contains(Vector2f(window.mapPixelToCoords(Mouse::getPosition(window))))) { clientText.setFillColor(Color::Blue); menuNum = 2; }
		if (backText.getGlobalBounds().contains(Vector2f(window.mapPixelToCoords(Mouse::getPosition(window))))) { backText.setFillColor(Color::Blue); menuNum = 3; }
		if (offlineText.getGlobalBounds().contains(Vector2f(window.mapPixelToCoords(Mouse::getPosition(window))))) { offlineText.setFillColor(Color::Blue); menuNum = 4; }
		if (offlineTextVillage.getGlobalBounds().contains(Vector2f(window.mapPixelToCoords(Mouse::getPosition(window))))) { offlineTextVillage.setFillColor(Color::Blue); menuNum = 5; }
		if (Mouse::isButtonPressed(Mouse::Button::Left) && pressedBut == false)
		{
			pressedBut = true;
			if (menuNum == 1) { cout << "HOST PICKED"; socket.bind(55001, myip); gamestate = 7; hostChoosed = 1; }
			if (menuNum == 2) { cout << "CLIENT PICKED"; socket.bind(55002, myip); gamestate = 8; hostChoosed = 0; }
			if (menuNum == 3) { cout << "GOING BACK"; gamestate = 1; }
			if (menuNum == 4) { cout << "OFFLINE TEST ROADS"; MapsID = 1; gamestate = 5; }
			if (menuNum == 5) { cout << "OFFLINE TEST VILLAGE"; MapsID = 2; gamestate = 5; }
			if (MapsID == 1) { map.LoadFromFile("road.xml"); obj = map.GetObjects("solid"); }
			if (MapsID == 2) { map.LoadFromFile("village.xml"); obj = map.GetObjects("solid"); }
		}
		
		window.draw(menubg);
		window.draw(hostText);
		window.draw(clientText);
		window.draw(offlineText);
		window.draw(backText);
		window.draw(text);
		window.draw(offlineTextVillage);
		window.display();
	}
};

class ChooseMap
{
private:
	Texture mainscreen;
	Sprite menubg;
	Text mainText, backText, textMapRoads, textMapVillage;
	int menuNum;
	bool isMenu;
	Font font;
public:
	ChooseMap()
	{
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
	void render(RenderWindow &window, int &gamestate, bool &pressedBut, int &MapsID, Maps &map, vector <Object> &obj)
	{
		menuNum = 0;
		window.clear();
		textMapRoads.setFillColor(Color::White);
		textMapVillage.setFillColor(Color::White);
		backText.setFillColor(Color::White);
		if (textMapRoads.getGlobalBounds().contains(Vector2f(window.mapPixelToCoords(Mouse::getPosition(window))))) { textMapRoads.setFillColor(Color::Blue); menuNum = 1; }
		if (textMapVillage.getGlobalBounds().contains(Vector2f(window.mapPixelToCoords(Mouse::getPosition(window))))) { textMapVillage.setFillColor(Color::Blue); menuNum = 2; }
		if (backText.getGlobalBounds().contains(Vector2f(window.mapPixelToCoords(Mouse::getPosition(window))))) { backText.setFillColor(Color::Blue); menuNum = 3; }
		if (Mouse::isButtonPressed(Mouse::Button::Left) && pressedBut == false)
		{
			pressedBut = true;
			if (menuNum == 1) { cout << "ROADS"; gamestate = 3; MapsID = 1; }
			if (menuNum == 2) { cout << "VILLAGE"; gamestate = 3; MapsID = 2; }
			if (menuNum == 3) { cout << "GOING BACK"; gamestate = 1; }
			if (MapsID == 1) { map.LoadFromFile("road.xml"); obj = map.GetObjects("solid"); }
			if (MapsID == 2) { map.LoadFromFile("village.xml"); obj = map.GetObjects("solid"); }
		}

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
	Texture mainscreen;
	Sprite menubg;
	Text mainText, backText,textIP, textConnect,wordIP;
	int menuNum;
	bool isMenu;
	Font font;
	bool pressedbut;
public:
	ConnectToIp()
	{
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
	void render(RenderWindow &window, int &gamestate, bool &pressedBut,IpAddress &enemyip,string &stringip)
	{
		menuNum = 0;
		window.clear();
		textIP.setString(stringip);
		textConnect.setFillColor(Color::White);
		backText.setFillColor(Color::White);
		if (textConnect.getGlobalBounds().contains(Vector2f(window.mapPixelToCoords(Mouse::getPosition(window))))) { textConnect.setFillColor(Color::Blue); menuNum = 1; }
		if (backText.getGlobalBounds().contains(Vector2f(window.mapPixelToCoords(Mouse::getPosition(window))))) { backText.setFillColor(Color::Blue); menuNum = 2; }
		if (Mouse::isButtonPressed(Mouse::Button::Left) && pressedBut == false)
		{
			pressedBut = true;
			if (menuNum == 1) { cout << "CONNECT"; enemyip = stringip; gamestate = 4; }
			if (menuNum == 2) { cout << "GOING BACK"; gamestate = 2; }
		}
		
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
				if (stringip.length() > 0)
					stringip.pop_back(); pressedbut = true;
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
		cout << enemyip << endl;
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
	Texture mainscreen;
	Sprite menubg;
	Text text,mainText,backText,waitText;
	Font font;
	int menuNum = 0;
	Packet packetinput;
	Packet packetoutput;
	int inputcode;
	int outputcode;
	unsigned short port;
public:
	WaitingForPlayers()
	{
		mainscreen.loadFromFile("mainscreen.jpg"); //Загрузка главного меню
		font.loadFromFile("font.ttf");
		text.setFont(font);
		menubg.setTexture(mainscreen);
		port = 55002; //Порт для отправки данных клиенту
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
	void render(RenderWindow &window, int &gamestate, bool &pressedBut, UdpSocket &socket,IpAddress &myip,IpAddress &enemyip,int &MapsID)
	{
		window.clear();
		text.setString("Your IP Address: " + myip.toString());
		backText.setFillColor(Color::White);

		menuNum = 0;
		if (backText.getGlobalBounds().contains(Vector2f(window.mapPixelToCoords(Mouse::getPosition(window))))) { backText.setFillColor(Color::Blue); menuNum = 1; }
		if (Mouse::isButtonPressed(Mouse::Button::Left) && pressedBut == false)
		{
			pressedBut = true;
			if (menuNum == 1) { cout << "BACK TO MAINMENU"; socket.unbind(); gamestate = 2;  }
		}
		outputcode = 1;
		packetinput.clear();
		packetoutput.clear();
		packetoutput << outputcode << MapsID;
		if (socket.receive(packetinput, enemyip, port)==Socket::Status::Done) 
		{ 
			packetinput >> inputcode;
			cout << "Received: " << inputcode << endl;
			if (inputcode == 2) { gamestate = 5; }
		}
		socket.send(packetoutput, enemyip, port);
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
	Texture mainscreen;
	Sprite menubg;
	int menuNum = 0;
	Packet packetinput;
	Packet packetoutput;
	int inputcode;
	int outputcode;
	unsigned short port;
	Text mainText, backText, waitText;
	Font font;
public:
	WaitingForServer()
	{
		port = 55001;
		mainscreen.loadFromFile("mainscreen.jpg");
		menubg.setTexture(mainscreen);
		font.loadFromFile("font.ttf");

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
	void render(RenderWindow &window, int &gamestate,UdpSocket &socket, bool &pressedBut, IpAddress &myip, IpAddress &enemyip,int &MapsID,Maps &map)
	{
		window.clear();
		backText.setFillColor(Color::White);
		menuNum = 0;
		if (backText.getGlobalBounds().contains(Vector2f(window.mapPixelToCoords(Mouse::getPosition(window))))) { backText.setFillColor(Color::Blue); menuNum = 1; }
		if (Mouse::isButtonPressed(Mouse::Button::Left) && pressedBut == false)
		{
			pressedBut = true;
			if (menuNum == 1) { cout << "BACK TO MAINMENU"; socket.unbind(); gamestate = 2; }
		}
		packetoutput.clear();
		outputcode = 2;
		packetoutput << outputcode;
		packetinput.clear();
		socket.send(packetoutput, enemyip, port);
		if (socket.receive(packetinput, enemyip, port))
		{
			packetinput >> inputcode >> MapsID;
			cout << "Received: " << inputcode << endl;
			if (inputcode == 1) { gamestate = 5; }
		}
		if (MapsID == 1) { map.LoadFromFile("road.xml"); }
		else if (MapsID == 2) { map.LoadFromFile("village.xml"); }
		window.draw(menubg);
		window.draw(mainText);
		window.draw(waitText);
		window.draw(backText);
		window.display();
	}
};