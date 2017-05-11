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


void menu(RenderWindow &window)
{
	Texture mainscreen, buttonStart, buttonSettings, buttonExit, buttonHost, buttonClient, buttonBack;
	mainscreen.loadFromFile("mainscreen.jpg");
	buttonStart.loadFromFile("buttons/startgame.jpg");
	buttonSettings.loadFromFile("buttons/settings.jpg");
	buttonExit.loadFromFile("buttons/exit.jpg");
	buttonHost.loadFromFile("buttons/host.jpg");
	buttonClient.loadFromFile("buttons/client.jpg");
	buttonBack.loadFromFile("buttons/back.jpg");

	Sprite menubg(mainscreen), menu1(buttonStart), menu2(buttonSettings), menu3(buttonExit);
	
	bool isMenu = 1;
	
	int menuNum = 0;
	menu1.setPosition(540, 310);
	menu2.setPosition(200, 310);
	menu3.setPosition(880, 310);

	while (isMenu)
	{
		menu1.setColor(Color::White);
		menu2.setColor(Color::White);
		menu3.setColor(Color::White);
		menuNum = 0;
		window.clear(Color(129, 181, 221));
		if (IntRect(540, 310, 200, 66).contains(Mouse::getPosition(window))) { menu1.setColor(Color::Blue); menuNum = 1; }
		if (IntRect(200, 310, 200, 66).contains(Mouse::getPosition(window))) { menu2.setColor(Color::Blue); menuNum = 2; }
		if (IntRect(880, 310, 200, 66).contains(Mouse::getPosition(window))) { menu3.setColor(Color::Blue); menuNum = 3; }

		if (Mouse::isButtonPressed(Mouse::Left))
		{
			if (menuNum == 1) isMenu = false;
			if (menuNum == 2) { cout << "sasha pidor"; }
			if (menuNum == 3) { window.close(); isMenu = false; }
		}
		window.draw(menubg);
		window.draw(menu1);
		window.draw(menu2);
		window.draw(menu3);
		window.display();
	}
	
}
void chooseHost(RenderWindow &window,int &hostChoosed)
{
	Texture mainscreen, buttonHost, buttonClient, buttonBack, offlineTest;
	mainscreen.loadFromFile("mainscreen.jpg");
	buttonHost.loadFromFile("buttons/host.jpg");
	buttonClient.loadFromFile("buttons/client.jpg");
	buttonBack.loadFromFile("buttons/back.jpg");
	offlineTest.loadFromFile("buttons/offlineTest.jpg");
	Sprite menubg(mainscreen), host(buttonHost), client(buttonClient), back(buttonBack), offTest(offlineTest);
	bool isChoosed = 1; 
	int menuNum = 0;
	host.setPosition(540,250);
	client.setPosition(540, 450);
	back.setPosition(1000, 580);
	offTest.setPosition(1006, 660);
	while (isChoosed)
	{

		host.setColor(Color::White);
		client.setColor(Color::White);
		back.setColor(Color::White);
		menuNum = 0;
		window.clear(Color(129, 181, 221));
		if (IntRect(540, 250, 200, 66).contains(Mouse::getPosition(window))) { host.setColor(Color::Blue); menuNum = 1; }
		if (IntRect(540, 450, 200, 66).contains(Mouse::getPosition(window))) { client.setColor(Color::Blue); menuNum = 2; }
		if (IntRect(1000, 580, 200, 66).contains(Mouse::getPosition(window))) { back.setColor(Color::Blue); menuNum = 3; }
		if (IntRect(1006, 660, 200, 66).contains(Mouse::getPosition(window))) { offTest.setColor(Color::Blue); menuNum = 4; }

		if (Mouse::isButtonPressed(Mouse::Left))
		{
			if (menuNum == 1) { cout << "HOST PICKED"; hostChoosed = 1; isChoosed = false; }
			if (menuNum == 2) { cout << "CLIENT PICKED"; hostChoosed = 0; isChoosed = false; }
			if (menuNum == 3) { menu(window); isChoosed = false; }
			if (menuNum == 4) { cout << "OFFLINE TEST"; hostChoosed = 2; isChoosed = false; }
		}
		window.draw(menubg);
		window.draw(host);
		window.draw(client);
		window.draw(back);
		window.draw(offTest);
		window.display();
	}
}

bool startGame() 
{
	int hostChoosed;
	RenderWindow window(VideoMode(1280, 720), "Reflex Strike", Style::None); //�������������� ����
	view.reset(FloatRect(0, 0, 1280, 720)); //������������ ������
	window.setVerticalSyncEnabled(true); //��������� ������������ �������������
	window.setFramerateLimit(60);
	menu(window);
	chooseHost(window,hostChoosed);
	vector <Object> obj;
	Vector2i Pixelpos; //���������� ��� ��������� ��������������� ����
	Vector2f pos; //���������� ��� �������� ��������� ��������� ����
	int gamePaused = 0;
	int pressedbut = 0; //���������� ��� �������� ������� ������ ����(
	Level map; //������� ������ ������ �����
	map.LoadFromFile("map.xml"); //������ ���� �����
	vector <Bullet> bullets1pl; //������ ����
	Bullet bullet("bullet.png");
	Player p1("soldier1.png", 500, 500, map, 1); //������� ������ ������ �����
	Player p2("soldier1.png", 600, 600, map, 2); //������� ������ ������ �����

	float time; //������� ���������� ��� �������� �������� ����
	Clock clock; //������� ������ ������ �������, ��� ������� �������� ����
	if (hostChoosed == 0)
	{
		TcpSocket socket;
		socket.connect("192.168.1.48", 55001);
	}
	if (hostChoosed == 1)
	{
		TcpListener listener;
		listener.listen(55001);
		TcpSocket socket;
		listener.accept(socket);
	}
	if (hostChoosed == 2)
	{
		cout << "STARTED OFFLINE TEST";
	}
	/*TcpSocket tcpsocket;
	string message = "Privet Pidar i client nah!";
	char buffer[1024];
	size_t received = 0;
	tcpsocket.connect("192.168.1.42", 55001);
	Packet input;
	Packet output;
	int p2PosX;
	int p2PosY;
*/
	obj = map.GetAllObjects();
	Event event; //������� ������ ������ �������
	while (window.isOpen()) //����, ���� ������� ����, �� ���������
	{	
		/*input << p1.getSpritePos().x << p1.getSpritePos().y;
		tcpsocket.send(message.c_str(), message.size() + 1);
		tcpsocket.send(output);
		tcpsocket.receive(buffer, sizeof(buffer), received);
		tcpsocket.receive(input);
		output >> p2PosX >> p2PosY;

		p2.sprite.setPosition(p2PosX, p2PosY);
		cout << buffer;*/
		window.clear(); //���������� ������
		Pixelpos = Mouse::getPosition(window); //��������� �������� ��������������� ����
		pos = window.mapPixelToCoords(Pixelpos); //��������������� � ���������� ��������� ����
		time = clock.getElapsedTime().asMilliseconds(); //��������� ������� � �������������
		clock.restart(); //������������� �����
		time = time * 5.5; //������ ����� �������� ����

		if (window.pollEvent(event)) //�������� �������� ����
		{
			if (event.type == Event::Closed) window.close();
		}

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
		bullet.updateDatas(p1.getSpritePos().x,p1.getSpritePos().y,p1.getSpriteOrigin(), pos);

		if (Keyboard::isKeyPressed(Keyboard::Tab)) { return true; }
		if (Keyboard::isKeyPressed(Keyboard::Escape)) { return false; }
		
		
		window.setView(view);
		map.Draw(window); //����� � ���������� �����
		window.draw(p1.sprite); //����� � ���������� ������� ������
		window.draw(p2.sprite); //����� � ���������� ������� ������
		for (int i = 0; i<bullets1pl.size(); i++) // ����� � ���������� ����
			window.draw(bullets1pl[i].sprite);
		
		for (int i = 0; i<bullets1pl.size(); i++)
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


