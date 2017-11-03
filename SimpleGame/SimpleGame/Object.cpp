#include "stdafx.h"
#include "Object.h"


Object::Object(float _x, float _y, int _type) : x(_x), y(_y), z(0), a(1), type(_type)
{
	init();
}

Object::~Object()
{
	std::cout << "객체 삭제 완료" << std::endl;
}

void Object::init()
{
	angle = rand() % 360;
	lifeTime = 1000 + rand() % 1000;
	std::cout << lifeTime << std::endl;

	switch (type)
	{
	case OBJECT_BUILDING:
		size = 50;
		life = 500;
		setSpeed(0);
		r = 1; g = 1; b = 0;
		break;
	case OBJECT_CHARACTER:
		size = 10;
		life = 10;
		setSpeed(300);
		r = 1; g = 1; b = 1;
		break;
	case OBJECT_BULLET:
		size = 2;
		life = 20;
		setSpeed(600);
		r = 1; g = 0; b = 0;
		break;
	case OBJECT_ARROW:
		size = 2;
		life = 10;
		setSpeed(100);
		r = 0; g = 1; b = 0;
		break;
	}

	
}

/* Setter / Getter */
void Object::setSize(float _size) { size = _size; }
float Object::getSize() { return size; }

void Object::setPositionX(float _x) { x = _x;  }
float Object::getPositionX() { return x; }

void Object::setPositionY(float _y) { y = _y; }
float Object::getPositionY() { return y; }

float Object::getTime() { return elapsedTime; }
void Object::setTime(float _time) { elapsedTime = _time; }

float Object::getLife() { return life; }

void Object::setSpeed(float speed)
{
	speedX = speedY = speed;
}


bool Object::intersect(Object* obj)
{
	return (
		x - size / 2 < obj->x + obj->size / 2 &&
		x + size / 2 > obj->x - obj->size / 2 &&
		y - size / 2 < obj->y + obj->size / 2 &&
		y + size / 2 > obj->y - obj->size / 2
		);
}


void Object::attacked(float damage)
{
	life -= damage;
}

bool Object::isDead()
{
	return lifeTime < 0;
}

void Object::update(float elapsed)
{
	elapsedTime += elapsed;		
	lifeTime -= elapsed;

	if (x < -250 || x > 250)
		speedX *= -1;
	
	if (y < -250 || y > 250)
		speedY *= -1;
	
	x += cos(angle) * speedX * 0.0001;
	y += sin(angle) * speedY * 0.0001;
}

void Object::render(Renderer* renderer)
{
	renderer->DrawSolidRect(x, y, z, size, r, g, b, a);
}

