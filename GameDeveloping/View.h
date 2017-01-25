#pragma once
#include "Header.h"

View view;
View getPosForPlayer(float x, float y)
{
	view.setCenter(x, y);
	return view;
}