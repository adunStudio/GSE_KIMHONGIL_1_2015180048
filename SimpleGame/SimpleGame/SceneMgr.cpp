#include "stdafx.h"
#include "SceneMgr.h"


SceneMgr::SceneMgr(Renderer* _renderer) : renderer(_renderer), curTime(0), prevTime(0)
{
	prevTime = static_cast<float>(timeGetTime() * 0.001f);

	init();
}


SceneMgr::~SceneMgr()
{
}

void SceneMgr::init()
{
	addBuildingObject(0, 0);
}

void SceneMgr::addBuildingObject(float x, float y)
{
	buildings.push_back(new Object(x, y, OBJECT_BUILDING));
}

void SceneMgr::addCharacterObject(float x, float y)
{
	if (characters.size() < MAX_CHARACTER_COUNT)
	{
		characters.push_back(new Object(x, y, OBJECT_CHARACTER));
	}
}

void SceneMgr::addBulletObject(float x, float y)
{
	bullets.push_back(new Object(x, y, OBJECT_BULLET));
}

void SceneMgr::update()
{
	curTime = static_cast<float>(timeGetTime() * 0.001f);
	float elapsed = curTime - prevTime;
	prevTime = curTime;

	for (auto v : buildings)
		v->update(elapsed);
	for (auto v : characters)
		v->update(elapsed);
	for (auto v : bullets)
		v->update(elapsed);

	// ĳ���� VS ����
	for (auto it = characters.begin(); it != characters.end();)
	{
		if (buildings.size() > 0 && (*it)->intersect(buildings[0]))
		{
			// ���� ü�� ���
			buildings[0]->attacked((*it)->getLife());
			if (buildings[0]->getLife() <= 0)
				buildings.erase(buildings.begin());

			// ĳ���� ����
			delete *it;
			it = characters.erase(it);
		}
		else
			++it;
	}

	// ĳ���� VS �Ѿ�
	for (auto it_c = characters.begin(); it_c != characters.end();)
	{
		auto character = *it_c;

		for (auto it_b = bullets.begin(); character != nullptr && it_b != bullets.end();)
		{
			auto bullet = *it_b;

			if (character->intersect(bullet))
			{
				// ĳ���� ü�� ��� | ĳ���� ����
				// TODO: �ɸ��� ü��(10)�� �Ѿ� ü��(20)���� ������ ??
				character->attacked(bullet->getLife());
				if (character->getLife() <= 0)
				{
					delete character;
					character = nullptr;
					it_c = characters.erase(it_c);
				}

				// �Ѿ� ����
				delete bullet;
				it_b = bullets.erase(it_b);
			}
			else
				++it_b;
		}

		if (character != nullptr)
			++it_c;
	}

	// �Ѿ� ����
	if (buildings.size() > 0 && buildings[0]->getTime() > 0.5)
	{
		buildings[0]->setTime(buildings[0]->getTime() - 0.5);
		addBulletObject(buildings[0]->getPositionX(), buildings[0]->getPositionY());
	}
}

void SceneMgr::render()
{
	for(auto v : buildings)
		v->render(renderer);

	for (auto v : characters)
		v->render(renderer);

	for (auto v : bullets)
		v->render(renderer);
	
}