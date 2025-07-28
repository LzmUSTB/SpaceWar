#pragma once
#include "object.cpp"
#include <graphics.h>

class itemBlock :public object {
	friend class itemSystem;
private:
	int m_type;
	IMAGE m_item;
	IMAGE m_alpha;
public:
	itemBlock(int x, int type)
	{
		loadimage(&m_item, _T("./images/item.png"));
		loadimage(&m_alpha, _T("./images/item_alpha.png"));
		m_x = x;
		m_y = 1 - m_height;
		m_height = m_item.getheight();
		m_width = m_item.getwidth();
		m_type = type;
		m_speed = 6 + m_type * 2;
	}
	void draw()
	{
		putimage(m_x, m_y, &m_alpha, SRCAND);
		putimage(m_x, m_y, &m_item, SRCPAINT);
		m_y += m_speed;
	}
	bool ifDelete()
	{
		if (m_y < 0 - m_height || m_y > map_height-m_height || m_x<0 - m_width || m_x>map_width)
		{
			return true;
		}
		return false;
	}
};

class itemSystem {
public:
	itemBlock* m_ptr;
	int m_count;
	itemSystem()
	{
		m_ptr = 0;
		m_count = 700;
	}
	void itemLauncher(int x, int type)
	{
		if (m_ptr == 0&&--m_count==0)
		{
			m_ptr = new itemBlock(x, type);
			m_count = 600;
		}
	}
	void drawItemBlock()
	{
		if (m_ptr == 0)
			return;
		m_ptr->draw();
		if (m_ptr->ifDelete())
		{
			delete m_ptr;
			m_ptr = 0;
		}
	}
	void isItemHit(object* ptr,int& type)
	{
		if (m_ptr == 0)
			return;
		if (object::isHit(ptr, m_ptr))
		{
			type = m_ptr->m_type;
			delete m_ptr;
			m_ptr = 0;
			return;
		}
	}
};