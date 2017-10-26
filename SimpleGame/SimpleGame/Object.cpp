#include "stdafx.h"
#include "Object.h"


Object::Object() : x(0), y(0), z(0), size(0), r(0), g(0), b(0), a(0) {};

Object::Object(float _x, float _y, float _z, float _size, float _r, float _g, float _b, float _a)
	: x(_x), y(_y), z(_z), size(_size), r(_r), g(_g), b(_b), a(_a), speedX(rand() / (float)RAND_MAX * 0.1f), speedY(rand() / (float)RAND_MAX * 0.1f) { }


Object::~Object() { }

/* Setter / Getter */
void Object::setSize(float _size) { size = _size; }
float Object::getSize() { return size; }

void Object::setPositionX(float _x) { x = _x;  }
float Object::getPositionX() { return x; }

void Object::setPositionY(float _y) { y = _y; }
float Object::getPositionY() { return y; }

void Object::setPositionZ(float _z) { z = _z; }
float Object::getPositionZ() { return z; }

void Object::setSpeedX(float _speedX) { speedX = _speedX;  }
float Object::getSpeedX() { return speedX; }

void Object::setSpeedY(float _speedY) { speedY = _speedY;  }
float Object::getSpeedY() { return speedY; }


void Object::setColor(Color& color)
{
	r = color.r;
	g = color.g;
	b = color.b;
	a = color.a;
};

Color& Object::getColor()
{
	Color color = { r, g, b, a };
	return color;
}

bool Object::intersect(Object* obj)
{
	return (
		x - size < obj->x + obj->size &&
		x + size > obj->x - obj->size &&
		y - size < obj->y + obj->size &&
		y + size > obj->y - obj->size
		);
}

bool Object::isDead()
{
	return dead;
}

void Object::attacked(float damage)
{
	life -= damage;
}

