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
	srand(time(NULL));

	addBuildingObject(-150, 300, RED_TEAM);
	addBuildingObject(0, 330, RED_TEAM);
	addBuildingObject(150, 300, RED_TEAM);

	addBuildingObject(-150, -300, BLUE_TEAM);
	addBuildingObject(0, -330, BLUE_TEAM);
	addBuildingObject(150, -300, BLUE_TEAM);
}

void SceneMgr::addBuildingObject(float x, float y, int team)
{
	if (team == RED_TEAM)
		red_buildings.push_back(new Object(x, y, OBJECT_BUILDING, team));
	else
		blue_buildings.push_back(new Object(x, y, OBJECT_BUILDING, team));
}

void SceneMgr::addBlueCharacterObject(float x, float y)
{
	if (blue_time >= BLUE_CHARACTER_COOLTIME && y < 0)
	{
		blue_time = 0;
		blue_characters.push_back(new Object(x, y, OBJECT_CHARACTER, BLUE_TEAM));
	}
}

void SceneMgr::addRedCharacterObject()
{
	if (red_time >= RED_CHARACTER_COOLTIME)
	{
		red_time = 0;

		int x = -250 + (rand() % WIDTH);
		int y = (rand() % (HEIGHT / 2));
		red_characters.push_back(new Object(x, y, OBJECT_CHARACTER, RED_TEAM));
	}
}

void SceneMgr::addBulletObject(float x, float y, int team)
{
	if (team == RED_TEAM)
		red_bullets.push_back(new Object(x, y, OBJECT_BULLET, team));
	else
		blue_bullets.push_back(new Object(x, y, OBJECT_BULLET, team));
}

void SceneMgr::addArrowObject(float x, float y, int team)
{
	if (team == RED_TEAM)
		red_arrows.push_back(new Object(x, y, OBJECT_ARROW, team));
	else
		blue_arrows.push_back(new Object(x, y, OBJECT_ARROW, team));
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

	red_time  += elapsed;
	blue_time += elapsed;

	for (auto v : red_buildings)
		v->update(elapsed);
	for (auto v : blue_buildings)
		v->update(elapsed);

	for (auto v : red_bullets)
		v->update(elapsed);
	for (auto v : blue_bullets)
		v->update(elapsed);

	for (auto v : red_characters)
		v->update(elapsed);
	for (auto v : blue_characters)
		v->update(elapsed);

	for (auto v : red_arrows)
		v->update(elapsed);
	for (auto v : blue_arrows)
		v->update(elapsed);

	// ·¹µåÆÀ Ä³¸¯ÅÍ »ý¼º
	addRedCharacterObject();

	// ÃÑ¾Ë »ý¼º
	for (auto v : red_buildings)
	{
		if (v->getTime() >= BULLET_COOLTIME)
		{
			v->setTime(0);
			addBulletObject(v->getPositionX(), v->getPositionY(), RED_TEAM);
		}
	}
	for (auto v : blue_buildings)
	{
		if (v->getTime() >= BULLET_COOLTIME)
		{
			v->setTime(0);
			addBulletObject(v->getPositionX(), v->getPositionY(), BLUE_TEAM);
		}
	}

	// È­»ì »ý¼º
	for (auto v : red_characters)
	{
		if (v->getTime() >= ARROW_COOLTIME)
		{
			v->setTime(0);
			addArrowObject(v->getPositionX(), v->getPositionY(), v->team);
		}
	}
	for (auto v : blue_characters)
	{
		if (v->getTime() >= ARROW_COOLTIME)
		{
			v->setTime(0);
			addArrowObject(v->getPositionX(), v->getPositionY(), v->team);
		}
	}


	// ·¹µåÆÀ Ä³¸¯ÅÍ vs ºí·çÆÀ ºôµù
	for (auto it_c = red_characters.begin(); it_c != red_characters.end();)
	{
		auto character = *it_c;
		
		for (auto it_b = blue_buildings.begin(); character != nullptr && it_b != blue_buildings.end();)
		{
			auto building = *it_b;

			if (collision(character, building))
			{
				building->attacked(character->getLife());

				delete character;
				character = nullptr;

				if (building->getLife() <= 0)
				{
					delete building;
					building = nullptr;
				}
			}

			if (building != nullptr)
				++it_b;
			else
				it_b = blue_buildings.erase(it_b);
			
		}

		if (character != nullptr)
			++it_c;
		else
			it_c = red_characters.erase(it_c);
	}

	// ºí·çÆÀ Ä³¸¯ÅÍ vs ·¹µåÆÀ ºôµù
	for (auto it_c = blue_characters.begin(); it_c != blue_characters.end();)
	{
		auto character = *it_c;

		for (auto it_b = red_buildings.begin(); character != nullptr && it_b != red_buildings.end();)
		{
			auto building = *it_b;

			if (collision(character, building))
			{
				building->attacked(character->getLife());

				delete character;
				character = nullptr;

				if (building->getLife() <= 0)
				{
					delete building;
					building = nullptr;
				}
			}

			if (building != nullptr)
				++it_b;
			else
				it_b = red_buildings.erase(it_b);
		}

		if (character != nullptr)
			++it_c;
		else
			it_c = blue_characters.erase(it_c);
	}


	// ·¹µåÆÀ Ä³¸¯ÅÍ vs ºí·çÆÀ ÃÑ¾Ë
	for (auto it_c = red_characters.begin(); it_c != red_characters.end();)
	{
		auto character = *it_c;

		for (auto it_b = blue_bullets.begin(); character != nullptr && it_b != blue_bullets.end();)
		{
			auto bullet = *it_b;

			if (collision(character, bullet))
			{
				bullet->attacked(character->getLife());

				delete character;
				character = nullptr;

				if (bullet->getLife() <= 0)
				{
					delete bullet;
					bullet = nullptr;
				}
			}

			if (bullet != nullptr)
				++it_b;
			else
				it_b = blue_bullets.erase(it_b);

		}

		if (character != nullptr)
			++it_c;
		else
			it_c = red_characters.erase(it_c);
	}


	// ºí·çÆÀ Ä³¸¯ÅÍ vs ·¹µåÆÀ ÃÑ¾Ë
	for (auto it_c = blue_characters.begin(); it_c != blue_characters.end();)
	{
		auto character = *it_c;

		for (auto it_b = red_bullets.begin(); character != nullptr && it_b != red_bullets.end();)
		{
			auto bullet = *it_b;

			if (collision(character, bullet))
			{
				bullet->attacked(character->getLife());

				delete character;
				character = nullptr;

				if (bullet->getLife() <= 0)
				{
					delete bullet;
					bullet = nullptr;
				}
			}

			if (bullet != nullptr)
				++it_b;
			else
				it_b = red_bullets.erase(it_b);

		}

		if (character != nullptr)
			++it_c;
		else
			it_c = blue_characters.erase(it_c);
	}


	// ·¹µåÆÀ Ä³¸¯ÅÍ vs ºí·çÆÀ È­»ì
	for (auto it_c = red_characters.begin(); it_c != red_characters.end();)
	{
		auto character = *it_c;

		for (auto it_b = blue_arrows.begin(); character != nullptr && it_b != blue_arrows.end();)
		{
			auto arrow = *it_b;

			if (collision(character, arrow))
			{
				arrow->attacked(character->getLife());

				delete character;
				character = nullptr;

				if (arrow->getLife() <= 0)
				{
					delete arrow;
					arrow = nullptr;
				}
			}

			if (arrow != nullptr)
				++it_b;
			else
				it_b = blue_arrows.erase(it_b);

		}

		if (character != nullptr)
			++it_c;
		else
			it_c = red_characters.erase(it_c);
	}


	// ºí·çÆÀ Ä³¸¯ÅÍ vs ·¹µåÆÀ È­»ì
	for (auto it_c = blue_characters.begin(); it_c != blue_characters.end();)
	{
		auto character = *it_c;

		for (auto it_b = red_arrows.begin(); character != nullptr && it_b != red_arrows.end();)
		{
			auto arrow = *it_b;

			if (collision(character, arrow))
			{
				arrow->attacked(character->getLife());

				delete character;
				character = nullptr;

				if (arrow->getLife() <= 0)
				{
					delete arrow;
					arrow = nullptr;
				}
			}

			if (arrow != nullptr)
				++it_b;
			else
				it_b = red_arrows.erase(it_b);

		}

		if (character != nullptr)
			++it_c;
		else
			it_c = blue_characters.erase(it_c);
	}
}

void SceneMgr::render()
{
	for (auto v : red_buildings)
		v->render(renderer);
	for (auto v : blue_buildings)
		v->render(renderer);

	for (auto v : red_bullets)
		v->render(renderer);
	for (auto v : blue_bullets)
		v->render(renderer);

	for (auto v : red_characters)
		v->render(renderer);
	for (auto v : blue_characters)
		v->render(renderer);

	for (auto v : red_arrows)
		v->render(renderer);
	for (auto v : blue_arrows)
		v->render(renderer);
}