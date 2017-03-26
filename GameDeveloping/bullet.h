#pragma once
#include "Header.h"
class Bullet 
{
private:
	float x,y,w,h,speed,bulletrot,damage;
	Vector2f direction;
	String File;
	Image image;
	Texture texture;
public:
	Sprite sprite;
	Bullet(String F)
	{
		damage = 10;
		speed = 0.5;
		w = 15;
		h = 5;
		File = F;
		texture.loadFromFile(File);
		sprite.setTexture(texture);
		texture.setSmooth(true);
		
	}
	void update(float &time)
	{
		x += (cos(bulletrot / 180* 3.14159265)*speed)*time;
		y += (sin(bulletrot / 180 * 3.14159265)*speed)*time;
		sprite.setPosition(x, y);
	}
	void updateDatas(int X, int Y, Vector2f &origin, Vector2f &pos)
	{
		x = X;
		y = Y;
		bulletrot = (atan2(pos.y - sprite.getPosition().y, pos.x - sprite.getPosition().x) * 180 / 3.14159265) - 4;
		sprite.setOrigin(origin.x - 80, origin.y - 75);
		sprite.setRotation(bulletrot);
		sprite.setPosition(x, y);
	}
	Vector2f getBulletSprPos() { return sprite.getPosition(); }
	FloatRect getBulletRect() { return FloatRect(x, y, w, h); }
};