#include "stdafx.h"
#include "SceneMgr.h"


SceneMgr::SceneMgr(Renderer* _renderer) : renderer(_renderer)
{
	initilize();
}


SceneMgr::~SceneMgr()
{
}

void SceneMgr::initilize()
{
	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
	{
		addObject();
	}
}

void SceneMgr::addObject()
{
	if (objectCount >= MAX_OBJECTS_COUNT)
	{
		std::cout << "오브젝트 개수가 꽉 찼습니다." << std::endl;
		return;
	}

	objects[objectCount] = new Locker(-200 + rand() % 400, -200 + rand() % 400, 0, 5, 1, 1, 1, 1);

	objectCount++;
}

void SceneMgr::update()
{
	for (int i = 0; i < objectCount; ++i)
	{
		objects[i]->update();
	}
}

void SceneMgr::render()
{
	for (int i = 0; i < objectCount; ++i)
	{
		objects[i]->render(renderer);
	}
}