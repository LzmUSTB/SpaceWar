#pragma once
#include <graphics.h>
#include <math.h>
#include "object.cpp"
class bullet:public object {
private:
	IMAGE m_bullet;
	IMAGE m_bullet_big_2;
	IMAGE m_bullet_big_3;
	IMAGE m_alpha;
	double m_angle;
	int bltType;
	int boundCount=1;
	bool m_direction = false;
	bool m_directionY = false;
public:
	bool ifBreak;
	bullet(int x,int y,int width,int speed,double angle,int type=0,bool ifEnemy=false,int height=0)
	{
		if (ifEnemy)
		{
			loadimage(&m_bullet, _T("./images/bullet_2_enemy.png"));
			loadimage(&m_alpha, _T("./images/bullet_2_alpha.png"));
			m_width = m_bullet.getwidth();
			m_height = m_bullet.getheight();
			m_y = y + height;
			m_x = x + width / 2 - m_width / 2;
			ifBreak = true;
			bltType = 0;
		}
		else
		{
			if (type == 0)
			{
				loadimage(&m_bullet, _T("./images/bullet_2.png"));
				loadimage(&m_alpha, _T("./images/bullet_2_alpha.png"));
				ifBreak = true;
				bltType = 0;
			}
			else if (type == 1)
			{
				loadimage(&m_bullet, _T("./images/bullet_big.png"));
				loadimage(&m_bullet_big_2, _T("./images/bullet_big.png"));
				loadimage(&m_bullet_big_3, _T("./images/bullet_big.png"));
				loadimage(&m_alpha, _T("./images/bullet_big_alpha.png"));
				ifBreak = false;
				bltType = 1;
			}
			else if (type == 2)
			{
				loadimage(&m_bullet, _T("./images/bullet_bound.png"));
				loadimage(&m_alpha, _T("./images/bullet_bound_alpha.png"));
				ifBreak = true;
				bltType = 2;
				boundCount = 5;
			}
			m_width = m_bullet.getwidth();
			m_height = m_bullet.getheight();
			m_y = y - m_height;
			m_x = x + width / 2 - m_width / 2;
		}
		m_speed = speed;
		m_angle = angle;	//发射角度，以竖直向下为0弧度，向右为正
	}

	void drawBullet()
	{
		putimage(m_x, m_y, &m_alpha, SRCAND);
		putimage(m_x, m_y, &m_bullet, SRCPAINT);
		if (bltType == 2)
		{
			m_y -= (m_directionY == false)?m_speed * cos(m_angle): -m_speed * cos(m_angle);
			m_x -= (m_direction == false) ? -m_speed * sin(m_angle) : m_speed * sin(m_angle);
			if (m_x < 0&&--boundCount>0) 
			{ m_x = 0; m_direction = !m_direction;}
			else if (m_x > map_width - m_width && --boundCount > 0)
			{ m_x = map_width - m_width; m_direction = !m_direction;}
			if (m_y < 0 && --boundCount>0)
			{
				m_y = 0; m_directionY = true;
			}
			else if (m_y > map_height - m_height && --boundCount > 0)
			{
				m_y = map_height - m_height; m_directionY = false;
			}
		}
		else
		{
			m_x += -m_speed * sin(m_angle);
			m_y += -m_speed * cos(m_angle);
		}
	}
	void drawBullet_Enemy()
	{
		putimage(m_x, m_y, &m_alpha, SRCAND);
		putimage(m_x, m_y, &m_bullet, SRCPAINT);
		m_x += m_speed * sin(m_angle);
		m_y += m_speed * cos(m_angle);
	}
	int getY()
	{
		return m_y;
	}
	bool deleteBullet(int map_width,int map_height)
	{
		if (m_y < 0-m_height || m_y > map_height-m_height||m_x<0-m_width||m_x>map_width)
			return true;
		return false;
	}
};