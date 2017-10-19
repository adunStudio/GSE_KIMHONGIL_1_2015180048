#pragma once
#include "Object.h"
#include <iostream>
using namespace std;
class Locker : public Object
{
public:
	Locker(float _x, float _y, float _z, float _size, float _r, float _g, float _b, float _a);
	~Locker();

	virtual void update();
	virtual void render(Renderer* render);
};

