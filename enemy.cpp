#include "bullet.cpp"
#include "object.cpp"
#include <graphics.h>
#pragma once
class enemy:public object {
	friend class enemies;
private:
	int m_type;
	bool m_direction=false;
	int m_life;
	int bltCount=0;
	IMAGE m_img;
	IMAGE m_alpha;
	bullet* m_blt;
public:
	enemy(int x, double score,int type=0)
	{
		if (type == 1)
		{
			m_type = 1;
			loadimage(&m_img, _T("./images/enemy_bee.png"));
			loadimage(&m_alpha, _T("./images/enemy__bee_alpha.png"));
			m_speed = 8*(1+score/(score+120));
			m_life = 1;
		}
		else if(type==2)
		{
			m_type = 2;
			loadimage(&m_img, _T("./images/enemy_crasher.png"));
			loadimage(&m_alpha, _T("./images/enemy__crasher_alpha.png"));
			m_speed = 2;
			m_life = 10 * (1 + score / (score + 120));
		}
		else if (type == 3||type>5)
		{
			m_type = 3;
			loadimage(&m_img, _T("./images/enemy_killer.png"));
			loadimage(&m_alpha, _T("./images/enemy__killer_alpha.png"));
			m_speed = 3 * (1 + score / (score + 120));
			m_life = 4 * (1 + score / (score + 200));
			bltCount = 25;
		}
		else
		{
			m_type = 0;
			loadimage(&m_img, _T("./images/enemy_normal.png"));
			loadimage(&m_alpha, _T("./images/enemy__normal_alpha.png"));
			m_speed = 5 * (1 + score / (score + 120));
			m_life = 2;
		}
		m_width = m_img.getwidth();
		m_height = m_img.getheight();
		m_y = 0 - m_height;
		m_x = x;
		m_blt = 0;
	}
	void drawEnemy()
	{
		putimage(m_x, m_y, &m_alpha, SRCAND);
		putimage(m_x, m_y, &m_img, SRCPAINT);
		if (m_type == 1)
		{
			m_y += m_speed;
			m_x += (m_direction == false) ? -m_speed : m_speed;
			if (m_x < 0) { m_x = 0; m_direction = true; }
			else if (m_x > map_width - m_width) { m_x = map_width - m_width; m_direction = false; }
		}
		else if (m_type == 2)
		{
			m_y += (m_y < 10) ? m_speed : 0;
			m_x += (m_direction==false)? -m_speed : m_speed;
			if (m_x < 0) { m_x = 0; m_direction = true; }
			else if (m_x > map_width-m_width) { m_x = map_width-m_width; m_direction = false; }
		}
		else 
		{
			m_y += m_speed;
		}
	}
};