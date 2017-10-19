#include "stdafx.h"
#include "Locker.h"


Locker::Locker(float _x, float _y, float _z, float _size, float _r, float _g, float _b, float _a)
	: Object(_x, _y, _z, _size, _r, _g, _b, _a) 
{
	
}


Locker::~Locker()
{
	cout << "�����Ǿ����ϴ�. \n";
}

void Locker::update() 
{
	speedX = rand() % 3 * 0.3;
	speedY = rand() % 3 * 0.3;

	if (rand() % 2 == 1)
		speedX *= -1;

	if (rand() % 2 == 1)
		speedY *= -1;

	x += speedX;
	y += speedY;
};

void Locker::render(Renderer* renderer)
{
	renderer->DrawSolidRect(x, y, z, size, r, g, b, a);
};