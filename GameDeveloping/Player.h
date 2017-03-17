#pragma once
#include"Header.h"
using namespace sf;
using namespace std;


class Player
{
private:
	float x, y, w, h, dx, dy, speed, health;
	float �urrentFrame = 0; // �������� ������� �������� ���������
	float rotation; //���������� �������������� ������ �����
	float deX = 0; //���������� ������ ��� �������� ����� ������ ����� ���
	float deY = 0; //���������� ������ ��� �������� ����� ������ ����� ���
	float activeButtons = 0;
	bool wbut=false, abut=false, sbut=false, dbut = false;
	String File;
	Image image;
	Texture texture;
	
	
	
public:
	Sprite sprite;
	Player(String F, int X, int Y,Level &map,int faction)
	{ 
		speed = 0.1;
		sprite.setOrigin(65 - 30, 93 - 30);
		File = F;
		image.loadFromFile(File);
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		x = X; y = Y;
		sprite.setTextureRect(IntRect(0, 112, 62, 91));
		texture.setSmooth(true);
		sprite.setPosition(x, y);
	}
	
	void setSpriteRect(int curframe) { sprite.setTextureRect(IntRect(62 * curframe, 8, 62, 91)); }
	void moving(float time, Vector2f &pos, RenderWindow &windows, vector <Object> &obj)
	{
		//--------------------------------------------------------------------------------------------------------------
		deX = pos.x - sprite.getPosition().x; //- p.x;������ , ����������� ������, ������� ���������� ������ � ������
		deY = pos.y - sprite.getPosition().y; //- p.y;�� ��, ���������� y
		rotation = (atan2(deY, deX)) * 180 / 3.14159265; //�������� ���� � �������� � ��������� ��� � �������
		sprite.setRotation(rotation + 85);//������������ ������ �� ��� �������
		//--------------------------------------------------------------------------------------------------------------
		
		if (Keyboard::isKeyPressed(Keyboard::A))
		{
			animation(time);
			activeButtons += 1;
			abut = true;
			if (Keyboard::isKeyPressed(Keyboard::W))
			{
				wbut = true;
				activeButtons += 1;
				y -= ((speed)*time)*0.75;
				checkcollisions(0, -speed*0.75, time, obj);
			}
			else if (Keyboard::isKeyPressed(Keyboard::S))
			{
				sbut = true;
				activeButtons += 1;
				y += ((speed)*time)*0.75;
				checkcollisions(0, speed*0.75, time, obj);
			}
			if (activeButtons == 1) 
			{
				x -= (speed)*time; 
				checkcollisions(-speed, 0, time, obj);
			}
			else if (activeButtons == 2) 
			{
				x -= ((speed)*time)*0.75;
				checkcollisions(-speed*0.75, 0, time, obj);
			}
			
			
		}
		else if (Keyboard::isKeyPressed(Keyboard::S))
		{
			animation(time);
			activeButtons += 1;
			sbut = true;
			if (Keyboard::isKeyPressed(Keyboard::A))
			{
				abut = true;
				activeButtons += 1;
				x -= ((speed)*time)*0.75;
				checkcollisions(-speed*0.75, 0, time, obj);
			}
			else if (Keyboard::isKeyPressed(Keyboard::D))
			{
				dbut = true;
				activeButtons += 1;
				x += ((speed)*time)*0.75;
				checkcollisions(speed*0.75, 0, time, obj);
			}
			if (activeButtons == 1) 
			{ 
				y += (speed)*time; 
				checkcollisions(0, speed, time, obj);
			}
			else if (activeButtons == 2) 
			{
				y += ((speed)*time)*0.75; 
				checkcollisions(0, speed*0.75, time, obj);
			}
			
		}
		else if (Keyboard::isKeyPressed(Keyboard::D))
		{
			animation(time);
			activeButtons += 1;
			dbut = true;
			if (Keyboard::isKeyPressed(Keyboard::W))
			{
				wbut = true;
				activeButtons += 1;
				y -= ((speed)*time)*0.75;
				checkcollisions(0, -speed*0.75, time, obj);
			}
			else if (Keyboard::isKeyPressed(Keyboard::S))
			{
				sbut = true;
				activeButtons += 1;
				y += ((speed)*time)*0.75;
				checkcollisions(0, speed*0.75, time, obj);
			}
			if (activeButtons == 1) 
			{ 
				x += (speed)*time; 
				checkcollisions(speed, 0, time, obj);
			}
			else if (activeButtons == 2) 
			{
				x += ((speed)*time)*0.75;
				checkcollisions(speed*0.75, 0, time, obj);
			}
			
		}
		else if (Keyboard::isKeyPressed(Keyboard::W))
		{
			animation(time);
			activeButtons += 1;
			wbut = true;
			if (Keyboard::isKeyPressed(Keyboard::A))
			{
				abut = true;
				activeButtons += 1;
				x -= ((speed)*time)*0.75;
				checkcollisions(-speed*0.75, 0, time, obj);
			}
			else if (Keyboard::isKeyPressed(Keyboard::D))
			{
				dbut = true;
				activeButtons += 1;
				x += ((speed)*time)*0.75;
				checkcollisions(speed*0.75, 0, time, obj);
			}
			if (activeButtons == 1)
			{ 
				y -= ((speed)*time); 
				checkcollisions(0, -speed, time, obj);
			}
			else if (activeButtons == 2)
			{ 
				y -= ((speed)*time)*0.75;
				checkcollisions(0, -speed*0.75, time, obj);
			}
			
		}
		else sprite.setTextureRect(IntRect(0, 112, 62, 91)); activeButtons = 0;
		sprite.setPosition(x, y);
		wbut = false, abut = false, sbut = false, dbut = false;
		
	}
	void animation(float time)
	{
		�urrentFrame += 0.002*time; //������ ��� ����������� �� "������". ���������� ������� �� ���� �������� ������������ ������� � ��������. ������� 0.005 ����� �������� �������� ��������
		if (�urrentFrame > 6) �urrentFrame -= 6; // ���� ������ � �������� ����� - ������������ �����.
		setSpriteRect(int(�urrentFrame)); //����� ����� ��������
	}
	void checkcollisions(float Dx, float Dy, float time,vector <Object> &obj)
	{
		for (int i = 0; i<obj.size(); i++)//���������� �� ��������
			if (getRect().intersects(obj[i].rect))//��������� ����������� ������ � ��������
			{
				if (obj[i].name == "solid")//���� ��������� �����������
				{
					if (activeButtons == 1)
					{
						if (Dy > 0)
						{
							y -= (speed)*time;
						}
						if (Dy < 0)
						{
							y += (speed)*time;
						}
						if (Dx > 0)
						{
							x -= (speed)*time;
						}
						if (Dx < 0)
						{
							x += (speed)*time;
						}
					}
					if (activeButtons == 2)
					{
						if (Dy > 0)
						{
							y -= ((speed)*time)*0.75;
							if (dbut == true) { x += (speed*time) / 5; }
							else if (abut == true) { x -= (speed*time) / 5; }
						}
						else if (Dy < 0)
						{
							y += ((speed)*time)*0.75;
							if (dbut == true) { x += (speed*time) / 5; }
							else if (abut == true) { x -= (speed*time) / 5; }
						}
						else if (Dx > 0)
						{
							x -= ((speed)*time)*0.75;
							if (wbut == true) { y -= (speed*time) / 5; }
							else if (sbut == true) { y += (speed*time) / 5; }
						}
						else if (Dx < 0)
						{
							x += ((speed)*time)*0.75;
							if (wbut == true) { y -= (speed*time) / 5; }
							else if (sbut == true) { y += (speed*time) / 5; }

						}
					}
				}
			}
	}
	Vector2f getSpritePos() { return sprite.getPosition(); }
	Vector2f getSpriteOrigin() { return sprite.getOrigin(); }
	FloatRect getRect() { return FloatRect(x-30, y-30, 50, 60); }

};