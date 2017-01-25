#pragma once
#include"Header.h"
using namespace sf;

class Player
{
private:
	float x, y, w, h, dx, dy, speed, health;
	float СurrentFrame = 0; // Хранение текущей анимации персонажа
	float rotation; //Переменная поворачивающая нашего шероя
	float deX = 0; //Переменная служит для поворота героя вокруг своей оси
	float deY = 0; //Переменная служит для поворота героя вокруг своей оси
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
	void moving(float time,Vector2f mousepos,RenderWindow &windows)
	{
		//--------------------------------------------------------------------------------------------------------------
		deX = mousepos.x - sprite.getPosition().x; //- p.x;вектор , колинеарный прямой, которая пересекает спрайт и курсор
		deY = mousepos.y - sprite.getPosition().y; //- p.y;он же, координата y
		rotation = (atan2(deY, deX)) * 180 / 3.14159265; //получаем угол в радианах и переводим его в градусы
		sprite.setRotation(rotation + 85);//поворачиваем спрайт на эти градусы
		//--------------------------------------------------------------------------------------------------------------

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
	Vector2f getSpritePos() { return sprite.getPosition(); }
	Vector2f getSpriteOrigin() { return sprite.getOrigin(); }
	

};