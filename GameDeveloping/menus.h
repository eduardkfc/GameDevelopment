#pragma once
#include "Header.h"

class MainMenu
{
private:
	Texture mainscreen, buttonStart, buttonSettings, buttonExit;
	Sprite menubg, menu1, menu2, menu3;
	int menuNum;
	bool isMenu;
public:
	MainMenu()
	{
		mainscreen.loadFromFile("mainscreen.jpg");
		buttonStart.loadFromFile("buttons/startgame.jpg");
		buttonSettings.loadFromFile("buttons/settings.jpg");
		buttonExit.loadFromFile("buttons/exit.jpg");
		menubg.setTexture(mainscreen);
		menu1.setTexture(buttonStart);
		menu2.setTexture(buttonSettings);
		menu3.setTexture(buttonExit);
		
		menuNum = 0;
		menu1.setPosition(540, 310);
		menu2.setPosition(200, 310);
		menu3.setPosition(880, 310);
		
	}
	void render(RenderWindow &window,int &gamestate,bool &pressedBut)
	{
		menuNum = 0;
		window.clear();
		menu1.setColor(Color::White);
		menu2.setColor(Color::White);
		menu3.setColor(Color::White);
		if (IntRect(540, 310, 200, 66).contains(Mouse::getPosition(window))) { menu1.setColor(Color::Blue); menuNum = 1; }
		if (IntRect(200, 310, 200, 66).contains(Mouse::getPosition(window))) { menu2.setColor(Color::Blue); menuNum = 2; }
		if (IntRect(880, 310, 200, 66).contains(Mouse::getPosition(window))) { menu3.setColor(Color::Blue); menuNum = 3; }
		if (Mouse::isButtonPressed(Mouse::Button::Left) && pressedBut == false)
		{
			pressedBut = true;
			if (menuNum == 1) gamestate = 2;
			if (menuNum == 2) cout << "sasha pidor"; 
			if (menuNum == 3) gamestate = 0;
			else cout << "KRIVOY HUILA";
		}
		window.draw(menubg);
		window.draw(menu1);
		window.draw(menu2);
		window.draw(menu3);
		window.display();
	}
};

class ChooseHost
{
private:
	Texture mainscreen, buttonHost, buttonClient, buttonBack, offlineTest;
	Sprite menubg, host, client, back, offTest;

	int menuNum = 0;
	bool isMenu;
	
public:
	ChooseHost()
	{
		mainscreen.loadFromFile("mainscreen.jpg");
		buttonHost.loadFromFile("buttons/host.jpg");
		buttonClient.loadFromFile("buttons/client.jpg");
		buttonBack.loadFromFile("buttons/back.jpg");
		offlineTest.loadFromFile("buttons/offlineTest.jpg");
		
		menubg.setTexture(mainscreen);
		host.setTexture(buttonHost);
		client.setTexture(buttonClient);
		back.setTexture(buttonBack);
		offTest.setTexture(offlineTest);
		host.setPosition(540, 250);
		client.setPosition(540, 450);
		back.setPosition(1000, 580);
		offTest.setPosition(1006, 660);

	}
	void render(RenderWindow &window, int &gamestate, int &hostChoosed, TcpSocket &socket,TcpListener &listener, bool &pressedBut)
	{
		menuNum = 0;
		window.clear();
		host.setColor(Color::White);
		client.setColor(Color::White);
		back.setColor(Color::White);
		if (IntRect(540, 250, 200, 66).contains(Mouse::getPosition(window))) { host.setColor(Color::Blue); menuNum = 1; }
		if (IntRect(540, 450, 200, 66).contains(Mouse::getPosition(window))) { client.setColor(Color::Blue); menuNum = 2; }
		if (IntRect(1000, 580, 200, 66).contains(Mouse::getPosition(window))) { back.setColor(Color::Blue); menuNum = 3; }
		if (IntRect(1006, 660, 200, 66).contains(Mouse::getPosition(window))) { offTest.setColor(Color::Blue); menuNum = 4; }
		if (Mouse::isButtonPressed(Mouse::Button::Left) && pressedBut == false)
		{
			pressedBut = true;
			if (menuNum == 1) { cout << "HOST PICKED"; gamestate = 3; listener.listen(55001); cout << "EDIKPIDOR"; }
			if (menuNum == 2) { cout << "CLIENT PICKED"; socket.connect("192.168.100.4", 55001); gamestate = 4; }
			if (menuNum == 3) { cout << "GOING BACK"; gamestate = 1; }
			if (menuNum == 4) { cout << "OFFLINE TEST"; gamestate = 5; }
		}

		window.draw(menubg);
		window.draw(host);
		window.draw(client);
		window.draw(offTest);
		window.draw(back);
		window.display();
	}
};

class WaitingForPlayers
{
private:
	Texture mainscreen, buttonBack, waitconnection;
	Sprite menubg, butBack, waitCon;
	int menuNum = 0;
public:
	WaitingForPlayers()
	{
		mainscreen.loadFromFile("mainscreen.jpg");
		buttonBack.loadFromFile("buttons/back.jpg");
		waitconnection.loadFromFile("buttons/wait.jpg");
		
		menubg.setTexture(mainscreen);
		butBack.setTexture(buttonBack);
		waitCon.setTexture(waitconnection);

		butBack.setPosition(1000, 580);
		waitCon.setPosition(540, 333);
	}
	void render(RenderWindow &window, int &gamestate, TcpListener &listener, bool &pressedBut, TcpSocket &socket)
	{
		window.clear();
		//listener.accept(socket);
		cout << "New client connected: :" << socket.getRemoteAddress() << endl;
		butBack.setColor(Color::White);
		menuNum = 0;
		if (IntRect(1000, 580, 200, 66).contains(Mouse::getPosition(window))) { butBack.setColor(Color::Blue); menuNum = 1; }
		if (Mouse::isButtonPressed(Mouse::Button::Left) && pressedBut == false)
		{
			pressedBut = true;
			if (menuNum == 1) { cout << "BACK TO MAINMENU"; gamestate = 2; listener.close(); }
		}
		if (Socket::Status::Done==listener.accept(socket)) { gamestate = 5; }
		window.draw(menubg);
		window.draw(waitCon);
		window.draw(butBack);
		window.display();
	}
};

class WaitingForServer
{
private:
	Texture mainscreen, buttonBack, waitconnection;
	Sprite menubg, butBack, waitCon;
	int menuNum = 0;
public:
	WaitingForServer()
	{
		mainscreen.loadFromFile("mainscreen.jpg");
		buttonBack.loadFromFile("buttons/back.jpg");
		waitconnection.loadFromFile("buttons/wait.jpg");

		menubg.setTexture(mainscreen);
		butBack.setTexture(buttonBack);
		waitCon.setTexture(waitconnection);

		butBack.setPosition(1000, 580);
		waitCon.setPosition(540, 333);
	}
	void render(RenderWindow &window, int &gamestate,TcpSocket &socket, bool &pressedBut)
	{
		window.clear();
		butBack.setColor(Color::White);
		menuNum = 0;
		if (IntRect(1000, 580, 200, 66).contains(Mouse::getPosition(window))) { butBack.setColor(Color::Blue); menuNum = 1; }
		if (Mouse::isButtonPressed(Mouse::Button::Left) && pressedBut == false)
		{
			pressedBut = true;
			if (menuNum == 1) { cout << "BACK TO MAINMENU"; gamestate = 2; socket.disconnect(); }
		}

		if (Socket::Status::Done == socket.connect("192.168.1.48",55001)) { gamestate = 5; cout << "EDIKPIDOR"; }
		window.draw(menubg);
		window.draw(waitCon);
		window.draw(butBack);
		window.display();
	}
};