#pragma once
#include "Header.h"

class MainMenu
{
private:
	Texture mainscreen, buttonStart, buttonHelp, buttonExit;
	Sprite menubg, menu1, menu2, menu3;
	int menuNum;
	bool isMenu;
public:
	MainMenu()
	{
		mainscreen.loadFromFile("mainscreen.jpg");
		buttonStart.loadFromFile("buttons/startgame.jpg");
		buttonHelp.loadFromFile("buttons/help.jpg");
		buttonExit.loadFromFile("buttons/exit.jpg");
		menubg.setTexture(mainscreen);
		menu1.setTexture(buttonStart);
		menu2.setTexture(buttonHelp);
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
			if (menuNum == 2) gamestate = 6; 
			if (menuNum == 3) gamestate = 0;
		}
		window.draw(menubg);
		window.draw(menu1);
		window.draw(menu2);
		window.draw(menu3);
		window.display();
	}
};

class Help
{
private:
	Texture mainscreen, SSicon, DDicon, buttonBack;
	Sprite menubg, SSico, DDico, bBack;
	bool menuNum;
	bool isMenu;
public:
	Help()
	{
		mainscreen.loadFromFile("mainscreen.jpg");
		SSicon.loadFromFile("images/superspeed.jpg");
		DDicon.loadFromFile("images/doubledamage.jpg");
		buttonBack.loadFromFile("buttons/back.jpg");
		menubg.setTexture(mainscreen);
		SSico.setTexture(SSicon);
		DDico.setTexture(DDicon);
		bBack.setTexture(buttonBack);

		menuNum = false;
		SSico.setPosition(540, 310);
		DDico.setPosition(200, 310);
		bBack.setPosition(880, 310);

	}
	void render(RenderWindow &window, int &gamestate, bool &pressedBut)
	{
		menuNum = 0;
		window.clear();
		bBack.setColor(Color::White);

		if (IntRect(880,310,200,66).contains(Mouse::getPosition(window))) { bBack.setColor(Color::Blue); menuNum = true; }
		if (Mouse::isButtonPressed(Mouse::Button::Left) && pressedBut == false)
		{
			pressedBut = true;
			if (menuNum == true) gamestate = 1;
		}
		window.draw(menubg);
		window.draw(DDico);
		window.draw(SSico);
		window.draw(bBack);
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
	void render(RenderWindow &window, int &gamestate, int &hostChoosed, UdpSocket &socket, bool &pressedBut,IpAddress &myip,IpAddress &enemyip)
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
			if (menuNum == 1) { cout << "HOST PICKED"; socket.bind(55001, myip); gamestate = 3; hostChoosed = 1; }
			if (menuNum == 2) { cout << "CLIENT PICKED"; socket.bind(55002, myip); gamestate = 4; hostChoosed = 0; }
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
	Packet packetinput;
	Packet packetoutput;
	bool inputcode;
	bool outputcode;
	unsigned short port;
public:
	WaitingForPlayers()
	{
		mainscreen.loadFromFile("mainscreen.jpg");
		buttonBack.loadFromFile("buttons/back.jpg");
		waitconnection.loadFromFile("buttons/wait.jpg");
		
		menubg.setTexture(mainscreen);
		butBack.setTexture(buttonBack);
		waitCon.setTexture(waitconnection);
		port = 55002;
		inputcode = false;
		outputcode = false;
		butBack.setPosition(1000, 580);
		waitCon.setPosition(540, 333);
	}
	void render(RenderWindow &window, int &gamestate, bool &pressedBut, UdpSocket &socket,IpAddress &myip,IpAddress &enemyip)
	{
		window.clear();
		butBack.setColor(Color::White);
		menuNum = 0;
		if (IntRect(1000, 580, 200, 66).contains(Mouse::getPosition(window))) { butBack.setColor(Color::Blue); menuNum = 1; }
		if (Mouse::isButtonPressed(Mouse::Button::Left) && pressedBut == false)
		{
			pressedBut = true;
			if (menuNum == 1) { cout << "BACK TO MAINMENU"; socket.unbind(); gamestate = 2;  }
		}
		packetinput.clear();
		packetoutput.clear();
		packetoutput << outputcode;
		socket.send(packetoutput, enemyip, port);
		if (socket.receive(packetinput, enemyip, port)) 
		{ 
			packetinput >> inputcode;
			if (inputcode == true) { gamestate = 5; }
			
		}
		packetoutput >> outputcode;
		cout << outputcode;
		
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
	Packet packetinput;
	Packet packetoutput;
	bool inputcode;
	bool outputcode;
	unsigned short port;
public:
	WaitingForServer()
	{
		mainscreen.loadFromFile("mainscreen.jpg");
		buttonBack.loadFromFile("buttons/back.jpg");
		waitconnection.loadFromFile("buttons/wait.jpg");
		port = 55001;
		menubg.setTexture(mainscreen);
		butBack.setTexture(buttonBack);
		waitCon.setTexture(waitconnection);
		inputcode = true;
		butBack.setPosition(1000, 580);
		waitCon.setPosition(540, 333);
	}
	void render(RenderWindow &window, int &gamestate,UdpSocket &socket, bool &pressedBut, IpAddress &myip, IpAddress &enemyip)
	{
		window.clear();
		butBack.setColor(Color::White);
		menuNum = 0;
		if (IntRect(1000, 580, 200, 66).contains(Mouse::getPosition(window))) { butBack.setColor(Color::Blue); menuNum = 1; }
		if (Mouse::isButtonPressed(Mouse::Button::Left) && pressedBut == false)
		{
			pressedBut = true;
			if (menuNum == 1) { cout << "BACK TO MAINMENU"; socket.unbind(); gamestate = 2; }
		}
		packetoutput.clear();
		outputcode = true;
		packetoutput << outputcode;
		packetinput.clear();
		socket.send(packetoutput, enemyip, port);
		if (socket.receive(packetinput, enemyip, port)) 
		{ 
			packetinput >> inputcode;
			if (inputcode == false) { gamestate = 5; }
			
		}
		
		window.draw(menubg);
		window.draw(waitCon);
		window.draw(butBack);
		window.display();
	}
};