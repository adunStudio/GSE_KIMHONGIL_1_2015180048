#include "stdafx.h"
#include "Locker.h"


Locker::Locker(float _x, float _y, float _z, float _size, float _r, float _g, float _b, float _a)
	: Node(_x, _y, _z, _size, _r, _g, _b, _a){}


Locker::~Locker()
{
	cout << "삭제되었습니다. \n";
}

void Locker::update() {

	x += moveX;
	y += moveY;
};

void Locker::render(Renderer* renderer) {
	renderer->DrawSolidRect(x, y, z, size, r, g, b, a);
};