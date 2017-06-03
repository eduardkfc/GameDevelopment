#pragma once
#include "Header.h"
class Bullet
{
private:
	float x, y, kekx, keky, w, h, speed, bulletrot, damage;
	Vector2f direction;
	String File;
	Image image;
	Texture texture;
public:
	Sprite sprite;
	Bullet()
	{
		damage = 5;
		speed = 120;
		w = 15;
		h = 5;
		texture.loadFromFile("bullet.png");
		sprite.setTexture(texture);
		texture.setSmooth(true);
		
	}
	void update(float &time)
	{
		x += (cos(bulletrot / 180 * 3.14159265)*speed)*time;
		y += (sin(bulletrot / 180 * 3.14159265)*speed)*time;
		sprite.setPosition(x, y);
	}
	void create(int X, int Y, float rotation)
	{
		x = X, y = Y;
		bulletrot = rotation - 88;
		sprite.setOrigin(35 - 80, 63 - 75);
		sprite.setRotation(bulletrot);
		sprite.setPosition(x, y);
	}
	Vector2f getBulletSprPos() { return sprite.getPosition(); }
	FloatRect getBulletRect() { return sprite.getGlobalBounds(); }
	int getDamage() { return damage; }
	void setDamage(int multiplier) { damage = multiplier; }
};