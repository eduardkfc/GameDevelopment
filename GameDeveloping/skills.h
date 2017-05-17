#pragma once
#include "Header.h"
void doubledamage(int &ddtime,bool &activeDD,Clock &DDtimer,bool &ddcooldown,Bullet &bullet)
{
	if (Keyboard::isKeyPressed(Keyboard::Q) && activeDD == false && ddcooldown == false)
	{
		activeDD = true;
		DDtimer.restart();
	}
	if (activeDD == true)
	{
		ddtime = DDtimer.getElapsedTime().asSeconds();
		//cout << ddtime << endl;
		if (ddtime == 0) 
		{ 
			bullet.setDamage(10); 
			cout << bullet.getDamage() << " Bullet dmg" << endl; 
		}
		if (ddtime == 5)
		{
			DDtimer.restart();
			activeDD = false;
			cout << "DOUBLE DAMAGE IS OFF" << endl;
			ddcooldown = true;
			cout << "COOLDOWN - 7 sec" << endl;
		}
	}
	if (ddcooldown == true)
	{
		ddtime = DDtimer.getElapsedTime().asSeconds();
		
		if (ddtime == 7)
		{
			ddcooldown = false;
			cout << "COOLDOWN FINISHED" << endl;
		}
	}
}
void speed(int &speedtime, bool &activeSpeed, Clock &Speedtimer, bool &speedcooldown, Player &p1)
{
	if (Keyboard::isKeyPressed(Keyboard::E) && activeSpeed == false && speedcooldown == false)
	{
		activeSpeed = true;
		Speedtimer.restart();
	}
	if (activeSpeed == true)
	{
		speedtime = Speedtimer.getElapsedTime().asSeconds();
		cout << speedtime << endl;
		if ( speedtime == 0)
		{
			p1.setSpeed(0.15);
			cout << p1.getSpeed() << " Player speed " << endl;
		}
		if ( speedtime == 2)
		{
			Speedtimer.restart();
			activeSpeed = false;
			cout << "SUPER SPEED IS OFF" << endl;
			p1.setSpeed(0.1);
			speedcooldown = true;
			cout << "COOLDOWN - 4 sec" << endl;
		}
	}
	if (speedcooldown == true)
	{
		speedtime = Speedtimer.getElapsedTime().asSeconds();

		if (speedtime == 4)
		{
			speedcooldown = false;
			cout << "COOLDOWN FINISHED" << endl;
		}
	}
}