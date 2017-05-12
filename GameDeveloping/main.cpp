#include "Header.h" //���������� header

using namespace sf; //������� ������������� sf::
using namespace std; //������� ������������� std::

//void gamepaused(int &gamePaused,RenderWindow &window)
//{
//	Image pauseimage;
//	pauseimage.loadFromFile("buttons/pause.png");
//	pauseimage.createMaskFromColor(Color::White);
//	Texture pausescreen;
//	pausescreen.loadFromImage(pauseimage);
//	Sprite pause(pausescreen);
//	pause.setPosition(300, 300);
//	int pIsPressed = 0;
//	if (Keyboard::isKeyPressed(Keyboard::P)) { gamePaused = 1; pIsPressed = 1; }
//	else pIsPressed = 0;
//	while (gamePaused == 1)
//	{
//		cout << " pause ";
//		if ((Keyboard::isKeyPressed(Keyboard::O) && gamePaused == 1)) { gamePaused = 0; }
//		else pIsPressed = 0;
//		window.draw(pause);
//		window.display();
//	}
//}




bool startGame() 
{
	int hostChoosed;
	int gamestate = 1;
	RenderWindow window(VideoMode(1280, 720), "Reflex Strike", Style::None); //�������������� ����
	view.reset(FloatRect(0, 0, 1280, 720)); //������������ ������
	window.setVerticalSyncEnabled(true); //��������� ������������ �������������
	window.setFramerateLimit(60);
	vector <Object> obj;
	Vector2i Pixelpos; //���������� ��� ��������� ��������������� ����
	Vector2f pos; //���������� ��� �������� ��������� ��������� ����
	int gamePaused = 0;
	bool pressedBut = false;
	int pressedbut = 0; //���������� ��� �������� ������� ������ ����(
	Level map; //������� ������ ������ �����
	map.LoadFromFile("map.xml"); //������ ���� �����
	vector <Bullet> bullets1pl; //������ ����
	Bullet bullet("bullet.png");
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
	Packet packetinput;
	Packet packetoutput;
	float p1posX, p1posY, p1Rotation;
	float p2posX, p2posY, p2Rotation;

	while (window.isOpen()) //����, ���� ������� ����, �� ���������
	{	
		if (gamestate == 0) { return false; }
		else if (gamestate == 1) { menu.render(window, gamestate,pressedBut); }
		else if (gamestate == 2) { chosinghost.render(window, gamestate, hostChoosed, socket, listener,pressedBut); }
		else if (gamestate == 3) { waitplayers.render(window, gamestate, listener,pressedBut); }
		else if (gamestate == 4) { waitserver.render(window, gamestate, socket,pressedBut); }
		else if (gamestate == 5)
		{
			p1posX = p1.getSpritePos().x;
			p1posY = p1.getSpritePos().y;
			p1Rotation = p1.sprite.getRotation();
			packetoutput << p1posX << p1posY << p1Rotation;
			socket.send(packetoutput);

			socket.receive(packetinput);
			packetinput >> p2posX >> p2posY >> p2Rotation;
			p2.setPosition(p2posX, p2posY);
			p2.sprite.setRotation(p2Rotation);

			window.clear(); //���������� ������
			Pixelpos = Mouse::getPosition(window); //��������� �������� ��������������� ����
			pos = window.mapPixelToCoords(Pixelpos); //��������������� � ���������� ��������� ����
			time = clock.getElapsedTime().asMilliseconds(); //��������� ������� � �������������
			clock.restart(); //������������� �����
			time = time * 5.5; //������ ����� �������� ����
			if (window.pollEvent(events)) //�������� �������� ����
				if (events.type == Event::Closed) window.close();
			if (Mouse::isButtonPressed(Mouse::Button::Left) && pressedbut == 0) //�������� ���������� ������� �� ������� ����
			{
				cout << "fire";
				pressedbut = 1;
				bullets1pl.push_back(bullet);
			}

			if (Mouse::isButtonPressed(Mouse::Button::Left)) { pressedbut = 1; } // �������� ���������� ������� �� �������
			else pressedbut = 0;

			p1.moving(time, pos, obj);
			getPosForPlayer(p1.getSpritePos().x, p1.getSpritePos().y);
			bullet.updateDatas(p1.getSpritePos().x, p1.getSpritePos().y, p1.getSpriteOrigin(), pos);

			if (Keyboard::isKeyPressed(Keyboard::Tab)) { return true; }
			if (Keyboard::isKeyPressed(Keyboard::Escape)) { return false; }


			window.setView(view);
			map.Draw(window); //����� � ���������� �����
			window.draw(p1.sprite); //����� � ���������� ������� ������
			window.draw(p2.sprite); //����� � ���������� ������� ������
			for (int i = 0; i < bullets1pl.size(); i++) // ����� � ���������� ����
				window.draw(bullets1pl[i].sprite);

			for (int i = 0; i < bullets1pl.size(); i++)
			{
				bullets1pl[i].update(time);
				if (p2.getRect().contains(bullets1pl[i].getBulletSprPos())) { cout << "POPADANIE"; }

				if (bullets1pl[i].getBulletSprPos().x > 960 || bullets1pl[i].getBulletSprPos().y > 1280 || p2.getRect().contains(bullets1pl[i].getBulletSprPos()))
				{
					bullets1pl.erase(bullets1pl.begin() + i); //�������� �������� �������(����)
				}
				else if (bullets1pl[i].getBulletSprPos().x < 0 || bullets1pl[i].getBulletSprPos().y < 0)
				{
					bullets1pl.erase(bullets1pl.begin() + i); //�������� �������� �������(����)
				}

			}
			//gamepaused(gamePaused, window);
			window.display(); //������������� �������
			
		}
		if (!Mouse::isButtonPressed(Mouse::Button::Left))
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


