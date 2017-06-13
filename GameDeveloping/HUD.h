#pragma once
#include "Header.h"
class HUD
{
private:
	RectangleShape myrect;
	RectangleShape myrectBack;
	RectangleShape Enemyrect;
	RectangleShape EnemyrectBack;
	Vector2f pos;
	Vector2f p1size;
	Vector2f p2size;
	Font font;
	Text Healthtext;
	Text EnemyHealthtext;
	Color c;
	int maxW;
	int max, p1HP, p2HP;
	string convertHP,convertEnHP, convertDD, convertSS;
	Texture ddIco, ssIco, ddCD,ssCD;
	Sprite ddIcon, ssIcon,ddCooldown,ssCooldown;
	Text workDD, workSS;
public:
	HUD()
	{
		ddIco.loadFromFile("images/doubledamage.jpg");
		ssIco.loadFromFile("images/superspeed.jpg");
		ddCD.loadFromFile("images/damagecd.jpg");
		ssCD.loadFromFile("images/speedcd.jpg");
		font.loadFromFile("font.ttf");
		c = Color::Green;
		max = 100; maxW = 100;
		pos.x = 500; pos.y = 500;
		p1size.y = 15; p1size.x = 100;
		p2size.y = 15; p2size.x = 100;
		myrect.setPosition(pos.x, pos.y);
		myrect.setFillColor(c);
		myrectBack.setPosition(pos.x, pos.y);
		myrectBack.setSize(p1size);
		myrectBack.setOutlineThickness(2);
		Healthtext.setCharacterSize(15);
		Healthtext.setFont(font);
		myrectBack.setOutlineColor(Color::Black);

		Enemyrect.setPosition(pos.x, pos.y);
		Enemyrect.setFillColor(c);
		EnemyHealthtext.setCharacterSize(15);
		EnemyrectBack.setPosition(pos.x, pos.y);
		EnemyrectBack.setSize(p2size);
		EnemyrectBack.setOutlineThickness(2);
		EnemyrectBack.setOutlineColor(Color::Black);
		EnemyHealthtext.setFont(font);

		ddIcon.setTexture(ddIco);
		ssIcon.setTexture(ssIco);
		ddCooldown.setTexture(ddCD);
		ssCooldown.setTexture(ssCD);
		
		workDD.setFont(font);
		workSS.setFont(font);
		workDD.setOutlineThickness(1);
		workSS.setOutlineThickness(1);
		workDD.setOutlineColor(Color::Black);
		workSS.setOutlineColor(Color::Black);
	}
	void draw(RenderWindow &window, Player &p1,Player &p2)
	{
		p1HP = p1.getHealth();
		p2HP = p2.getHealth();
		p1size.x = (p1HP*maxW) / max;
		p2size.x = (p2HP*maxW) / max;
		myrect.setSize(p1size);
		Enemyrect.setSize(p2size);
		myrect.setPosition(p1.getSpritePos().x-45, p1.getSpritePos().y-90);
		Enemyrect.setPosition(p2.getSpritePos().x - 45, p2.getSpritePos().y - 90);
		myrectBack.setPosition(p1.getSpritePos().x-45, p1.getSpritePos().y-90);
		EnemyrectBack.setPosition(p2.getSpritePos().x - 45, p2.getSpritePos().y - 90);
		convertHP = to_string(p1HP);
		convertEnHP = to_string(p2HP);
		if (p1.getDDcooldown() == true) { convertDD = to_string(float(7.0 - float(p1.getDDtime())/1000)); }
		else convertDD = to_string(float(5.0 - float(p1.getDDtime())/1000));
		convertDD.erase(3);
		if (p1.getSScooldown() == true) { convertSS = to_string(float(4.0 - float(p1.getSpeedtime())/1000)); }
		else convertSS = to_string(float(2.0 - float(p1.getSpeedtime())/1000));
		convertSS.erase(3);
		workDD.setString(convertDD);
		workSS.setString(convertSS);
		Healthtext.setString(convertHP);
		EnemyHealthtext.setString(convertEnHP);
		Healthtext.setPosition(p1.getSpritePos().x -5 , p1.getSpritePos().y - 90);
		EnemyHealthtext.setPosition(p2.getSpritePos().x - 5, p2.getSpritePos().y - 90);
		ddIcon.setPosition(p1.getSpritePos().x + 500, p1.getSpritePos().y + 90);
		ddCooldown.setPosition(p1.getSpritePos().x + 500, p1.getSpritePos().y + 90);
		ssIcon.setPosition(p1.getSpritePos().x + 500, p1.getSpritePos().y + 180);
		ssCooldown.setPosition(p1.getSpritePos().x + 500, p1.getSpritePos().y + 180);
		workDD.setPosition(p1.getSpritePos().x + 515, p1.getSpritePos().y + 110);
		workSS.setPosition(p1.getSpritePos().x + 515, p1.getSpritePos().y + 200);
		
		if (p1HP < 70) { Healthtext.setFillColor(Color::Black); }
		if (p1HP < 30) { Healthtext.setFillColor(Color::Red); }
		if (p2HP < 70) { EnemyHealthtext.setFillColor(Color::Black); }
		if (p2HP < 30) { EnemyHealthtext.setFillColor(Color::Red); }

		window.draw(myrectBack);
		window.draw(myrect);
		window.draw(Healthtext);
		window.draw(EnemyrectBack);
		window.draw(Enemyrect);
		window.draw(EnemyHealthtext);
		if (p1.getDDcooldown() == true) { window.draw(ddCooldown); window.draw(workDD); }
		if (p1.getDDcooldown() == false) window.draw(ddIcon);
		if (p1.getSScooldown() == true) { window.draw(ssCooldown); window.draw(workSS); }
		if (p1.getSScooldown() == false) window.draw(ssIcon);
		if (p1.getActiveDD() == true) { window.draw(workDD); }
		if (p1.getActiveSS() == true) { window.draw(workSS); }
	}
};