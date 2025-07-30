#pragma once
#include <graphics.h>
#include <math.h>
#include <conio.h>
#include "player.cpp"
#include "destroy.cpp"
#include "enemies.cpp"
#include "object.cpp"
#include "item.cpp"

class state {
private:
	int score;
	bool intro = true;
	int intro_Y = -850;
	int scroll_Y=-845;
	IMAGE m_menuImg;
	IMAGE m_instruction;
	IMAGE m_result;
	IMAGE m_gameBG;
	IMAGE m_scroll;
public:
	state()
	{
		score = 0;
		loadimage(&m_menuImg, _T("./images/menu.png"));
		loadimage(&m_instruction, _T("./images/instruction.png"));
		loadimage(&m_result, _T("./images/menu_result.png"));
		loadimage(&m_gameBG, _T("./images/bg.png"));
		loadimage(&m_scroll, _T("./images/scroll.png"));
	}
	void systemPause()
	{
		while (1)
		{
			if (_kbhit())
			{
				char pCmd = _getch();

				if (pCmd == 27)
					return;
			}
		}
	}
	void printScore(int x=188,int y=855)
	{
		TCHAR c[6];
		_stprintf_s(c, _T("%d"), score);
		settextstyle(55, 0, _T("Trebuchet MS"));
		outtextxy(x, y, c);
	}
	void selectMenu()
	{
		cleardevice();
		putimage(0, 0, &m_menuImg);
		while (1)
		{
			if (_kbhit())
			{
				char cmd = _getch();
				switch (cmd)
				{
				case ' ':return; break;
				}
			}
		}
	}
	void scroll()
	{
		if (intro == true)
			return;
		putimage(0, scroll_Y, &m_scroll);
		scroll_Y+=5;
		if (scroll_Y == 0) { scroll_Y = -850; }
	}
	void introduction()
	{
		if (intro == false)
			return;
		putimage(0, intro_Y, &m_instruction);
		intro_Y += 2;
		if (intro_Y == 0) { intro = false; }
	}
	void printResult()
	{
		BeginBatchDraw();
		putimage(0, 0, &m_result);
		printScore(327,402);
		FlushBatchDraw();
		while (1)
		{
			if (_kbhit())
			{
				char cmd = _getch();
				switch (cmd)
				{
				case ' ':return;
				}
			}
		}
	}
	void startToPlay(int width,int screenSize)
	{
		bool ifFailed = false;
		itemSystem ItemSystem;
		player p1(width, screenSize);
		destroy destroySystem;
		enemies enemySystem(width,screenSize);
		int timeCount = 66;
		srand((unsigned int)time(NULL));
		BeginBatchDraw();

		// main loop
		while (1)
		{
			if (ifFailed) 
			{ 
				p1.failed(); 
				printResult();
				score = 0; intro = true;
				intro_Y = -850;
				scroll_Y = -845;
				return; 
			}
			if (timeCount-- == 0) { score++; timeCount = 66; }
			
			cleardevice();
			scroll();
			introduction();
			putimage(0, 850, &m_gameBG);
			p1.drawItemSlot();
			enemySystem.createEnemy(score);
			ItemSystem.itemLauncher(rand() % 310, rand()%2);
			ItemSystem.drawItemBlock();
			ItemSystem.isItemHit(&p1,p1.itemType);
			enemySystem.drawEnemies();
			// enemy collision
			for (int i = 0; i <50; i++)
			{
				if (p1.m_blt[i] != 0)
					score += enemySystem.isEnemiesHit(p1.m_blt[i], &destroySystem);
			}

			p1.drawPlayerAndBullet();
			
			// player collision
			for (int i = 0; i < 30; i++)
			{
				if (p1.shieldOn) { break; }
				if (enemySystem.ePtr[i] != 0)
				{
					if (object::isHit(enemySystem.ePtr[i],&p1))
					{
						ifFailed = true;
					}
				}
			}
			for (int i = 0; i < 50; i++)
			{
				if (p1.shieldOn) { break; }
				if (enemySystem.m_blt[i] != 0)
				{
					if (object::isHit(&p1, enemySystem.m_blt[i]))
					{
						ifFailed = true;
					}
				}
			}

			printScore();
			destroySystem.drawEffects();
			
			// input
			if (_kbhit())
			{
				char cmd = _getch();
				switch (cmd)
				{
				case 27:systemPause(); break;
				default:p1.command(cmd); break;
				}
			}
			FlushBatchDraw();
			
			// frame limit
			Sleep(50);
		}
	}
};