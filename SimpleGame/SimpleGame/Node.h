#pragma once

#include "Renderer.h"

struct Color
{
	float r, g, b, a;
};

class Node
{
protected:
	float x, y, z;
	float size;
	float r, g, b, a;

public:
	Node();
	Node(float _x, float _y, float _z, float _size, float _r, float _g, float _b, float _a);
	~Node();

	void setPositionX(float _x);
	float getPositionX();

	void setPositionY(float _y);
	float getPositionY();

	void setPositionZ(float _z);
	float getPositionZ();

	void setPosition(float _x, float _y, float _z = 0);

	void setSize(float _size);
	float getSize();

	void setColor(Color& color);
	Color& getColor();

	virtual void update() = 0;

	virtual void render(Renderer* renderer) = 0;

};

