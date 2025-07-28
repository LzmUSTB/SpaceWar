#include "enemy.cpp" 
#include "destroy.cpp"
#include "bullet.cpp"
#include <ctime>
#pragma once
class enemies {
friend class destroy;
	int enemyCount;
	int interval;
	int map_height;
	int map_width;
	bool crasherExist = false;
public:
	bullet* m_blt[50] = { 0 };
	enemy* ePtr[30] = { 0 };
	enemies(int width,int height)
	{
		enemyCount = 0;
		interval = 300;
		map_height = height;
		map_width = width;
	}
	~enemies()
	{
		for (int i = 0; i < 30; i++)
		{
			delete ePtr[i];
			ePtr[i] = 0;
		}
	}
	void createEnemy(int score){
		if(interval!=0)
		{
			interval--;
			return;
		}
		for (int i = 0; i < 30; i++)
		{
			if (ePtr[i] == 0)
			{
				int type = rand() % (7*score/(score+120)+1);
				if (crasherExist && type == 2)type = 0;
				ePtr[i] = new enemy(rand()%(351-51),score,type);
				if (type == 2)crasherExist = true;
				enemyCount++;
				interval = 5+25*(1-score/(score+30));
				return;
			}
		}
	}
	void drawEnemies()
	{
		for (int i = 0; i < 30; i++)
		{
			if (ePtr[i] != 0)
			{
				shoot(i);
				ePtr[i]->drawEnemy();
			}
			if (ePtr[i] != 0 && ePtr[i]->m_y > map_height-ePtr[i]->m_height)
			{
				if (ePtr[i]->m_type == 2) { crasherExist = false; }
				deleteEnemies(i);
			}
		}
		for (int i = 0; i < 50; i++)
		{
			if (m_blt[i] != 0)
			{
				m_blt[i]->drawBullet_Enemy();
			}
			if (m_blt[i] != 0 && m_blt[i]->deleteBullet(map_width,map_height))
			{
				delete m_blt[i];
				m_blt[i] = 0;
			}
		}
	}
	void deleteEnemies(int i)
	{
		delete ePtr[i];
		ePtr[i] = 0;
		enemyCount--;
	}
	int isEnemiesHit(bullet* &blt,destroy* des)
	{
		int scorePlus = 0;
		if (blt == 0)
			return scorePlus;
		for (int i = 0; i < 30; i++)
		{
			if (ePtr[i] == 0)
				continue;
			if (object::isHit(ePtr[i], blt))
			{
				if (--ePtr[i]->m_life == 0)
				{
					scorePlus = (ePtr[i]->m_type) * 2+2;
					des->getInstance(ePtr[i]->m_x, ePtr[i]->m_y, ePtr[i]->m_width, ePtr[i
					]->m_height);
					if (ePtr[i]->m_type == 2) { crasherExist = false; }
					delete ePtr[i];
					enemyCount--;
					ePtr[i] = 0;
				}
				if (blt->ifBreak)
				{
					delete blt;
					blt = 0;
				}
				return scorePlus;
			}
		}
		return scorePlus;
	}
	void shoot(int i)
	{
		if (ePtr[i]->m_type == 2)
		{
			if (ePtr[i]->bltCount-- > 0)return;
			for (int j = 0; j < 50-2; j++)
			{
				if (m_blt[j] == 0 && m_blt[j + 1] == 0 && m_blt[j + 2] == 0)
				{
					m_blt[j] = new bullet(ePtr[i]->m_x, ePtr[i]->m_y, ePtr[i]->m_width, 10, 0, 0, true, ePtr[i]->m_height);
					m_blt[j + 1] = new bullet(ePtr[i]->m_x - 25, ePtr[i]->m_y, ePtr[i]->m_width, 10, 0, 0, true, ePtr[i]->m_height);
					m_blt[j + 2] = new bullet(ePtr[i]->m_x + 25, ePtr[i]->m_y, ePtr[i]->m_width, 10, 0, 0, true, ePtr[i]->m_height);
					ePtr[i]->bltCount = 40;
					return;
				}
			}
		}
		else if (ePtr[i]->m_type == 3)
		{
			if (ePtr[i]->bltCount-- > 0)return;
			for (int j = 0; j < 50 - 3; j++)
			{
				if (m_blt[j] == 0 && m_blt[j + 1] == 0 && m_blt[j + 2] == 0 && m_blt[j + 3] == 0)
				{
					m_blt[j] = new bullet(ePtr[i]->m_x-18, ePtr[i]->m_y-69, ePtr[i]->m_width, 10, -0.7, 0, true, ePtr[i]->m_height);
					m_blt[j + 1] = new bullet(ePtr[i]->m_x - 18, ePtr[i]->m_y-36, ePtr[i]->m_width, 10, -0.7, 0, true, ePtr[i]->m_height);
					m_blt[j + 2] = new bullet(ePtr[i]->m_x + 18, ePtr[i]->m_y-36, ePtr[i]->m_width, 10, 0.7, 0, true, ePtr[i]->m_height);
					m_blt[j + 3] = new bullet(ePtr[i]->m_x + 18, ePtr[i]->m_y-69, ePtr[i]->m_width, 10, 0.7, 0, true, ePtr[i]->m_height);
					ePtr[i]->bltCount = 25;
				}
			}
		}
	}
};