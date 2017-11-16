#include "stdafx.h"
#include "Object.h"


Object::Object(float _x, float _y, int _type, int _team)
	: x(_x), y(_y), z(0), a(1), type(_type), team(_team)
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
	lifeTime = 100;

	switch (type)
	{
	case OBJECT_BUILDING:
		size = 50;
		life = 5;
		setSpeed(0);
		r = 1; g = 1; b = 0;
		break;
	case OBJECT_CHARACTER:
		size = 10;
		life = 10;
		setSpeed(300);
		if (team == RED_TEAM) { r = 1; g = 0; b = 0; }
		else { r = 1; g = 0; b = 1; }
		break;
	case OBJECT_BULLET:
		size = 2;
		life = 20;
		setSpeed(600);
		if (team == RED_TEAM){r = 1; g = 0; b = 0;}
		else                 {r = 1; g = 0; b = 1;}
		break;
	case OBJECT_ARROW:
		size = 2;
		life = 10;
		setSpeed(100);
		if (team == RED_TEAM) { r = 0.5; g = 0.2; b = 0.7; }
		else { r = 1; g = 1; b = 0; }
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

void Object::setParent(Object* _parent)
{
	parent = _parent;
}

Object* Object::getParent()
{
	return parent;
}

void Object::addChild(Object* child)
{
	children.push_back(child);
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

	if (x < -WIDTH/2 || x > WIDTH/2)
		speedX *= -1;
	
	if (y < -HEIGHT/2 || y > HEIGHT/2)
		speedY *= -1;
	
	x += cos(angle) * speedX * 0.0005;
	y += sin(angle) * speedY * 0.0005;
}

void Object::render(Renderer* renderer)
{
	if (type == OBJECT_BUILDING) 
	{
		if (texture < 0)
		{
			switch (team)
			{
				case RED_TEAM:
					texture = renderer->CreatePngTexture("./resource/red_team2.png");
					break;

				case BLUE_TEAM:
					texture = renderer->CreatePngTexture("./resource/blue_team.png");
					break;
			}
		}
		renderer->DrawTexturedRect(x, y, 0, size, r, g, b, a, texture);
	}

	else
		renderer->DrawSolidRect(x, y, z, size, r, g, b, a);
}

