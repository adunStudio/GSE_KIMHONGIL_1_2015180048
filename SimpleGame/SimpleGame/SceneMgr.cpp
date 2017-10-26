#include "stdafx.h"
#include "SceneMgr.h"


SceneMgr::SceneMgr(Renderer* _renderer) : renderer(_renderer), curTime(0), prevTime(0)
{
	prevTime = static_cast<float>(timeGetTime() * 0.001f);

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

	objects.push_back(new Locker(-200 + rand() % 400, -200 + rand() % 400, 0, 5, 1, 1, 1, 1));

	objectCount = objects.size();
}

void SceneMgr::update()
{
	curTime = static_cast<float>(timeGetTime() * 0.001f);
	float elapsed = curTime - prevTime;
	prevTime = curTime;

	for (int i = 0; i < objectCount; ++i)
	{
		objects[i]->update(elapsed);

		objects[i]->setColor(whiteColor);
		for (int j = 0; j < objectCount; ++j)
		{
			if (objects[i] != objects[j])
			{
				if (objects[i]->intersect(objects[j]))
				{
					objects[i]->setColor(redColor);
					objects[i]->attacked(0.001);
					objects[j]->attacked(0.001);
				}
			}
		}
	}

	for (int i = 0; i < objectCount; ++i)
	{
		if (objects[i]->isDead())
		{
			(objects.erase(objects.begin() + i));
			objectCount = objects.size();
		}
	}
}

void SceneMgr::render()
{
	for (int i = 0; i < objectCount; ++i)
	{
		objects[i]->render(renderer);
	}
}