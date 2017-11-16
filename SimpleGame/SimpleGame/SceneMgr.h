#pragma once
#include "stdafx.h"
#include "define.h"
#include "Object.h"
#include "Renderer.h"
#include <iostream>
#include <vector>
#include <memory>
using namespace std;

class SceneMgr
{
private:
	Renderer* renderer;

	static const int MAX_CHARACTER_COUNT = 10;

	vector<Object*> red_buildings;
	vector<Object*> red_characters;
	vector<Object*> red_bullets;
	vector<Object*> red_arrows;

	vector<Object*> blue_buildings;
	vector<Object*> blue_characters;
	vector<Object*> blue_bullets;
	vector<Object*> blue_arrows;

	void init();
	void addBuildingObject(float x, float y, int team);
	void addBulletObject(float x, float y, int team);
	void addRedCharacterObject();
	
	void addArrowObject(float x, float y, int team);

	bool collision(Object* obj1, Object* obj2);

	float curTime, prevTime;

public:
	SceneMgr(Renderer* _renderer);
	~SceneMgr();

	float red_time = 0;
	float blue_time = 0;

	void update();
	void render();

	void addBlueCharacterObject(float x, float y);
};

