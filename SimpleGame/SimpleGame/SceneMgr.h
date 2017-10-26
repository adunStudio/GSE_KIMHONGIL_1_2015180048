#pragma once
#include "stdafx.h"
#include "Locker.h"
#include "Renderer.h"
#include <iostream>
#include <vector>
#include <memory>
using namespace std;

class SceneMgr
{
private:
	Renderer* renderer;

	static const int MAX_OBJECTS_COUNT = 50;
	vector<Object*> objects;
	int objectCount = 0;

	void initilize();
	void addObject();

	Color whiteColor = { 1, 1, 1, 1 };
	Color redColor = { 1, 0, 0, 1 };

	float curTime, prevTime;

public:
	SceneMgr(Renderer* _renderer);
	~SceneMgr();

	void update();
	void render();
};

