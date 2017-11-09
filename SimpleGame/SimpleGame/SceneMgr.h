#pragma once
#include "stdafx.h"
#include "Object.h"
#include "Renderer.h"
#include <iostream>
#include <vector>
#include <memory>
using namespace std;

#define OBJECT_BUILDING  0
#define OBJECT_CHARACTER 1
#define OBJECT_BULLET    2
#define OBJECT_ARROW     3

class SceneMgr
{
private:
	Renderer* renderer;

	static const int MAX_CHARACTER_COUNT = 10;

	vector<Object*> buildings;
	vector<Object*> characters;
	vector<Object*> bullets;
	vector<Object*> arrows;

	void init();
	void addBuildingObject(float x, float y);
	void addBulletObject(float x, float y);
	void addArrowObject(float x, float y, Object* parent);

	bool collision(Object* obj1, Object* obj2);

	float curTime, prevTime;

public:
	SceneMgr(Renderer* _renderer);
	~SceneMgr();

	void update();
	void render();

	void addCharacterObject(float x, float y);
};

