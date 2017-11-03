#pragma once

#include "Renderer.h"

struct Color
{
	float r, g, b, a;
};

#define OBJECT_BUILDING  0
#define OBJECT_CHARACTER 1
#define OBJECT_BULLET    2
#define OBJECT_ARROW     3

class Object
{
private:
	float x, y, z;
	float size;
	int type;
	float r, g, b, a;
	float speedX, speedY;
	float life;
	float lifeTime = 0;
	float elapsedTime = 0;
	float angle;

private:
	void init();

public:
	Object(float _x, float _y, int _type);
	~Object();

	void Object::setSpeed(float speed);

	void setPositionX(float _x);
	float getPositionX();

	void setPositionY(float _y);
	float getPositionY();

	void setSize(float _size);
	float getSize();

	float getTime();
	void setTime(float _time);

	float getLife();

	bool isDead();

	void update(float elapsed);

	void render(Renderer* renderer);

	bool intersect(Object* obj);

	void attacked(float damage);
};

