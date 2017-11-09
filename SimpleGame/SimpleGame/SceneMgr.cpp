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

void SceneMgr::addArrowObject(float x, float y, Object* parent)
{
	auto arrow = new Object(x, y, OBJECT_ARROW);
	arrow->setParent(parent);

	arrows.push_back(arrow);
}

bool SceneMgr::collision(Object* obj1, Object* obj2)
{
	return obj1->intersect(obj2);
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
	for (auto v : arrows)
		v->update(elapsed);

	// 캐릭터 VS 빌딩
	for (auto it = characters.begin(); it != characters.end();)
	{
		if (buildings.size() > 0 && collision((*it), buildings[0]))
		{
			// 빌딩 체력 깎기
			buildings[0]->attacked((*it)->getLife());
			if (buildings[0]->getLife() <= 0)
				buildings.erase(buildings.begin());

			// 캐릭터 삭제
			delete *it;
			it = characters.erase(it);
		}
		else
			++it;
	}

	// 캐릭터  VS  총알
	for (auto it_c = characters.begin(); it_c != characters.end();)
	{
		auto character = *it_c;

		for (auto it_b = bullets.begin(); character != nullptr && it_b != bullets.end();)
		{
			auto bullet = *it_b;

			if (collision(character, bullet))
			{
				// 캐릭터 체력 깎기 | 캐릭터 삭제
				// TODO: 케릭터 체력(10)이 총알 체력(20)보다 작은데 ??
				character->attacked(bullet->getLife());
				if (character->getLife() <= 0)
				{
					delete character;
					character = nullptr;
					it_c = characters.erase(it_c);
				}

				// 총알 삭제
				delete bullet;
				it_b = bullets.erase(it_b);
			}
			else
				++it_b;
		}

		if (character != nullptr)
			++it_c;
	}
	
	// 화살 VS 빌딩
	for (auto it_a = arrows.begin(); it_a != arrows.end();)
	{
		auto arrow = *it_a;

		if (buildings.size() > 0 && collision(arrow, buildings[0]))
		{
			// 빌딩 체력 깎기
			buildings[0]->attacked(arrow->getLife());
			if (buildings[0]->getLife() <= 0)
				buildings.erase(buildings.begin());

			// 화살 삭제
			delete *it_a;
			it_a = arrows.erase(it_a);
		}
		else
			++it_a;
	}

	// 캐릭터  VS  화살
	for (auto it_c = characters.begin(); it_c != characters.end();)
	{
		auto character = *it_c;

		for (auto it_a = arrows.begin(); character != nullptr && it_a != arrows.end();)
		{
			auto arrow = *it_a;

			if (arrow->getParent() != character && collision(character, arrow))
			{
				// 캐릭터 체력 깎기 | 캐릭터 삭제
				character->attacked(arrow->getLife());
				if (character->getLife() <= 0)
				{
					delete character;
					character = nullptr;
					it_c = characters.erase(it_c);
				}

				// 화살 삭제
				delete arrow;
				it_a = arrows.erase(it_a);
			}
			else
				++it_a;
		}

		if (character != nullptr)
			++it_c;
	}
	
	
	// 부모가 없는 총알 삭제
	for (auto it = arrows.begin(); it != arrows.end();)
	{
		if (std::find(characters.begin(), characters.end(), (*it)->getParent()) == characters.end())
			it = arrows.erase(it);
		else
			++it;
	}

	// 총알 생성
	if (buildings.size() > 0 && buildings[0]->getTime() > 0.5)
	{
		buildings[0]->setTime(buildings[0]->getTime() - 0.5);
		addBulletObject(buildings[0]->getPositionX(), buildings[0]->getPositionY());
	}

	// 화살 생성
	for (auto c : characters)
	{
		if (c->getTime() > 0.5)
		{
			c->setTime(c->getTime() - 0.5);
			addArrowObject(c->getPositionX(), c->getPositionY(), c);
		}
	}

	// 라이프 타임
	/*for (auto it = characters.begin(); it != characters.end();)
	{
		if ((*it)->isDead())
		{
			delete *it;
			it = characters.erase(it);
		}
		else
			++it;
	}

	for (auto it = bullets.begin(); it != bullets.end();)
	{
		if ((*it)->isDead())
		{
			delete *it;
			it = bullets.erase(it);
		}
		else
			++it;
	}

	for (auto it = arrows.begin(); it != arrows.end();)
	{
		if ((*it)->isDead())
		{
			delete *it;
			it = arrows.erase(it);
		}
		else
			++it;
	}*/
}

void SceneMgr::render()
{
	for (auto v : buildings)
		v->render(renderer);

	for (auto v : characters)
		v->render(renderer);

	for (auto v : bullets)
		v->render(renderer);

	for (auto v : arrows)
		v->render(renderer);
}