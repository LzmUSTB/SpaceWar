#include <graphics.h>
#pragma once
class destroy {
	IMAGE destroy_1, destroy_2, destroy_3;
	IMAGE alpha_1, alpha_2, alpha_3;
	int count;
	int m_x;
	int m_y;
	int m_width;
	int m_height;
	destroy* dPtr[10] = { 0 };
public:
	destroy(){}
	~destroy()
	{
		for (int i = 0; i < 10; i++)
		{
			delete dPtr[i];
		}
	}
	destroy(int x,int y,int width,int height)
	{
		count = 30;
		loadimage(&destroy_1, _T("./images/destroy_1.png"));
		loadimage(&destroy_2, _T("./images/destroy_2.png"));
		loadimage(&destroy_3, _T("./images/destroy_3.png"));
		loadimage(&alpha_1, _T("./images/destroy_1_alpha.png"));
		loadimage(&alpha_2, _T("./images/destroy_2_alpha.png"));
		loadimage(&alpha_3, _T("./images/destroy_3_alpha.png"));
		m_width = destroy_3.getwidth();
		m_height = destroy_3.getheight();
		m_x = x + width/2 - m_width / 2;
		m_y = y + height / 2 - m_height / 2;
	}
	void getInstance(int x, int y, int width, int height)
	{
		for (int i = 0; i < 10; i++)
		{
			if (dPtr[i] == 0)
			{
				dPtr[i] = new destroy(x, y, width, height);
				return;
			}
		}
	}
	int animation(int speed=4)
	{
		if (count <= 30 && count > 20)
		{
			putimage(m_x, m_y, &alpha_1, SRCAND);
			putimage(m_x, m_y, &destroy_1, SRCPAINT);
		}
		if (count <= 20 && count > 10)
		{
			putimage(m_x, m_y, &alpha_2, SRCAND);
			putimage(m_x, m_y, &destroy_2, SRCPAINT);
		}
		if (count <= 10 && count > 0)
		{
			putimage(m_x, m_y, &alpha_3, SRCAND);
			putimage(m_x, m_y, &destroy_3, SRCPAINT);
		}
		count-=speed;
		return count;
	}
	void drawEffects()
	{
		for (int i = 0; i < 10; i++)
		{
			if (dPtr[i] != 0)
			{
				if (dPtr[i]->animation() <= 0)
				{
					delete dPtr[i];
					dPtr[i] = 0;
				}
			}
		}
	}
};