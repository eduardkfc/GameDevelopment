#pragma once
#include "Header.h"

class GameLoop
{
private:
	int myHealth;
	float time;
	//-���������� ������� ������
	float p2posX, p2posY, p2Rotation, mousePos2pX, mousePos2pY; //���������� ������� ������
	Vector2f mousePos2p; //���������� ��� �������� ��������� ��������� ���� ������� ������
	int enemyHealth;
	int bulletdmg;
	bool myshot, enemyshot;

	Clock clock; //����� ���������������� ������� ����
	HUD hud; //����� ���������� 

	Packet packetinput;
	Packet packetoutput;
	bool queue = true;
	bool settedqueue = false;

	Text p1win, p2win, restartButton;
	Font font;

	Bullet bullet;
	vector <Bullet> bulletsvector; //������ ���� ������� ������
	vector <Bullet> bulletsvector2p;
	float p1rotation;
	int menuNum;
public:
	GameLoop()
	{
		hud.init();
		font.loadFromFile("font.ttf");
		
		p1win.setFont(font);
		p1win.setString("Player 1 WIN!");
		p1win.setCharacterSize(70);
		p1win.setOrigin(p1win.getLocalBounds().width / 2, p1win.getLocalBounds().height / 2);
		p1win.setOutlineThickness(2);

		p2win.setFont(font);
		p2win.setString("You are DEAD!");
		p2win.setCharacterSize(70);
		p2win.setOrigin(p2win.getLocalBounds().width / 2, p2win.getLocalBounds().height / 2);
		p2win.setOutlineThickness(2);

		restartButton.setFont(font);
		restartButton.setString("Restart");
		restartButton.setCharacterSize(30);
		restartButton.setOrigin(restartButton.getLocalBounds().width / 2, restartButton.getLocalBounds().height / 2);
		restartButton.setOutlineThickness(2);
	}
	void render(RenderWindow &window, Player &p1, Player &p2, bool &pressedBut, int &hostChoosed, int &gamestate, TcpSocket &socket, Maps &map, vector <Object> &obj, Vector2f &MousePos)
	{
		if (hostChoosed == 1 && settedqueue == false) { queue = false; settedqueue = true; }
		else if (hostChoosed == 0 && settedqueue == false) { queue = true; settedqueue = true; }

		window.clear(); //���������� ������
		time = clock.getElapsedTime().asMilliseconds(); //��������� ������� � �������������
		clock.restart(); //������������� �����
		time = time / 80; //������ ����� �������� ����
		
		//--����������� � ����������
		p1rotation = p1.getRotation();
		p1.skills(bullet);
		p1.moving(time, obj, pressedBut, bulletsvector, bullet, map, window, MousePos, myshot, p1rotation);
		getPosForPlayer(p1.getSpritePos().x, p1.getSpritePos().y); //������ ����

		packetoutput.clear();
		packetinput.clear();
		
		//���������� ������ ����������
		if (queue == false || myshot == true)
		{
			packetoutput << p1.getSpritePos().x << p1.getSpritePos().y << p1rotation << p1.getHealth() << p2.getHealth() << bullet.getDamage() << myshot; //��������� ������
			socket.send(packetoutput); //�������� ������
			queue = true; // ���� ������� ������� ������
		}
		if (!socket.receive(packetinput)) //����� ������� �� ���������� ���� ��� ��������
		{
			packetinput >> p2posX >> p2posY >> p2Rotation >> enemyHealth >> myHealth >> bulletdmg >> enemyshot; // ����������
			if ((p2.getSpritePos().x != p2posX) || (p2.getSpritePos().y != p2posY)) { p2.animation(time); } // �������� ������� ������
			if (p1.getHealth() != myHealth) { p1.setHealth(myHealth); } //������������� ��������
			p2.setPosition(p2posX, p2posY); //���������� �������
			p2.sprite.setRotation(p2Rotation); // ���������� 
			if (enemyshot == true) //�������� �� ������� ����������
			{
				bulletsvector2p.push_back(bullet); // ���������� ���� � ������
				bulletsvector2p[bulletsvector2p.size() - 1].create(p2.getSpritePos().x, p2.getSpritePos().y, p2Rotation); //�������
			}
			queue = false; //���� ������� ������� ������
		}
	
		if (Keyboard::isKeyPressed(Keyboard::Escape)) { gamestate = 9; } //������� ���� �� ������

		enemyshot = false;
		myshot = false;

		window.setView(view); //���������� ������ ����
		map.Draw(window); //����� � ���������� �����
		window.draw(p1.sprite); //����� � ���������� ������� ������
		window.draw(p2.sprite); //����� � ���������� ������� ������
		hud.draw(window, p1, p2);
		
	//-----------------------�������������� � ��������� � ����������� ���� ������� ������-----------------------
		for (int j = 0; j < obj.size(); j++)//���������� �� �������� �����
			for (int i = 0; i < bulletsvector.size(); i++) //���������� �� ������� ����
			{
				if (bulletsvector[i].getBulletRect().intersects(obj[j].rect)) //��������� ������� � ��������� �����
				{
					if (obj[j].name == "solid")//���� ��������� �����������
					{
						bulletsvector.erase(bulletsvector.begin() + i); //�������� ����
					}
				}
			}
		// �������� ��������� ���� � ������
		for (int i = 0; i < bulletsvector.size(); i++) 
		{
			bulletsvector[i].update(time); // ���������� ����
			if (bulletsvector[i].getBulletRect().intersects(p2.getGlobalBounds())) //��������� ������� � �������
			{
				bulletsvector.erase(bulletsvector.begin() + i); //�������� ����
				p2.setHealth(p2.getHealth() - bullet.getDamage()); // ��������� �����
			}

		}
		// ����� � ���������� ����
		for (int i = 0; i < bulletsvector.size(); i++) 
			window.draw(bulletsvector[i].sprite);
	//----------------------�������������� � ��������� � ����������� ���� ������� ������------------------------
	//���������� �� ��������
		for (int j = 0; j < obj.size(); j++)//���������� �� �������� �����
			for (int i = 0; i < bulletsvector2p.size(); i++)//���������� �� ������� ����
			{
				if (bulletsvector2p[i].getBulletRect().intersects(obj[j].rect))//��������� ����������� ������ � ��������
				{
					if (obj[j].name == "solid")//���� ��������� �����������
					{
						bulletsvector2p.erase(bulletsvector2p.begin() + i); //�������� ����
					}
				}
			}

		for (int i = 0; i < bulletsvector2p.size(); i++)
		{
			bulletsvector2p[i].update(time); // ���������� ����
			if (bulletsvector2p[i].getBulletRect().intersects(p1.getGlobalBounds())) //��������� ������� � �������
			{
				bulletsvector2p.erase(bulletsvector2p.begin() + i); //�������� ����
				p1.setHealth(p1.getHealth() - bulletdmg); // ��������� �����
			}

		}
		// ����� � ���������� ����
		for (int i = 0; i < bulletsvector2p.size(); i++) // ����� � ���������� ����
			window.draw(bulletsvector2p[i].sprite);

		//�������� ��� ��������� ����		
		if (p1.getHealth() <= 0)
		{
			while (true)
			{
				window.clear();
				p2win.setPosition(p1.getSpritePos().x,p1.getSpritePos().y-200);
				restartButton.setPosition(p1.getSpritePos().x, p1.getSpritePos().y);
				restartButton.setFillColor(Color::White);
				menuNum = 0;
				if (restartButton.getGlobalBounds().contains(Vector2f(window.mapPixelToCoords(Mouse::getPosition(window))))) { restartButton.setFillColor(Color::Blue); menuNum = 1; }
				if (Mouse::isButtonPressed(Mouse::Button::Left) && pressedBut == false)
				{
					pressedBut = true;
					if (menuNum == 1) { gamestate = 9; break; }
				}
				window.draw(p2win);
				window.draw(restartButton);
				window.display();
			}
		}
		else if (p2.getHealth() <= 0)
		{
			while (true)
			{
				window.clear();
				p1win.setPosition(p1.getSpritePos().x, p1.getSpritePos().y - 200);
				restartButton.setPosition(p1.getSpritePos().x, p1.getSpritePos().y);
				restartButton.setFillColor(Color::White);
				menuNum = 0;
				if (restartButton.getGlobalBounds().contains(Vector2f(window.mapPixelToCoords(Mouse::getPosition(window))))) { restartButton.setFillColor(Color::Blue); menuNum = 1; }
				if (Mouse::isButtonPressed(Mouse::Button::Left)) //&& pressedBut == false)
				{
					//pressedBut = true;
					if (menuNum == 1) { gamestate = 9; break; }
				}
				window.draw(p1win);
				window.draw(restartButton);
				window.display();
			}
		}

		window.display(); //������������� �������
	}
};