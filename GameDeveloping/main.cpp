#include "Header.h" //���������� header

using namespace sf; //������� ������������� sf::
using namespace std; //������� ������������� std::


bool startGame() 
{
	int hostChoosed;
	int gamestate = 1;
	RenderWindow window(VideoMode(1280, 720), "Reflex Strike", Style::None); //�������������� ����
	view.reset(FloatRect(0, 0, 1280, 720)); //������������ ������
	window.setVerticalSyncEnabled(true); //��������� ������������ �������������
	//window.setFramerateLimit(60); //����� ������ � �������
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

	//-----------------------------------��� ����������� ������������-----------------------
	
	Player p1("soldier1.png", 500, 500, map, 1); //������� ������ ������ �����
	Player p2("soldier1.png", 600, 600, map, 2); //������� ������ ������ �����
	Bullet bullet("bullet.png");
	vector <Bullet> bulletsvector; //������ ���� ������� ������
	vector <Bullet> bulletsvector2p;

	float time; //������� ���������� ��� �������� �������� ����
	Clock clock; //������� ������ ������ �������, ��� ������� �������� ����
	obj = map.GetAllObjects();
	Event events; //������� ������ ������ �������
	UdpSocket socket;
	socket.setBlocking(false);
	IpAddress myip = IpAddress::getLocalAddress();
	IpAddress enemyip("192.168.100.5");
	unsigned short port;

	MainMenu menu;
	ChooseHost choosinghost;
	WaitingForPlayers waitplayers;
	WaitingForServer waitserver;
	Help helpwindow;
	Color color(255, 0, 0);
	HUD hud; hud.init();
	Packet packetinput;
	Packet packetoutput;
	float p2posX, p2posY, p2Rotation, mousePos2pX,mousePos2pY;
	int enemyHealth, myHealth;

	while (window.isOpen()) //����, ���� ������� ����, �� ���������
	{	
		if (gamestate == 0) { return false; }
		else if (gamestate == 1) { menu.render(window, gamestate,pressedBut); }
		else if (gamestate == 2) { choosinghost.render(window, gamestate, hostChoosed, socket, pressedBut, myip, enemyip); }
		else if (gamestate == 3) { waitplayers.render(window, gamestate, pressedBut, socket, myip, enemyip); }
		else if (gamestate == 4) { waitserver.render(window, gamestate, socket, pressedBut, myip, enemyip); }
		else if (gamestate == 6) { helpwindow.render(window, gamestate, pressedBut); }
		else if (gamestate == 5)
		{
			if (hostChoosed == 1) { port = 55002; }
			else port == 55001;
			window.clear(); //���������� ������
			time = clock.getElapsedTime().asMilliseconds(); //��������� ������� � �������������
			clock.restart(); //������������� �����
			
			time = time * 5.4; //������ ����� �������� ����

			//--�����������--
			p1.skills(bullet);

			//-------------------------���������� ������ �������-----------------------------
			Pixelpos = Mouse::getPosition(window); //��������� �������� ��������������� ����
			mousePos1p = window.mapPixelToCoords(Pixelpos); //��������������� � ���������� ��������� ����
			
			if (window.pollEvent(events)) //�������� �������� ����
				if (events.type == Event::Closed) window.close();
			
			p1.moving(time, mousePos1p, obj);
			getPosForPlayer(p1.getSpritePos().x, p1.getSpritePos().y);
			
			bullet.updateDatas(p1.getSpritePos().x, p1.getSpritePos().y, Vector2f(window.mapPixelToCoords(Mouse::getPosition(window))));
			if (Mouse::isButtonPressed(Mouse::Button::Left) && pressedbut == 0) //�������� ���������� ������� �� ������� ����
			{
				cout << "fire";
				pressedbut = 1;
				
				bulletsvector.push_back(bullet);
				
			}
			if (Mouse::isButtonPressed(Mouse::Button::Left)) { pressedbut = 1; } // �������� ���������� ������� �� �������
			else pressedbut = 0;

			//cout << p1posX << " " << p1posY << "First Player" << endl;
			packetoutput << p1.getSpritePos().x << p1.getSpritePos().y << p1.getRotation() << mousePos1p.x << mousePos1p.y << p1.getHealth() << p2.getHealth();
			socket.send(packetoutput, enemyip, port);
			packetoutput.clear();
			

			

			//----------------------���������� ������ �������----------------------------------
			
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
			
			
			if (Keyboard::isKeyPressed(Keyboard::Tab)) { return true; }
			if (Keyboard::isKeyPressed(Keyboard::Escape)) { return false; }
			if (Keyboard::isKeyPressed(Keyboard::U)) { p1.setHealth(100); }
			if (Keyboard::isKeyPressed(Keyboard::H)) { p2.sprite.move(0, p1.getSpeed()*time); }
			if (p1.getHealth() <= 0 || p2.getHealth() <= 0) { return true; }

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


