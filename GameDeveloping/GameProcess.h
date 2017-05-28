#pragma once
#include "Header.h"

class MainGame
{
private:
	int gamePaused, enemyHealth, myHealth;
	float time;
	float p2posX, p2posY, p2Rotation, mousePos2pX, mousePos2pY;
	vector <Object> obj;
	Clock clock;
	Event events; 
	HUD hud;
	unsigned short port;
	Vector2i Pixelpos; //���������� ��� ��������� ��������������� ����
	Vector2f mousePos1p; //���������� ��� �������� ��������� ��������� ���� ������� ������
	Vector2f mousePos2p; //���������� ��� �������� ��������� ��������� ���� ������� ������
	Packet packetinput;
	Packet packetoutput;
	Bullet bullet;
	vector <Bullet> bulletsvector; //������ ���� ������� ������
	vector <Bullet> bulletsvector2p;
	Level map; //������� ������ ������ �����
public:
	MainGame(int &levelID)
	{
		hud.init();
		if (levelID == 1)
		{
			map.LoadFromFile("road.xml"); //������ ���� �����
		}
		else if (levelID == 2)
		{
			map.LoadFromFile("village.xml"); //������ ���� �����
		}
		
		obj = map.GetObjects("solid");
	}
	void render(RenderWindow &window,Player &p1,Player &p2,bool &pressedBut,int &hostChoosed,int &gamestate,UdpSocket &socket,IpAddress &enemyip)
	{
		if (hostChoosed == 1) { port = 55002; }
		else port == 55001;

		window.clear(); //���������� ������
		time = clock.getElapsedTime().asMilliseconds(); //��������� ������� � �������������
		clock.restart(); //������������� �����
		time = time / 80; //������ ����� �������� ����
		
		//--�����������--
		p1.skills(bullet);

		Pixelpos = Mouse::getPosition(window); //��������� �������� ��������������� ����
		mousePos1p = window.mapPixelToCoords(Pixelpos); //��������������� � ���������� ��������� ����

		p1.moving(time, mousePos1p, obj, pressedBut, bulletsvector, bullet, map);
		getPosForPlayer(p1.getSpritePos().x, p1.getSpritePos().y);

		if (window.pollEvent(events)) //�������� �������� ����
			if (events.type == Event::Closed) window.close();

		bullet.updateDatas(p1.getSpritePos().x, p1.getSpritePos().y, Vector2f(window.mapPixelToCoords(Mouse::getPosition(window))));

		packetoutput << p1.getSpritePos().x << p1.getSpritePos().y << p1.getRotation() << mousePos1p.x << mousePos1p.y << p1.getHealth() << p2.getHealth();
		socket.send(packetoutput, enemyip, port);
		packetoutput.clear();

		packetinput.clear();
		if (!socket.receive(packetinput, enemyip, port))
		{
			packetinput >> p2posX >> p2posY >> p2Rotation >> mousePos2pX >> mousePos2pY >> enemyHealth >> myHealth;
			if (p1.getHealth() != myHealth)
			{
				p1.setHealth(myHealth);
			}
			mousePos2p.x = mousePos2pX;
			mousePos2p.y = mousePos2pY;
			if ((p2.getSpritePos().x != p2posX) || (p2.getSpritePos().y != p2posY)) { p2.animation(time); }
			p2.setPosition(p2posX, p2posY);
			p2.sprite.setRotation(p2Rotation);
			cout << p2posX << " " << p2posY << "Second Player" << endl;

		}
		if (Keyboard::isKeyPressed(Keyboard::Tab)) {  }
		if (Keyboard::isKeyPressed(Keyboard::U)) { p1.setHealth(100); }
		if (Keyboard::isKeyPressed(Keyboard::H)) { p2.sprite.move(0, p1.getSpeed()*time); }

		window.setView(view);
		map.Draw(window); //����� � ���������� �����
		window.draw(p1.sprite); //����� � ���������� ������� ������
		window.draw(p2.sprite); //����� � ���������� ������� ������

		hud.draw(window, p1, p2);
		for (int j = 0; j < obj.size(); j++)//���������� �� ��������
			for (int i = 0; i < bulletsvector.size(); i++)
			{
				//cout << "error";

				if (bulletsvector[i].getBulletRect().intersects(obj[j].rect))//��������� ����������� ������ � ��������
				{
					if (obj[j].name == "solid")//���� ��������� �����������
					{

						bulletsvector.erase(bulletsvector.begin() + i);
					}
				}
			}
		for (int i = 0; i < bulletsvector.size(); i++)
		{
			bulletsvector[i].update(time);
			if (bulletsvector[i].getBulletRect().intersects(p2.getGlobalBounds()))
			{
				cout << "POPADANIE"; bulletsvector.erase(bulletsvector.begin() + i);
				p2.setHealth(p2.getHealth() - bullet.getDamage());
			}

		}
		for (int i = 0; i < bulletsvector.size(); i++) // ����� � ���������� ����
			window.draw(bulletsvector[i].sprite);
		//----------------------------------------------------------------------------------
		for (int j = 0; j < obj.size(); j++)//���������� �� ��������
			for (int i = 0; i < bulletsvector2p.size(); i++)
			{
				//cout << "error";

				if (bulletsvector2p[i].getBulletRect().intersects(obj[j].rect))//��������� ����������� ������ � ��������
				{
					if (obj[j].name == "solid")//���� ��������� �����������
					{

						bulletsvector2p.erase(bulletsvector2p.begin() + i);
					}
				}
			}
		for (int i = 0; i < bulletsvector2p.size(); i++)
		{
			bulletsvector2p[i].update(time);
			if (bulletsvector2p[i].getBulletRect().intersects(p2.getGlobalBounds()))
			{
				cout << "POPADANIE"; bulletsvector2p.erase(bulletsvector2p.begin() + i);
				p2.setHealth(p2.getHealth() - bullet.getDamage());
			}

		}
		for (int i = 0; i < bulletsvector2p.size(); i++) // ����� � ���������� ����
			window.draw(bulletsvector2p[i].sprite);

		window.display(); //������������� �������
	}
};