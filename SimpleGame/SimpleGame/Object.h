#pragma once

#include "Renderer.h"
#include "define.h"
#include <vector>

using namespace std;

struct Color
{
	float r, g, b, a;
};


class Object
{
private:
	float x, y, z;
	float size;
	int type;
	float r, g, b, a;
	float speedX, speedY;
	float m_maxLife = 0;
	float life;
	float lifeTime = 0;
	float elapsedTime = 0;
	float angle;
	int texture = -1;
	float m_drawLevel = 0;
	int frame = 0;
	float frameTime = 0;

	Object* parent = nullptr;
	vector<Object*> children;

public:
	int team;

private:
	void init();

public:
	Object(float _x, float _y, int _type, int _team);
	~Object();

	void Object::setSpeed(float speed);

	void setPositionX(float _x);
	float getPositionX();

	void setPositionY(float _y);
	float getPositionY();

	void setSize(float _size);
	float getSize();

	void setParent(Object* _parent);
	Object* getParent();

	void addChild(Object* child);

	float getTime();
	void setTime(float _time);

	float getLife();

	bool isDead();

	void update(float elapsed);

	void render(Renderer* renderer);

	bool intersect(Object* obj);

	void attacked(float damage);
};

