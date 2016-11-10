#include "Header.h" //���������� header

using namespace sf; //������� ������������� sf
using namespace std; //������� ������������� std

int main() //������� ������� ����
{
	RenderWindow window(VideoMode(1366,768), "HUYHUY",Style::None); //�������������� ����
	window.setVerticalSyncEnabled(true);
	View view2; //������� ������ ������ ������
	Player p1("soldier1.png", 500, 500); //������� ������ ������ �����
	Player p2("soldier1.png", 600, 600);
	vector <Bullet> bullets1pl;
	float time; //������� ���������� ��� �������� �������� ����
	Vector2i Pixelpos; //���������� ��� ��������� ��������������� ����
	Vector2f pos; //���������� ��� �������� ��������� ��������� ����
	float rotation; //���������� �������������� ������ �����
	float bulletrot;
	float deX = 0; //���������� ������ ��� �������� ����� ������ ����� ���
	float deY = 0; //���������� ������ ��� �������� ����� ������ ����� ���
	Clock clock; //������� ������ ������ �������, ��� ������� �������� ����
	float �urrentFrame = 0; // �������� ������� �������� ���������

	Level map; //������� ������ ������ �����
	map.LoadFromFile("map.xml"); //������ ���� �����
	int pressedbut = 0;
	Vector2f heropos = p1.getSpritePos(); //������ �������������� ���������
	view2.setCenter(heropos.x, heropos.y); //������ ��������� ������ �� ������� �����
	view2.setSize(1366, 768); //������ ������ ���� ��� ������
	while (window.isOpen()) //����, ���� ������� ����, �� ���������
	{
		
		time = clock.getElapsedTime().asMicroseconds(); //��������� ������� � �������������
		clock.restart(); //������������� �����
		time = time / 150; //������ ����� �������� ����
		Event event; //������� ������ ������ �������
		
		Pixelpos = Mouse::getPosition(window); //��������� �������� ��������������� ����
		pos = window.mapPixelToCoords(Pixelpos); //��������������� � ���������� ��������� ����
		heropos = p1.getSpritePos(); // �������� ��������� ���������
		deX = pos.x - heropos.x; //- p.x;������ , ����������� ������, ������� ���������� ������ � ������
		deY = pos.y - heropos.y; //- p.y;�� ��, ���������� y
		rotation = (atan2(deY, deX)) * 180 / 3.14159265;//�������� ���� � �������� � ��������� ��� � �������
		
		p1.setSpriteRotation(rotation+85);//������������ ������ �� ��� �������
		
		
		if (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}
		
		
//----------------�������� �������------------------------------
//----------------�������� ������� ������-----------------------

		if (Keyboard::isKeyPressed(Keyboard::A) && Keyboard::isKeyPressed(Keyboard::W))
		{
			�urrentFrame += 0.002*time; //������ ��� ����������� �� "������". ���������� ������� �� ���� �������� ������������ ������� � ��������. ������� 0.005 ����� �������� �������� ��������
			if (�urrentFrame > 6) �urrentFrame -= 6; // ���� ������ � �������� ����� - ������������ �����.
			p1.setSpriteRect(int(�urrentFrame));
			p1.moveSprite(((-p1.getSpeed())*time)*0.75 , ((-p1.getSpeed())*time)*0.75 ); view2.move(((-p1.getSpeed())*time)*0.75, ((-p1.getSpeed())*time)*0.75);
			
		}
		else if (Keyboard::isKeyPressed(Keyboard::W) && Keyboard::isKeyPressed(Keyboard::D))
		{
			�urrentFrame += 0.002*time; //������ ��� ����������� �� "������". ���������� ������� �� ���� �������� ������������ ������� � ��������. ������� 0.005 ����� �������� �������� ��������
			if (�urrentFrame > 6) �urrentFrame -= 6; // ���� ������ � �������� ����� - ������������ �����.
			p1.setSpriteRect(int(�urrentFrame));
			p1.moveSprite(((p1.getSpeed())*time) *0.75, ((-p1.getSpeed())*time)*0.75 ); view2.move(((p1.getSpeed())*time)*0.75, ((-p1.getSpeed())*time)*0.75);
			
		}
		else if (Keyboard::isKeyPressed(Keyboard::D) && Keyboard::isKeyPressed(Keyboard::S))
		{
			�urrentFrame += 0.002*time; //������ ��� ����������� �� "������". ���������� ������� �� ���� �������� ������������ ������� � ��������. ������� 0.005 ����� �������� �������� ��������
			if (�urrentFrame > 6) �urrentFrame -= 6; // ���� ������ � �������� ����� - ������������ �����.
			p1.setSpriteRect(int(�urrentFrame));
			p1.moveSprite(((p1.getSpeed())*time)*0.75, ((p1.getSpeed())*time)*0.75); view2.move(((p1.getSpeed())*time)*0.75, ((p1.getSpeed())*time)*0.75);
			
		}
		else if (Keyboard::isKeyPressed(Keyboard::S) && Keyboard::isKeyPressed(Keyboard::A))
		{
			�urrentFrame += 0.002*time; //������ ��� ����������� �� "������". ���������� ������� �� ���� �������� ������������ ������� � ��������. ������� 0.005 ����� �������� �������� ��������
			if (�urrentFrame > 6) �urrentFrame -= 6; // ���� ������ � �������� ����� - ������������ �����.
			p1.setSpriteRect(int(�urrentFrame));
			p1.moveSprite(((-p1.getSpeed())*time)*0.75, ((p1.getSpeed())*time)*0.75); 
			view2.move(((-p1.getSpeed())*time)*0.75, ((p1.getSpeed())*time)*0.75);
			
		}
		else if (Keyboard::isKeyPressed(Keyboard::A))
		{
			�urrentFrame += 0.002*time; //������ ��� ����������� �� "������". ���������� ������� �� ���� �������� ������������ ������� � ��������. ������� 0.005 ����� �������� �������� ��������
			if (�urrentFrame > 6) �urrentFrame -= 6; // ���� ������ � �������� ����� - ������������ �����.
			p1.setSpriteRect(int(�urrentFrame));
			p1.moveSprite(((-p1.getSpeed())*time), 0);
			view2.move(((-p1.getSpeed())*time), 0);
		}
		else if (Keyboard::isKeyPressed(Keyboard::W))
		{
			�urrentFrame += 0.002*time; //������ ��� ����������� �� "������". ���������� ������� �� ���� �������� ������������ ������� � ��������. ������� 0.005 ����� �������� �������� ��������
			if (�urrentFrame > 6) �urrentFrame -= 6; // ���� ������ � �������� ����� - ������������ �����.
			p1.setSpriteRect(int(�urrentFrame));
			p1.moveSprite(0, ((-p1.getSpeed())*time));
			view2.move(0, ((-p1.getSpeed())*time));
		}
		else if (Keyboard::isKeyPressed(Keyboard::S))
		{
			
			�urrentFrame += 0.002*time; //������ ��� ����������� �� "������". ���������� ������� �� ���� �������� ������������ ������� � ��������. ������� 0.005 ����� �������� �������� ��������
			if (�urrentFrame > 6) �urrentFrame -= 6; // ���� ������ � �������� ����� - ������������ �����.
			p1.setSpriteRect(int(�urrentFrame));
			p1.moveSprite(0, ((p1.getSpeed())*time));
			view2.move(0, ((p1.getSpeed())*time));
		}
		else if (Keyboard::isKeyPressed(Keyboard::D))
		{
			�urrentFrame += 0.002*time; //������ ��� ����������� �� "������". ���������� ������� �� ���� �������� ������������ ������� � ��������. ������� 0.005 ����� �������� �������� ��������
			if (�urrentFrame > 6) �urrentFrame -= 6; // ���� ������ � �������� ����� - ������������ �����.
			p1.setSpriteRect(int(�urrentFrame));
			p1.moveSprite(((p1.getSpeed())*time), 0);
			view2.move(((p1.getSpeed())*time), 0);
			
		}
		else
		{
			�urrentFrame = 0;
			p1.setSpriteRect(int(�urrentFrame));
		}
//----------�������� ������� ������--------------------------------------

//----------�������� �������---------------------------------------------
//----------�������� ������� ������--------------------------------------
		
		if (Mouse::isButtonPressed(Mouse::Button::Left) && pressedbut == 0)
		{
			pressedbut = 1;
			Bullet bullet("bullet.png", p1.getSpritePos().x, p1.getSpritePos().y,p1.getSpriteOrigin(), pos);
			bullets1pl.push_back(bullet);
			
			
		}
		if (Mouse::isButtonPressed(Mouse::Button::Left) == false) { pressedbut = 0; }
		else pressedbut = 1;
		for (int i = 0; i<bullets1pl.size(); i++)
		{ 
			bullets1pl[i].update();
			if (bullets1pl[i].getBulletSprPos().x > 960 || bullets1pl[i].getBulletSprPos().y > 1280) 
			{ 
				bullets1pl.pop_back(); 
			}
			else if (bullets1pl[i].getBulletSprPos().x < 0 || bullets1pl[i].getBulletSprPos().y < 0)
			{
				bullets1pl.pop_back();
			}
		}
//----------�������� ������� ������--------------------------------------

//---����� �� �����------------------
		
		window.clear();

		map.Draw(window);
		window.setView(view2);
		window.draw(p1.sprite);
		window.draw(p2.sprite);
		for(int i=0;i<bullets1pl.size();i++)
			window.draw(bullets1pl[i].sprite);
		window.display();

	}

	return 0;
}
