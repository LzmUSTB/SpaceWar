#pragma once
#include "bullet.cpp"
#include "object.cpp"
#include "destroy.cpp"
#include <graphics.h>
#include <conio.h>
class player:public object {
private:
	int map_width;
	int map_height;
	int bltCount;
	int bltType;
	int itemCount = -1;
	IMAGE m_img;
	IMAGE m_alpha;
	IMAGE m_item_0;
	IMAGE m_item_1;
	IMAGE m_shield;
	IMAGE m_shield_alpha;
	IMAGE m_unit;
	IMAGE m_unit_alpha;
	int m_unit_width;
	int m_unit_height;
	int unitBltCount=1;
	bool unitOn = false;
public:
	bool shieldOn = false;
	int itemType;
	bullet* m_blt[50] = { 0 };
	player(int width,int height)
	{
		loadimage(&m_img, _T("./images/player.png"));
		loadimage(&m_alpha, _T("./images/player_alpha.png"));
		loadimage(&m_item_0, _T("./images/item_0.png"));
		loadimage(&m_item_1, _T("./images/item_1.png"));
		loadimage(&m_shield, _T("./images/shield.png"));
		loadimage(&m_shield_alpha, _T("./images/shield_alpha.png"));
		loadimage(&m_unit, _T("./images/unit.png"));
		loadimage(&m_unit_alpha , _T("./images/unit_alpha.png"));
		m_width = m_img.getwidth();
		m_height = m_img.getheight();
		m_unit_width = m_unit.getwidth();
		m_unit_height = m_unit.getheight();
		m_x = width/2-m_width/2;
		m_y = height-m_height-250;
		map_width = width;
		map_height = height;
		m_speed = 15;
		bltCount = 0;
		bltType=0;
		itemType = -1;
	}
	~player()
	{
		for(int i=0;i<50;i++)
		{
			delete m_blt[i];
		}
	}
	void shoot()
	{
		if(unitOn&&(--unitBltCount==0))
		{
			bltType_Unit();
		}
		if (--bltCount > 0)
			return;
		switch (bltType)
		{
		case 0:bltType_normal(); break;
		case 1:bltType_spread(); break;
		case 2:bltType_allRange(); break;
		case 3:bltType_burst(); break;
		}
	}
	void command(char cmd)
	{
		switch (cmd)
		{
		case 'w':if (judgeYOverflow(cmd))m_y-= m_speed; break;
		case 'a':if (judgeXOverflow(cmd))m_x-= m_speed; break;
		case 's':if (judgeYOverflow(cmd))m_y+= m_speed; break;
		case 'd':if (judgeXOverflow(cmd))m_x+= m_speed; break;
		case 'q':useItem(); break;
		case ' ':bltType = ((bltType == 3) ? 0 : bltType+1); break;
		}
	}
	bool judgeYOverflow(char cmd)
	{
		if(cmd=='s' && m_y + 10>map_height - m_height)
		{
			m_y = map_height - m_height;
			return false;
		}
		else if (cmd=='w' && m_y - 10 < 0)
		{
			m_y = 0;
			return false;
		}
		else
		return true;
	}
	bool judgeXOverflow(char cmd)
	{
		if (cmd=='d' && m_x + 10 > map_width - m_width)
		{
			m_x = map_width - m_width;
			return false;
		}
		else if (cmd=='a' && m_x - 10 < 0)
		{
			m_x = 0;
			return false;
		}
		else
		return true;
	}
	void drawPlayerAndBullet()
	{
		shoot();
		putimage(m_x, m_y, &m_alpha, SRCAND);
		putimage(m_x, m_y, &m_img, SRCPAINT);
		if(shieldOn)
		{
			putimage(m_x+m_width/2-31, m_y+m_height/2-30, &m_shield_alpha, SRCAND);
			putimage(m_x+m_width/2-31, m_y+m_height/2-30, &m_shield, SRCPAINT);
			if(--itemCount <=0)
			{
				shieldOn = false;
			}
		}		
		if (unitOn)
		{
			putimage(m_x + m_width / 2 - m_unit_width / 2, m_y - 20, &m_unit_alpha, SRCAND);
			putimage(m_x + m_width / 2 - m_unit_width / 2, m_y - 20, &m_unit, SRCPAINT);
			if (--itemCount <= 0)
			{
				unitOn = false;
			}
		}
		for (int i = 0; i < 50; i++)
		{
			if (m_blt[i] != 0 && m_blt[i]->deleteBullet(map_width, map_height))
			{
				delete m_blt[i];
				m_blt[i] = 0;
			}
			if (m_blt[i] != 0)
			{
				m_blt[i]->drawBullet();
			}
		}
	}
	void drawItemSlot()
	{
		switch (itemType)
		{
		case 0:putimage(440, 861, &m_item_0); break;
		case 1:putimage(440, 861, &m_item_1); break;
		default:return;
		}
	}
	void useItem()
	{
		switch (itemType)
		{
		case 0: {shieldOn = true; itemCount = 150; } break;
		case 1: {unitOn = true; itemCount = 500; }break;
		default:return; break;
		}
		itemType = -1;
	}
	void bltType_spread()
	{
		for (int i = 0; i < 50-2; i++)
		{
			if (m_blt[i]==0&&m_blt[i+1]==0&&m_blt[i+2]==0)
			{
				m_blt[i] = new bullet(m_x, m_y, m_width, 13, 0);
				m_blt[i+1] = new bullet(m_x+20, m_y+5, m_width, 13, -1.04);
				m_blt[i+2] = new bullet(m_x-20, m_y+5, m_width, 13, 1.04);
				bltCount = 13;
				return;
			}
		}
	}
	void bltType_normal()
	{
		for (int i = 0; i < 50; i++)
		{
			if (m_blt[i] == 0)
			{
				m_blt[i] = new bullet(m_x, m_y, m_width, 13, 0);
				bltCount = 10;
				return;
			}
		}
	}
	void bltType_burst()
	{
		for (int i = 0; i < 50; i++)
		{
			if (m_blt[i] == 0)
			{
				m_blt[i] = new bullet(m_x,m_y,m_width,15,0,1);
				bltCount = 35;
				return;
			}
		}
	}
	void bltType_allRange()
	{
		for (int i = 0; i < 46; i++)
		{
			if (m_blt[i] == 0&&m_blt[i+1]==0 && m_blt[i + 2] == 0 && m_blt[i + 3] == 0 && m_blt[i + 4] == 0)
			{
				m_blt[i] = new bullet(m_x, m_y, m_width, 13, 0);
				m_blt[i+1] = new bullet(m_x+15, m_y+5, m_width, 13, -0.5);
				m_blt[i+2] = new bullet(m_x-15, m_y+5, m_width, 13, 0.5);
				m_blt[i+3] = new bullet(m_x-25, m_y+10, m_width, 13, 1.1);
				m_blt[i+4] = new bullet(m_x+25, m_y+10, m_width, 13, -1.1);
				bltCount = 20;
				return;
			}
		}
	}
	void bltType_Unit()
	{
		for (int i = 0; i < 45; i++)
		{
			if (m_blt[i] == 0 && m_blt[i + 1] == 0 && m_blt[i + 2] == 0 && m_blt[i + 3] == 0 && m_blt[i + 4] == 0 && m_blt[i + 5] == 0)
			{
				m_blt[i] = new bullet(m_x-m_unit_width/2+26, m_y-20, m_width, 13, -0.4,2);
				m_blt[i + 1] = new bullet(m_x+m_unit_width/2-26, m_y-20, m_width, 13, 0.4,2);
				m_blt[i + 2] = new bullet(m_x - m_unit_width / 2 + 14, m_y-12, m_width, 13, -0.8,2);
				m_blt[i + 3] = new bullet(m_x + m_unit_width / 2 - 14, m_y - 12, m_width, 13, 0.8,2);
				m_blt[i + 4] = new bullet(m_x - m_unit_width / 2 + 2, m_y -3, m_width, 13, -1.1,2);
				m_blt[i + 5] = new bullet(m_x + m_unit_width / 2 - 2, m_y - 3, m_width, 13, 1.1,2);
				unitBltCount = 100;
				return;
			}
		}
	}
	void failed()
	{
		destroy playerFailed(m_x, m_y, m_width, m_height);
		while(playerFailed.animation(2)>0)
		{
			Sleep(60);
			FlushBatchDraw();
		}
		return;
	}
};