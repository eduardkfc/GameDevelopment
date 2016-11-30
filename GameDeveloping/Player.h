#pragma once
#include"Header.h"
using namespace sf;
class Player
{
private:
	float x, y, dx, dy, speed, health;
	float �urrentFrame = 0; // �������� ������� �������� ���������

	String File;
	Image image;
	Texture texture;
	
	
public:
	Sprite sprite;
	Player(String F, int X, int Y,int faction)
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

	void moving(float time)
	{
		if (Keyboard::isKeyPressed(Keyboard::A) && Keyboard::isKeyPressed(Keyboard::W))
		{
			�urrentFrame += 0.002*time; //������ ��� ����������� �� "������". ���������� ������� �� ���� �������� ������������ ������� � ��������. ������� 0.005 ����� �������� �������� ��������
			if (�urrentFrame > 6) �urrentFrame -= 6; // ���� ������ � �������� ����� - ������������ �����.
			setSpriteRect(int(�urrentFrame)); //����� ����� ��������
			sprite.move(((-speed)*time)*0.75, ((-speed)*time)*0.75); //�������� ���������

		}
		else if (Keyboard::isKeyPressed(Keyboard::W) && Keyboard::isKeyPressed(Keyboard::D))
		{
			�urrentFrame += 0.002*time; //������ ��� ����������� �� "������". ���������� ������� �� ���� �������� ������������ ������� � ��������. ������� 0.005 ����� �������� �������� ��������
			if (�urrentFrame > 6) �urrentFrame -= 6; // ���� ������ � �������� ����� - ������������ �����.
			setSpriteRect(int(�urrentFrame)); //����� ����� ��������
			sprite.move(((speed)*time) *0.75, ((-speed)*time)*0.75); //�������� ���������

		}
		else if (Keyboard::isKeyPressed(Keyboard::D) && Keyboard::isKeyPressed(Keyboard::S))
		{
			�urrentFrame += 0.002*time; //������ ��� ����������� �� "������". ���������� ������� �� ���� �������� ������������ ������� � ��������. ������� 0.005 ����� �������� �������� ��������
			if (�urrentFrame > 6) �urrentFrame -= 6; // ���� ������ � �������� ����� - ������������ �����.
			setSpriteRect(int(�urrentFrame));
			sprite.move(((speed)*time)*0.75, ((speed)*time)*0.75);
		}
		else if (Keyboard::isKeyPressed(Keyboard::S) && Keyboard::isKeyPressed(Keyboard::A))
		{
			�urrentFrame += 0.002*time; //������ ��� ����������� �� "������". ���������� ������� �� ���� �������� ������������ ������� � ��������. ������� 0.005 ����� �������� �������� ��������
			if (�urrentFrame > 6) �urrentFrame -= 6; // ���� ������ � �������� ����� - ������������ �����.
			setSpriteRect(int(�urrentFrame));
			sprite.move(((-speed)*time)*0.75, ((speed)*time)*0.75);
		}
		else if (Keyboard::isKeyPressed(Keyboard::A))
		{
			�urrentFrame += 0.002*time; //������ ��� ����������� �� "������". ���������� ������� �� ���� �������� ������������ ������� � ��������. ������� 0.005 ����� �������� �������� ��������
			if (�urrentFrame > 6) �urrentFrame -= 6; // ���� ������ � �������� ����� - ������������ �����.
			setSpriteRect(int(�urrentFrame));
			sprite.move(((-speed)*time), 0);
		}
		else if (Keyboard::isKeyPressed(Keyboard::W))
		{
			�urrentFrame += 0.002*time; //������ ��� ����������� �� "������". ���������� ������� �� ���� �������� ������������ ������� � ��������. ������� 0.005 ����� �������� �������� ��������
			if (�urrentFrame > 6) �urrentFrame -= 6; // ���� ������ � �������� ����� - ������������ �����.
			setSpriteRect(int(�urrentFrame));
			sprite.move(0, ((-speed)*time));
		}
		else if (Keyboard::isKeyPressed(Keyboard::S))
		{

			�urrentFrame += 0.002*time; //������ ��� ����������� �� "������". ���������� ������� �� ���� �������� ������������ ������� � ��������. ������� 0.005 ����� �������� �������� ��������
			if (�urrentFrame > 6) �urrentFrame -= 6; // ���� ������ � �������� ����� - ������������ �����.
			setSpriteRect(int(�urrentFrame));
			sprite.move(0, ((speed)*time));
		}
		else if (Keyboard::isKeyPressed(Keyboard::D))
		{
			�urrentFrame += 0.002*time; //������ ��� ����������� �� "������". ���������� ������� �� ���� �������� ������������ ������� � ��������. ������� 0.005 ����� �������� �������� ��������
			if (�urrentFrame > 6) �urrentFrame -= 6; // ���� ������ � �������� ����� - ������������ �����.
			setSpriteRect(int(�urrentFrame));
			sprite.move(((speed)*time), 0);
		}
		else
		{
			�urrentFrame = 0;
			sprite.setTextureRect(IntRect(0, 112, 62, 91));


		}
	}
	void moveSprite(float x, float y) { sprite.move(x, y); }
	Vector2f getSpritePos() { return sprite.getPosition(); }
	void setSpriteRotation(float rot) { sprite.setRotation(rot); }
	
	float getSpriteRotation(float rot) { return sprite.getRotation(); }
	Vector2f getSpriteOrigin() { return sprite.getOrigin(); }
	float getSpeed(){ return speed; }
	
};