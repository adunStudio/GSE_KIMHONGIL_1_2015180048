#pragma once
#include "Locker.h"
#include "Renderer.h"
#include <iostream>
class SceneMgr
{
private:
	Renderer* renderer;

	static const int MAX_OBJECTS_COUNT = 50;
	Object* objects[MAX_OBJECTS_COUNT];
	int objectCount = 0;

	void initilize();
	void addObject();

public:
	SceneMgr(Renderer* _renderer);
	~SceneMgr();

	void update();
};

