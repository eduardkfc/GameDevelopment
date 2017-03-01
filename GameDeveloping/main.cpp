#include "Header.h" //���������� header

using namespace sf; //������� ������������� sf::
using namespace std; //������� ������������� std::
Vector2i Pixelpos; //���������� ��� ��������� ��������������� ����
Vector2f pos; //���������� ��� �������� ��������� ��������� ����
int gamestate = 1;
int pressedbut = 0; //���������� ��� �������� ������� ������ ����(



void mainmenu(RenderWindow &window)
{
	Texture mainscreen;
	Texture buttonStart;
	Texture buttonSettings;
	Texture buttonExit;
	mainscreen.loadFromFile("mainscreen.jpg");
	buttonStart.loadFromFile("buttons/startgame.jpg");
	buttonSettings.loadFromFile("buttons/settings.jpg");
	buttonExit.loadFromFile("buttons/exit.jpg");
	Sprite mainscreene;
	Sprite butStart;
	Sprite butSettings;
	Sprite butExit;
	mainscreene.setTexture(mainscreen);
	butStart.setTexture(buttonStart);
	butSettings.setTexture(buttonSettings);
	butExit.setTexture(buttonExit);
	butSettings.setPosition(200, 310);
	butStart.setPosition(540, 310);
	butExit.setPosition(880, 310);
	window.clear();
	window.draw(mainscreene);
	window.draw(butStart);
	window.draw(butSettings);
	window.draw(butExit);
	window.display();
}

void methodchoose()
{
	
}
void startedgame(RenderWindow &window)
{
	Level map; //������� ������ ������ �����
	map.LoadFromFile("map.xml"); //������ ���� �����
	Player p1("soldier1.png", 500, 500, map, 1); //������� ������ ������ �����
	Player p2("soldier1.png", 600, 600, map, 2); //������� ������ ������ �����
	vector <Bullet> bullets1pl; //������ ����
	float time; //������� ���������� ��� �������� �������� ����
	Clock clock; //������� ������ ������ �������, ��� ������� �������� ����
	Pixelpos = Mouse::getPosition(window); //��������� �������� ��������������� ����
	pos = window.mapPixelToCoords(Pixelpos); //��������������� � ���������� ��������� ����
	time = clock.getElapsedTime().asMicroseconds(); //��������� ������� � �������������
	clock.restart(); //������������� �����
	time = time / 150; //������ ����� �������� ����
	Bullet bullet("bullet.png", p1.getSpritePos().x, p1.getSpritePos().y, p1.getSpriteOrigin(), pos, time);
	if (Mouse::isButtonPressed(Mouse::Button::Left) && pressedbut == 0) //�������� ���������� ������� �� ������� ����
	{
		pressedbut = 1;
		bullets1pl.push_back(bullet);
	}
	p1.moving(time, pos, window);
	window.clear(); //���������� ������
	getPosForPlayer(p1.getSpritePos().x, p1.getSpritePos().y);
	window.setView(view);
	map.Draw(window); //����� � ���������� �����
	window.draw(p1.sprite); //����� � ���������� ������� ������
	window.draw(p2.sprite); //����� � ���������� ������� ������
	for (int i = 0; i<bullets1pl.size(); i++) // ����� � ���������� ����
		window.draw(bullets1pl[i].sprite);

	for (int i = 0; i<bullets1pl.size(); i++)
	{
		bullets1pl[i].update();
		if (bullets1pl[i].getBulletSprPos().x > 960 || bullets1pl[i].getBulletSprPos().y > 1280)
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

int main() //������� ������� ����
{
	//gamestate = 1 MainMenu
	//gamestate = 2 Choose Host
	//gamestate = 3 Settings
	//gamestate = 4 Start Game
	RenderWindow window(VideoMode(1280,720), "Reflex Strike",Style::None); //�������������� ����
	view.reset(FloatRect(0, 0, 1280, 720)); //������������ ������
	window.setVerticalSyncEnabled(true); //��������� ������������ �������������
	
	
	
	while (window.isOpen()) //����, ���� ������� ����, �� ���������
	{
		if (gamestate == 1) { mainmenu(window); }
		if (gamestate == 4) { startedgame(window); }
		Pixelpos = Mouse::getPosition(window); //��������� �������� ��������������� ����
		pos = window.mapPixelToCoords(Pixelpos); //��������������� � ���������� ��������� ����
		if (Mouse::isButtonPressed(Mouse::Button::Left))
			if ((740 > pos.x) && (pos.x > 540) && (377 > pos.y) && (pos.y > 310)) { cout << " ti pidor "; gamestate = 4; } //������ ����
		if (Mouse::isButtonPressed(Mouse::Button::Left))
			if ((400 > pos.x) && (pos.x > 200) && (377 > pos.y) && (pos.y > 310)) { cout << " ti pidor "; } //���������
		if (Mouse::isButtonPressed(Mouse::Button::Left))
			if ((1080 > pos.x) && (pos.x > 880) && (377 > pos.y) && (pos.y > 310)) { window.close(); } //����� �� ����
	
		Event event; //������� ������ ������ �������
		if (window.pollEvent(event)) //�������� �������� ����
		{
			if (event.type == Event::Closed) window.close();
		}
		if (Keyboard::isKeyPressed(Keyboard::Escape)) { window.close(); }
		if (Mouse::isButtonPressed(Mouse::Button::Left) == false) { pressedbut = 0; } // �������� ���������� ������� �� �������
		else pressedbut = 1;
	}
	return 0;
}


