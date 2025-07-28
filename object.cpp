#pragma once
#include <graphics.h>

class object {
protected:
	int m_x;
	int m_y;
	int m_width;
	int m_height;
	int m_speed;
	int map_width=550;
	int map_height=850;
public:
	static bool isHit(object* ptr1,object* blt)
	{
		int adjust = 0;
		if (ptr1 == 0 || blt == 0)
			return false;
		if (ptr1->m_x - blt->m_x > blt->m_width || ptr1->m_x+(ptr1->m_width)<blt->m_x)
			return false;
		if (ptr1->m_y - blt->m_y > blt->m_height || ptr1->m_y+(ptr1->m_height)< blt->m_y)
			return false;
		if (blt->m_x > 10 && blt->m_y > 10)
		{
			adjust = 5;
		}
		for (int i = 0+adjust; i < blt->m_width-adjust;i++)
		{
			for (int j = 0 + adjust; j < blt->m_height-adjust; j++)
			{
				if (getpixel(blt->m_x + i, blt->m_y + j) != BLACK&& getpixel(blt->m_x + i, blt->m_y + j) != 0x000033)
				{
					
					return true;
				}
			}
		}
		return false;
	}
};