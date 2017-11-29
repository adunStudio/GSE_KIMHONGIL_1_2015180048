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

	// ������ ĳ���� ����
	addRedCharacterObject();

	// �Ѿ� ����
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

	// ȭ�� ����
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


	// ������ ����Ʈ

	// ������ ĳ���� vs ����� ����
	iterateCollision(red_characters, blue_buildings);
	// ����� ĳ���� vs ������ ����
	iterateCollision(blue_characters, red_buildings);


	// ������ ĳ���� vs ����� �Ѿ�
	iterateCollision(red_characters, blue_bullets);
	// ����� ĳ���� vs ������ �Ѿ�
	iterateCollision(blue_characters, red_bullets);


	// ������ ĳ���� vs ����� ȭ��
	iterateCollision(red_characters, blue_arrows);
	// ����� ĳ���� vs ������ ȭ��
	iterateCollision(blue_characters, red_arrows);


	// Bullet �� Arrow �� ȭ�鿡�� ����� ��������� ����
	outerCheckAndDelete(red_bullets);
	outerCheckAndDelete(blue_bullets);
	outerCheckAndDelete(red_arrows);
	outerCheckAndDelete(blue_arrows);



}

void SceneMgr::iterateCollision(vector<Object*>& team1V, vector<Object*>& team2V)
{

	for (auto team1 = team1V.begin(); team1 != team1V.end();)
	{
		auto obj1 = *team1;

		for (auto team2 = team2V.begin(); obj1 != nullptr && team2 != team2V.end();)
		{
			auto obj2 = *team2;

			if (collision(obj1, obj2))
			{
				float obj1_life = obj1->getLife();
				float obj2_life = obj2->getLife();

				obj1->attacked(obj2_life);
				obj2->attacked(obj1_life);

				if (obj1->getLife() <= 0);
				{
					delete obj1;
					obj1 = nullptr;
				}

				if (obj2->getLife() <= 0)
				{
					delete obj2;
					obj2 = nullptr;
				}
			}

			if (obj2 != nullptr)
				++team2;
			else
				team2 = team2V.erase(team2);
		}

		if (obj1 != nullptr)
			++team1;
		else
			team1 = team1V.erase(team1);
	}
}

void SceneMgr::outerCheckAndDelete(vector<Object*>& v)
{
	for (auto it = v.begin(); it != v.end();)
	{
		auto obj = *it;

		float x = obj->getPositionX();
		float y = obj->getPositionY();

		if (x < -WIDTH / 2 || x > WIDTH / 2 || y < -HEIGHT / 2 || y > HEIGHT / 2)
		{
			delete obj;
			obj = nullptr;
			std::cout << "��輱 �Ѿ�� ����" << std::endl;
		}

		if (obj != nullptr)
			++it;
		else
			it = v.erase(it);
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