#include "Header.h" //���������� header

using namespace sf; //������� ������������� sf::
using namespace std; //������� ������������� std::

int main() //������� ������� ����
{
	
	RenderWindow window(VideoMode(1280,720), "Reflex Strike",Style::Close); //�������������� ����
	view.reset(FloatRect(0, 0, 1280, 720)); //������������ ������
	
	
	window.setVerticalSyncEnabled(true); //��������� ������������ �������������
	Level map; //������� ������ ������ �����
	map.LoadFromFile("map.xml"); //������ ���� �����
	Player p1("soldier1.png", 500, 500, map, 1); //������� ������ ������ �����
	Player p2("soldier1.png", 600, 600, map, 2); //������� ������ ������ �����
	vector <Bullet> bullets1pl; //������ ����
	float time; //������� ���������� ��� �������� �������� ����
	Vector2i Pixelpos; //���������� ��� ��������� ��������������� ����
	Vector2f pos; //���������� ��� �������� ��������� ��������� ����
	Clock clock; //������� ������ ������ �������, ��� ������� �������� ����
	int pressedbut = 0; //���������� ��� �������� ������� ������ ����
	
	while (window.isOpen()) //����, ���� ������� ����, �� ���������
	{
		time = clock.getElapsedTime().asMicroseconds(); //��������� ������� � �������������
		clock.restart(); //������������� �����
		time = time / 150; //������ ����� �������� ����
		Bullet bullet("bullet.png", p1.getSpritePos().x, p1.getSpritePos().y, p1.getSpriteOrigin(), pos, time);
		Event event; //������� ������ ������ �������

		Pixelpos = Mouse::getPosition(window); //��������� �������� ��������������� ����
		pos = window.mapPixelToCoords(Pixelpos); //��������������� � ���������� ��������� ����
		if (window.pollEvent(event)) //�������� �������� ����
		{
			if (event.type == Event::Closed)
				window.close();
		}
		if (Keyboard::isKeyPressed(Keyboard::Escape)) { window.close(); }
		
		if (Mouse::isButtonPressed(Mouse::Button::Left) && pressedbut == 0) //�������� ���������� ������� �� ������� ����
		{
			pressedbut = 1;
			bullets1pl.push_back(bullet);
		}

		if (Mouse::isButtonPressed(Mouse::Button::Left) == false) { pressedbut = 0; } // �������� ���������� ������� �� �������

		else pressedbut = 1;

		p1.moving(time, pos, window);


//---����� �� �����------------------
		window.clear(); //���������� ������
		getPosForPlayer(p1.getSpritePos().x, p1.getSpritePos().y);
		window.setView(view);
		map.Draw(window); //����� � ���������� �����
		window.draw(p1.sprite); //����� � ���������� ������� ������
		window.draw(p2.sprite); //����� � ���������� ������� ������
		for(int i=0;i<bullets1pl.size();i++) // ����� � ���������� ����
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

	return 0;
}


