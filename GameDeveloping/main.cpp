#include "Header.h" //���������� header

using namespace sf; //������� ������������� sf::
using namespace std; //������� ������������� std::

int main() //������� ������� ����
{
	RenderWindow window(VideoMode(1366,768), "HUYHUY",Style::None); //�������������� ����
	window.setVerticalSyncEnabled(true); //��������� ������������ �������������
	View view2; //������� ������ ������ ������
	Player p1("soldier1.png", 500, 500,1); //������� ������ ������ �����
	Player p2("soldier1.png", 600, 600,2); //������� ������ ������ �����
	vector <Bullet> bullets1pl; //������ ����
	float time; //������� ���������� ��� �������� �������� ����
	Vector2i Pixelpos; //���������� ��� ��������� ��������������� ����
	Vector2f pos; //���������� ��� �������� ��������� ��������� ����

	float bulletrot; //���������� �������������� ���� ����
	Clock clock; //������� ������ ������ �������, ��� ������� �������� ����

	Level map; //������� ������ ������ �����
	map.LoadFromFile("map.xml"); //������ ���� �����
	int pressedbut = 0; //���������� ��� �������� ������� ������ ����
	Vector2f heropos;
	view2.setSize(1366, 768); //������ ������ ���� ��� ������
	while (window.isOpen()) //����, ���� ������� ����, �� ���������
	{
		
		time = clock.getElapsedTime().asMicroseconds(); //��������� ������� � �������������
		clock.restart(); //������������� �����
		time = time / 150; //������ ����� �������� ����
		Bullet bullet("bullet.png", p1.getSpritePos().x, p1.getSpritePos().y, p1.getSpriteOrigin(), pos, time);
		Event event; //������� ������ ������ �������
		
		Pixelpos = Mouse::getPosition(window); //��������� �������� ��������������� ����
		pos = window.mapPixelToCoords(Pixelpos); //��������������� � ���������� ��������� ����
		heropos = p1.getSpritePos(); // �������� ��������� ���������
		view2.setCenter(heropos.x, heropos.y); //������ ��������� ������ �� ������� �����
		
		
		if (window.pollEvent(event)) //�������� �������� ����
		{
			if (event.type == Event::Closed)
				window.close();
		}
		
		
//----------------�������� �������------------------------------
//----------------�������� ������� ������-----------------------
		
		p1.moving(time,pos);
//----------�������� ������� ������--------------------------------------

//----------�������� �������---------------------------------------------
//----------�������� ������� ������--------------------------------------
		
		if (Mouse::isButtonPressed(Mouse::Button::Left) && pressedbut == 0)
		{
			pressedbut = 1;
			
			bullets1pl.push_back(bullet);
			
			
		}
		if (Mouse::isButtonPressed(Mouse::Button::Left) == false) { pressedbut = 0; }
		else pressedbut = 1;
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
//----------�������� ������� ������--------------------------------------

//---����� �� �����------------------
		
		window.clear(); //���������� ������
		map.Draw(window); //����� � ���������� �����
		window.setView(view2); // ����� � ���������� ������ ����
		window.draw(p1.sprite); //����� � ���������� ������� ������
		window.draw(p2.sprite); //����� � ���������� ������� ������
		for(int i=0;i<bullets1pl.size();i++) // ����� � ���������� ����
			window.draw(bullets1pl[i].sprite);
		window.display(); //������������� �������

	}

	return 0;
}
