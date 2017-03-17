#include "Header.h" //���������� header

using namespace sf; //������� ������������� sf::
using namespace std; //������� ������������� std::




void menu(RenderWindow &window)
{
	Texture mainscreen, buttonStart, buttonSettings, buttonExit;
	mainscreen.loadFromFile("mainscreen.jpg");
	buttonStart.loadFromFile("buttons/startgame.jpg");
	buttonSettings.loadFromFile("buttons/settings.jpg");
	buttonExit.loadFromFile("buttons/exit.jpg");
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
		window.clear();
		window.draw(menubg);
		window.draw(menu1);
		window.draw(menu2);
		window.draw(menu3);
		window.display();
	}
	
}

bool startGame() 
{
	RenderWindow window(VideoMode(1280, 720), "Reflex Strike", Style::None); //�������������� ����
	view.reset(FloatRect(0, 0, 1280, 720)); //������������ ������
	window.setVerticalSyncEnabled(true); //��������� ������������ �������������
	menu(window);
	vector <Object> obj;
	Vector2i Pixelpos; //���������� ��� ��������� ��������������� ����
	Vector2f pos; //���������� ��� �������� ��������� ��������� ����

	int gamestate = 1;
	int pressedbut = 0; //���������� ��� �������� ������� ������ ����(
	Level map; //������� ������ ������ �����
	map.LoadFromFile("map.xml"); //������ ���� �����
	vector <Bullet> bullets1pl; //������ ����
	Player p1("soldier1.png", 500, 500, map, 1); //������� ������ ������ �����
	Player p2("soldier1.png", 600, 600, map, 2); //������� ������ ������ �����


	float time; //������� ���������� ��� �������� �������� ����
	Clock clock; //������� ������ ������ �������, ��� ������� �������� ����

	while (window.isOpen()) //����, ���� ������� ����, �� ���������
	{

		Pixelpos = Mouse::getPosition(window); //��������� �������� ��������������� ����
		pos = window.mapPixelToCoords(Pixelpos); //��������������� � ���������� ��������� ����
		time = clock.getElapsedTime().asMicroseconds(); //��������� ������� � �������������
		clock.restart(); //������������� �����
		time = time / 150; //������ ����� �������� ����
		Bullet bullet("bullet.png", p1.getSpritePos().x, p1.getSpritePos().y, p1.getSpriteOrigin(), pos, time);
		Event event; //������� ������ ������ �������
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

		obj = map.GetAllObjects();

		p1.moving(time, pos, window,obj);
		getPosForPlayer(p1.getSpritePos().x, p1.getSpritePos().y);
		

		if (Keyboard::isKeyPressed(Keyboard::Tab)) { return true; }
		if (Keyboard::isKeyPressed(Keyboard::Escape)) { return false; }
		window.clear(); //���������� ������
		window.setView(view);
		map.Draw(window); //����� � ���������� �����
		window.draw(p1.sprite); //����� � ���������� ������� ������
		window.draw(p2.sprite); //����� � ���������� ������� ������
		for (int i = 0; i<bullets1pl.size(); i++) // ����� � ���������� ����
			window.draw(bullets1pl[i].sprite);
			
		for (int i = 0; i<bullets1pl.size(); i++)
		{
			bullets1pl[i].update();
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


