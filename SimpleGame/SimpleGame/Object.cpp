#include "stdafx.h"
#include "Object.h"


Object::Object(float _x, float _y, int _type, int _team)
	: x(_x), y(_y), z(0), a(1), type(_type), team(_team)
{
	init();
}

Object::~Object()
{
	std::cout << "��ü ���� �Ϸ�" << std::endl;
}

void Object::init()
{
	switch (team)
	{
	case RED_TEAM:
		angle = 180 + rand() % 180;

		break;
	case BLUE_TEAM:
		angle = rand() % 180;

		break;
	}
	lifeTime = 100;

	switch (type)
	{
	case OBJECT_BACKGROUND:
		m_drawLevel = LEVEL_BACKGROUND;
		break;
	case OBJECT_BUILDING:
		size = 100;
		life = 500;
		m_maxLife = 500;
		setSpeed(0);
		r = 1; g = 1; b = 0;
		m_drawLevel = LEVEL_BUILDING;
		break;
	case OBJECT_CHARACTER:
		size = 30;
		life = 100;
		m_maxLife = 100;
		setSpeed(300);
		if (team == RED_TEAM) { r = 1; g = 0; b = 0; }
		else { r = 1; g = 0; b = 1; }
		m_drawLevel = LEVEL_CHARACTER;
		break;
	case OBJECT_BULLET:
		size = 4;
		life = 15;
		m_maxLife = 15;
		setSpeed(600);
		if (team == RED_TEAM){r = 1; g = 0; b = 0;}
		else                 {r = 1; g = 0; b = 1;}
		m_drawLevel = LEVEL_BULLET;
		break;
	case OBJECT_ARROW:
		size = 4;
		life = 10;
		m_maxLife = 10;
		setSpeed(100);
		if (team == RED_TEAM) { r = 0.5; g = 0.2; b = 0.7; }
		else { r = 1; g = 1; b = 0; }
		m_drawLevel = LEVEL_ARROW;
		break;
	}

	
}

/* Setter / Getter */
void Object::setSize(float _size) { size = _size; }
float Object::getSize() { return size; }

void Object::setPositionX(float _x) { x = _x;  }
float Object::getPositionX() { return x; }

void Object::setPositionY(float _y) { y = _y; }
float Object::getPositionY() { return y; }

float Object::getTime() { return elapsedTime; }
void Object::setTime(float _time) { elapsedTime = _time; }

float Object::getLife() { return life; }

void Object::setSpeed(float speed)
{
	speedX = speedY = speed;
}

void Object::setParent(Object* _parent)
{
	parent = _parent;
}

Object* Object::getParent()
{
	return parent;
}

void Object::addChild(Object* child)
{
	children.push_back(child);
}

bool Object::intersect(Object* obj)
{
	return (
		x - size / 2 < obj->x + obj->size / 2 &&
		x + size / 2 > obj->x - obj->size / 2 &&
		y - size / 2 < obj->y + obj->size / 2 &&
		y + size / 2 > obj->y - obj->size / 2
		);
}


void Object::attacked(float damage)
{
	life -= damage;
}

bool Object::isDead()
{
	return lifeTime < 0;
}

void Object::update(float elapsed)
{
	aa++;

	if (aa > 360)
		aa = 0;

	elapsedTime += elapsed;	
	frameTime += elapsed;
	lifeTime -= elapsed;

	
	if (type == OBJECT_BUILDING)
	{
		if (frameTime >((double)rand() / (RAND_MAX)) + 1)
		{
			frame = (frame + 1) % 5;
			frameTime = 0;

			if(frame == 1)
				frameY = (frameY + 1) % 4;
		}

	}
	else
	{
		if (frameTime > 0.2)
		{
			frame = (frame + 1) % 4;
			frameTime = 0;

		}

	}

	if (type == OBJECT_CHARACTER)
	{
		if (x < -WIDTH / 2 || x > WIDTH / 2)
			speedX *= -1;

		if (y < -HEIGHT / 2 || y > HEIGHT / 2)
			speedY *= -1;
	}
	else
	{

	}
	x += cos(angle * PI / 180.0f) * speedX * 0.0005;
	y += sin(angle * PI / 180.0f) * speedY * 0.0005;
	/**if (type == OBJECT_CHARACTER)
	{
	
	}
	else
	{
		x += cos(angle) * speedX * 0.0005;
		y += sin(angle) * speedY * 0.0005;
	}**/
	
	
}

void Object::render(Renderer* renderer)
{

	switch (type)
	{
	case OBJECT_BACKGROUND:
		if(texture < 0)
			texture = renderer->CreatePngTexture("./resource/background.png");
		
		renderer->DrawTexturedRect(0, 0, 0, 800, 1, 1, 1, 1, texture, m_drawLevel);
		break;

	case OBJECT_CHARACTER:
		if (texture < 0)
		{
			switch (team)
			{
			case RED_TEAM:
				texture = renderer->CreatePngTexture("./resource/skeleton.png");
				break;
			case BLUE_TEAM:
				texture = renderer->CreatePngTexture("./resource/santa.png");

				bb = renderer->CreatePngTexture("./resource/ch/ch_gift.png");

			}
		}

		if(team == RED_TEAM)
			renderer->DrawTexturedRectSeq(x,  y, 0, size, 1, 1, 1, 1, texture, frame, 0, 4, 1, m_drawLevel);
		else
		{
			renderer->DrawTexturedRectSeq(x, y, 0, size, 1, 1, 1, 1, texture, frame, 0, 8, 1, m_drawLevel);

			renderer->DrawTexturedRect(cos(aa * PI / 180.0f) + x + 15, sin(aa * PI / 180.0f) + y + 15, 0, 30, 1, 1, 1, 1, bb, m_drawLevel);

		}

		break;

	case OBJECT_BULLET:
		if (texture < 0)
			texture = renderer->CreatePngTexture("./resource/candy.png");
		renderer->DrawParticle(x, y, 0, size, 1, 1, 1, 1, -1 * speedX / abs(speedX) * cos(angle * PI / 180.0f),  -1 * speedY / abs(speedY) * sin(angle  * PI / 180.0f), texture, elapsedTime, LEVEL_BULLET);

		break;

	case OBJECT_BUILDING:
		if (texture < 0)
		{
			switch (team)
			{
			case RED_TEAM:
				texture = renderer->CreatePngTexture("./resource/tree.png");
				break;

			case BLUE_TEAM:
				texture = renderer->CreatePngTexture("./resource/tree.png");
				break;
			}
		}

		//renderer->DrawTexturedRectSeq(x, y, 0, size, 1, 1, 1, 1, texture, frame, 0, 4, 1, m_drawLevel);
		renderer->DrawTexturedRectSeqXY(x, y, 0, size, size, 1, 1, 1, 1, texture, frame, frameY, 5, 3, m_drawLevel);
		//renderer->DrawTexturedRect(x, y, 0, size, 1, 1, 1, 1, texture, m_drawLevel);
	
		break;
		
	case OBJECT_ARROW:
		if (texture < 0)
		{
			switch (team)
			{
			case RED_TEAM:
				texture = renderer->CreatePngTexture("./resource/particle.png");
				break;

			case BLUE_TEAM:
				texture = renderer->CreatePngTexture("./resource/ch/ch_gift.png");

				break;
			}
		}

		renderer->DrawTexturedRect(x, y, 0, size + 10, 1, 1, 1, 1, texture, m_drawLevel);
		break;


	default:
		renderer->DrawSolidRect(x, y, z, size, r, g, b, a, m_drawLevel);

	}

	

	if (type == OBJECT_BUILDING || type == OBJECT_CHARACTER)
	{
		if (team == RED_TEAM)
			renderer->DrawSolidRectGauge(x, y + 10 + (size / 2), z, size, 10, 1, 0, 0, 1, life / m_maxLife, m_drawLevel);
		else
			renderer->DrawSolidRectGauge(x, y + 10 + (size / 2), z, size, 10, 0, 0, 1, 1, life / m_maxLife, m_drawLevel);

		if (type == OBJECT_BUILDING)
		{
			char text[10];
			_itoa_s(life, text, 10);
			renderer->DrawText(x - 10, y + 56, GLUT_BITMAP_TIMES_ROMAN_10, 1, 1, 0, text);
		}
	}

}

