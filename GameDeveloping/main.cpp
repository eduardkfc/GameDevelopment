#include "Header.h" //���������� header

using namespace sf; //������� ������������� sf::
using namespace std; //������� ������������� std::

void threadFunction()
{
	while (true)
	{
		cout << "Esli eta huynya rabotaet to edik pidor" << endl;
	}
}


bool startGame() 
{
	int hostChoosed;
	int gamestate = 1;
	RenderWindow window(VideoMode(1280, 720), "Reflex Strike", Style::None); //�������������� ����
	view.reset(FloatRect(0, 0, 1280, 720)); //������������ ������
	window.setVerticalSyncEnabled(true); //��������� ������������ �������������
	window.setFramerateLimit(60); //����� ������ � �������
	vector <Object> obj;
	Vector2i Pixelpos; //���������� ��� ��������� ��������������� ����
	Vector2f mousePos1p; //���������� ��� �������� ��������� ��������� ���� ������� ������
	Vector2f mousePos2p; //���������� ��� �������� ��������� ��������� ���� ������� ������
	int gamePaused = 0;
	int damage = 10;
	bool pressedBut = false;
	int pressedbut = 0; //���������� ��� �������� ������� ������ ����(
	Level map; //������� ������ ������ �����
	map.LoadFromFile("map.xml"); //������ ���� �����

	Bullet bullet("bullet.png");
	vector <Bullet> bulletsvector; //������ ���� ������� ������
	vector <Bullet> bulletsvector2p;
	Player p1("soldier1.png", 500, 500, map, 1); //������� ������ ������ �����
	Player p2("soldier1.png", 600, 600, map, 2); //������� ������ ������ �����
	TcpSocket socket;
	TcpListener listener;
	socket.setBlocking(false);
	listener.setBlocking(false);
	float time; //������� ���������� ��� �������� �������� ����
	Clock clock; //������� ������ ������ �������, ��� ������� �������� ����
	obj = map.GetAllObjects();
	Event events; //������� ������ ������ �������
	MainMenu menu;
	ChooseHost chosinghost;
	WaitingForPlayers waitplayers;
	WaitingForServer waitserver;

	thread thr(threadFunction);
	thr.detach();

	Packet packetinput;
	Packet packetoutput;
	float p1posX, p1posY, p1Rotation;
	float p2posX, p2posY, p2Rotation, mousePos2pX,mousePos2pY;
	
	int identify = 0;
	while (window.isOpen()) //����, ���� ������� ����, �� ���������
	{	
		if (gamestate == 0) { return false; }
		else if (gamestate == 1) { menu.render(window, gamestate,pressedBut); }
		else if (gamestate == 2) { chosinghost.render(window, gamestate, hostChoosed, socket, listener,pressedBut, identify); }
		else if (gamestate == 3) { waitplayers.render(window, gamestate, listener, pressedBut, socket); }
		else if (gamestate == 4) { waitserver.render(window, gamestate, socket, pressedBut); }
		else if (gamestate == 5)
		{
			
			p1posX = p1.getSpritePos().x;
			p1posY = p1.getSpritePos().y;
			cout << p1posX << " " << p1posY << "First Player" << endl;
			p1Rotation = p1.sprite.getRotation();
			packetoutput << p1posX << p1posY << p1Rotation << mousePos1p.x << mousePos1p.y;
			socket.send(packetoutput);
			packetoutput.clear();
			
			packetinput.clear();
			socket.receive(packetinput);
			packetinput >> p2posX >> p2posY >> p2Rotation >> mousePos2pX >> mousePos2pY;
			mousePos2p.x = mousePos2pX;
			mousePos2p.y = mousePos2pY;
			if (p2.getSpritePos().x != p2posX && p2.getSpritePos().y != p2posX) { p2.setPosition(p2posX, p2posY); p2.animation(time); }

			p2.sprite.setRotation(p2Rotation);
			cout << p2posX << " " << p2posY << "Second Player" << endl;
		
			window.clear(); //���������� ������
			time = clock.getElapsedTime().asMilliseconds(); //��������� ������� � �������������
			clock.restart(); //������������� �����
			time = time * 5.5; //������ ����� �������� ����

			//-------------------------���������� ������ �������-----------------------------

			Pixelpos = Mouse::getPosition(window); //��������� �������� ��������������� ����
			mousePos1p = window.mapPixelToCoords(Pixelpos); //��������������� � ���������� ��������� ����
			if (window.pollEvent(events)) //�������� �������� ����
				if (events.type == Event::Closed) window.close();
			if (Mouse::isButtonPressed(Mouse::Button::Left) && pressedbut == 0) //�������� ���������� ������� �� ������� ����
			{
				cout << "fire";
				pressedbut = 1;
				bulletsvector.push_back(bullet);
			}
			if (Mouse::isButtonPressed(Mouse::Button::Left)) { pressedbut = 1; } // �������� ���������� ������� �� �������
			else pressedbut = 0;

			p1.moving(time, mousePos1p, obj);
			getPosForPlayer(p1.getSpritePos().x, p1.getSpritePos().y);
			bullet.updateDatas(p1.getSpritePos().x, p1.getSpritePos().y, p1.getSpriteOrigin(), mousePos1p);
			

			//----------------------���������� ������ �������----------------------------------
			p2moving(p2, identify,bulletsvector2p,bullet);
			//bullet.updateDatasP2(p2posX, p2posY, p2.getSpriteOrigin(), mousePos2p);
			
			if (Keyboard::isKeyPressed(Keyboard::Tab)) { return true; }
			if (Keyboard::isKeyPressed(Keyboard::Escape)) { return false; }

			window.setView(view);
			map.Draw(window); //����� � ���������� �����
			window.draw(p1.sprite); //����� � ���������� ������� ������
			window.draw(p2.sprite); //����� � ���������� ������� ������
			for (int i = 0; i < bulletsvector.size(); i++) // ����� � ���������� ����
				window.draw(bulletsvector[i].sprite);
			for (int i = 0; i < bulletsvector.size(); i++)
			{
				bulletsvector[i].update(time);
				if (p2.getRect().contains(bulletsvector[i].getBulletSprPos())) { cout << "POPADANIE"; }

				if (bulletsvector[i].getBulletSprPos().x > 960 || bulletsvector[i].getBulletSprPos().y > 1280 || p2.getRect().contains(bulletsvector[i].getBulletSprPos()))
				{
					bulletsvector.erase(bulletsvector.begin() + i); //�������� �������� �������(����)
				}
				else if (bulletsvector[i].getBulletSprPos().x < 0 || bulletsvector[i].getBulletSprPos().y < 0)
				{
					bulletsvector.erase(bulletsvector.begin() + i); //�������� �������� �������(����)
				}

			}
			for (int i = 0; i < bulletsvector2p.size(); i++) // ����� � ���������� ����
				window.draw(bulletsvector2p[i].sprite);

			//for (int i = 0; i < bulletsvector.size(); i++)
			//{
			//	bulletsvector2p[i].update(time);
			//	if (p1.getRect().contains(bulletsvector2p[i].getBulletSprPos())) { cout << "POPADANIE"; p1.setHealth(damage); cout << p1.getHealth(); }

			//	if (bulletsvector2p[i].getBulletSprPos().x > 960 || bulletsvector2p[i].getBulletSprPos().y > 1280 || p2.getRect().contains(bulletsvector2p[i].getBulletSprPos()))
			//	{
			//		bulletsvector2p.erase(bulletsvector2p.begin() + i); //�������� �������� �������(����)
			//	}
			//	else if (bulletsvector2p[i].getBulletSprPos().x < 0 || bulletsvector2p[i].getBulletSprPos().y < 0)
			//	{
			//		bulletsvector2p.erase(bulletsvector2p.begin() + i); //�������� �������� �������(����)
			//	}

			//}
			

			window.display(); //������������� �������
			
		}
		if (!Mouse::isButtonPressed(Mouse::Button::Left)) // �������� �� ��������� ������� �������
			pressedBut = false;
		
	}
}

void gameRunning() 
{
	if (startGame()) { gameRunning(); }
}

int main() //������� ������� ����
{

	gameRunning();
	return 0;
}


