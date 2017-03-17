#pragma once
#include "Header.h"
class Bullet 
{
private:
	float x,y,w,h,speed,bulletrot,velocity_x,velocity_y,intime,damage;
	Vector2f direction;
	String File;
	Image image;
	Texture texture;
public:
	Sprite sprite;
	Bullet(String F, int X, int Y,Vector2f origin,Vector2f mousepos,float time)
	{
		damage = 10;
		speed = 0.5;
		w = 15;
		h = 5;
		File = F;
		texture.loadFromFile(File);
		sprite.setTexture(texture);
		intime = time;
		x = X; y = Y;
		texture.setSmooth(true);
		sprite.setPosition(x, y);
		bulletrot = (atan2(mousepos.y - sprite.getPosition().y, mousepos.x - sprite.getPosition().x) * 180 / 3.14159265)-4;
		sprite.setOrigin(origin.x-80,origin.y-75);
		sprite.setRotation(bulletrot);
		
	}
	void update()
	{
		velocity_x = (cos(bulletrot / 180* 3.14159265)*speed)*intime;
		velocity_y = (sin(bulletrot / 180 * 3.14159265)*speed)*intime;
		sprite.move(velocity_x, velocity_y);
	}
	Vector2f getBulletSprPos() { return sprite.getPosition(); }
	FloatRect getBulletRect() { return FloatRect(x, y, w, h); }
};