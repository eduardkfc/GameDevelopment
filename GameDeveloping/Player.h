#pragma once
#include"Header.h"
using namespace sf;
class Player
{
private:
	float x, y, dx, dy, speed, health;
	float СurrentFrame = 0; // Хранение текущей анимации персонажа

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
			СurrentFrame += 0.002*time; //служит для прохождения по "кадрам". переменная доходит до трех суммируя произведение времени и скорости. изменив 0.005 можно изменить скорость анимации
			if (СurrentFrame > 6) СurrentFrame -= 6; // если пришли к третьему кадру - откидываемся назад.
			setSpriteRect(int(СurrentFrame)); //Смена кадра анимации
			sprite.move(((-speed)*time)*0.75, ((-speed)*time)*0.75); //Движение персонажа

		}
		else if (Keyboard::isKeyPressed(Keyboard::W) && Keyboard::isKeyPressed(Keyboard::D))
		{
			СurrentFrame += 0.002*time; //служит для прохождения по "кадрам". переменная доходит до трех суммируя произведение времени и скорости. изменив 0.005 можно изменить скорость анимации
			if (СurrentFrame > 6) СurrentFrame -= 6; // если пришли к третьему кадру - откидываемся назад.
			setSpriteRect(int(СurrentFrame)); //Смена кадра анимации
			sprite.move(((speed)*time) *0.75, ((-speed)*time)*0.75); //Движение персонажа

		}
		else if (Keyboard::isKeyPressed(Keyboard::D) && Keyboard::isKeyPressed(Keyboard::S))
		{
			СurrentFrame += 0.002*time; //служит для прохождения по "кадрам". переменная доходит до трех суммируя произведение времени и скорости. изменив 0.005 можно изменить скорость анимации
			if (СurrentFrame > 6) СurrentFrame -= 6; // если пришли к третьему кадру - откидываемся назад.
			setSpriteRect(int(СurrentFrame));
			sprite.move(((speed)*time)*0.75, ((speed)*time)*0.75);
		}
		else if (Keyboard::isKeyPressed(Keyboard::S) && Keyboard::isKeyPressed(Keyboard::A))
		{
			СurrentFrame += 0.002*time; //служит для прохождения по "кадрам". переменная доходит до трех суммируя произведение времени и скорости. изменив 0.005 можно изменить скорость анимации
			if (СurrentFrame > 6) СurrentFrame -= 6; // если пришли к третьему кадру - откидываемся назад.
			setSpriteRect(int(СurrentFrame));
			sprite.move(((-speed)*time)*0.75, ((speed)*time)*0.75);
		}
		else if (Keyboard::isKeyPressed(Keyboard::A))
		{
			СurrentFrame += 0.002*time; //служит для прохождения по "кадрам". переменная доходит до трех суммируя произведение времени и скорости. изменив 0.005 можно изменить скорость анимации
			if (СurrentFrame > 6) СurrentFrame -= 6; // если пришли к третьему кадру - откидываемся назад.
			setSpriteRect(int(СurrentFrame));
			sprite.move(((-speed)*time), 0);
		}
		else if (Keyboard::isKeyPressed(Keyboard::W))
		{
			СurrentFrame += 0.002*time; //служит для прохождения по "кадрам". переменная доходит до трех суммируя произведение времени и скорости. изменив 0.005 можно изменить скорость анимации
			if (СurrentFrame > 6) СurrentFrame -= 6; // если пришли к третьему кадру - откидываемся назад.
			setSpriteRect(int(СurrentFrame));
			sprite.move(0, ((-speed)*time));
		}
		else if (Keyboard::isKeyPressed(Keyboard::S))
		{

			СurrentFrame += 0.002*time; //служит для прохождения по "кадрам". переменная доходит до трех суммируя произведение времени и скорости. изменив 0.005 можно изменить скорость анимации
			if (СurrentFrame > 6) СurrentFrame -= 6; // если пришли к третьему кадру - откидываемся назад.
			setSpriteRect(int(СurrentFrame));
			sprite.move(0, ((speed)*time));
		}
		else if (Keyboard::isKeyPressed(Keyboard::D))
		{
			СurrentFrame += 0.002*time; //служит для прохождения по "кадрам". переменная доходит до трех суммируя произведение времени и скорости. изменив 0.005 можно изменить скорость анимации
			if (СurrentFrame > 6) СurrentFrame -= 6; // если пришли к третьему кадру - откидываемся назад.
			setSpriteRect(int(СurrentFrame));
			sprite.move(((speed)*time), 0);
		}
		else
		{
			СurrentFrame = 0;
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