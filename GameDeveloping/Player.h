#pragma once
#include"Header.h"



class Player
{
private:
	float x, y, w, h, speed;
	int  dx, dy;
	int health = 100;
	float �urrentFrame = 0; // �������� ������� �������� ���������
	float rotation; //���������� �������������� ������ �����
	float deX = 0; //���������� ������ ��� �������� ����� ������ ����� ���
	float deY = 0; //���������� ������ ��� �������� ����� ������ ����� ���
	float activeButtons = 0;
	bool collision;
	String File;
	Image image;
	Texture texture;
	Clock DDtimer;
	Clock Speedtimer;
	int ddtime, speedtime;
	bool activeDD = false, ddcooldown = false;
	bool activeSpeed = false, speedcooldown = false;
	
public:
	Sprite sprite;
	Player(Vector2f positions)
	{ 
		speed = 40;
		sprite.setOrigin(35, 63);
		texture.loadFromFile("soldier1.png");
		sprite.setTexture(texture);
		sprite.setTextureRect(IntRect(0, 112, 62, 91));
		texture.setSmooth(true);
		sprite.setPosition(positions);
	}
	void setSpriteRect(int curframe) { sprite.setTextureRect(IntRect(62 * curframe, 8, 62, 91)); }
	void moving(float &time, vector <Object> &obj, bool &pressedBut, vector <Bullet> &bulletsvector, Bullet &bullet, Maps &map,RenderWindow &window,Vector2f &MousePos,bool &myshot,float &p1rotation)
	{
		//--------------------------------------------------------------------------------------------------------------
		deX = MousePos.x - sprite.getPosition().x; //- p.x;������ , ����������� ������, ������� ���������� ������ � ������
		deY = MousePos.y - sprite.getPosition().y; //- p.y;�� ��, ���������� y
		rotation = (atan2(deY, deX)) * 180 / 3.14159265; //�������� ���� � �������� � ��������� ��� � �������
		sprite.setRotation(rotation + 85);//������������ ������ �� ��� �������
		//--------------------------------------------------------------------------------------------------------------
		if (Mouse::isButtonPressed(Mouse::Button::Left) && pressedBut == false) //�������� ���������� ������� �� ������� ����
		{

			pressedBut = true;
			myshot = true;
			bulletsvector.push_back(bullet);
			bulletsvector[bulletsvector.size() - 1].create(x, y, p1rotation);
		}
		if (Mouse::isButtonPressed(Mouse::Button::Left)) { pressedBut = true; } // �������� ���������� ������� �� �������
		else pressedBut = false;

		dx = 0; dy = 0;
		if (Keyboard::isKeyPressed(Keyboard::A))
			dx = -(speed)*time; 
		if (Keyboard::isKeyPressed(Keyboard::D))
			dx = (speed)*time; 
		if (Keyboard::isKeyPressed(Keyboard::W))
			dy = -(speed)*time;
		if (Keyboard::isKeyPressed(Keyboard::S))
			dy = (speed)*time;
		if (dy != 0 || dx != 0) { animation(time); }
		else sprite.setTextureRect(IntRect(0, 112, 62, 91)); activeButtons = 0;
		if (dy != 0 && dx != 0)
		{
			if (dx > 0) { dx = ((speed+20)*time)/2;  }
			else { dx = -((speed + 20)*time)/2;  }
			if (dy > 0) { dy = ((speed + 20)*time)/2; }
			else { dy = -((speed + 20)*time)/2; }
		}
		y += dy;
		x += dx;
		checkcollisions(dx, dy, time, obj);
		sprite.setPosition(x, y);
	}
	void animation(float time)
	{
		�urrentFrame += 0.8*time; //������ ��� ����������� �� "������". ���������� ������� �� ���� �������� ������������ ������� � ��������. ������� 0.005 ����� �������� �������� ��������
		if (�urrentFrame > 6) �urrentFrame -= 6; // ���� ������ � �������� ����� - ������������ �����.
		setSpriteRect(int(�urrentFrame)); //����� ����� ��������
	}
	void checkcollisions(int Dx, int Dy, float &time,vector <Object> &obj)
	{
		for (int i = 0; i < obj.size(); i++)//���������� �� ��������
		{
			if (getRect().intersects(obj[i].rect))//��������� ����������� ������ � ��������
			{
				collision = false;
				if (obj[i].name == "solid")//���� ��������� �����������
					collision = true;
				if (collision == true)
				{
					if (Dy > 0) { y += (-Dy); }
					if (Dy < 0) { y += (Dy*(-1)); }
					if (Dx > 0) { x += (-Dx); }
					if (Dx < 0) { x += (Dx*(-1)); }
				}
			}
		}
	}
	void skills(Bullet &bullet)
	{
		if (Keyboard::isKeyPressed(Keyboard::Q) && activeDD == false && ddcooldown == false)
		{
			activeDD = true;
			DDtimer.restart();
		}
		if (activeDD == true)
		{
			ddtime = DDtimer.getElapsedTime().asMilliseconds();
	
			if (ddtime >= 0)
			{
				bullet.setDamage(10);
			}
			if (ddtime >= 5000)
			{
				DDtimer.restart();
				activeDD = false;
				ddcooldown = true;
				bullet.setDamage(5);
			}
		}
		if (ddcooldown == true)
		{
			ddtime = DDtimer.getElapsedTime().asMilliseconds();

			if (ddtime >= 7000)
			{
				ddcooldown = false;
			}
		}

		if (Keyboard::isKeyPressed(Keyboard::E) && activeSpeed == false && speedcooldown == false)
		{
			activeSpeed = true;
			Speedtimer.restart();
		}
		if (activeSpeed == true)
		{
			speedtime = Speedtimer.getElapsedTime().asMilliseconds();
			if (speedtime >= 0)
			{
				speed = 60;
			}
			if (speedtime >= 2000)
			{
				Speedtimer.restart();
				activeSpeed = false;
				speed = 40;
				speedcooldown = true;
			}
		}
		if (speedcooldown == true)
		{
			speedtime = Speedtimer.getElapsedTime().asMilliseconds();

			if (speedtime >= 4000)
			{
				speedcooldown = false;
			}
		}
	}
	Vector2f getSpritePos() { return sprite.getPosition(); }
	Vector2f getSpriteOrigin() { return sprite.getOrigin(); }
	FloatRect getRect() { return FloatRect(x-30, y-30, 50, 60); }
	FloatRect getGlobalBounds() { return sprite.getGlobalBounds(); }
	void setPosition(float x, float y) { sprite.setPosition(x, y); }
	void setHealth(int healthint) { health = healthint; }
	int getHealth() { return health; }
	float getSpeed() { return speed; }
	void setSpeed(float xSpeed) { speed = xSpeed; }
	int getDDtime() { return ddtime; }
	int getSpeedtime() { return speedtime; }
	bool getActiveDD() { return activeDD; }
	bool getDDcooldown() { return ddcooldown; }
	bool getActiveSS() { return activeSpeed; }
	bool getSScooldown() { return speedcooldown; }
	float getRotation() { return sprite.getRotation(); }
	void startPosition(int host, int map)
	{
		if (map == 1)
		{
			if (host == 1) { x = 100; y = 100; }
			else if (host == 0) { x = 1113; y = 1495; }
		}
		else if (map == 2)
		{
			if (host == 1) { x = 119; y = 107; }
			else if (host == 0) { x = 813; y = 1154; }
		
		}
	}
};