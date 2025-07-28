#define WINVER 0x0A00
#define _WIN32_WINNT 0x0A00

#include "state.cpp"
#include <graphics.h>
#include <conio.h>
#include <ShellScalingApi.h>
#pragma comment(lib, "Shcore.lib")
#include <Windows.h>


int main()
{
	//使窗口大小不受系统影响
	SetProcessDpiAwareness(PROCESS_PER_MONITOR_DPI_AWARE);
	//初始化
	int score = 0;
	int width = 550;
	int height = 950;
	int screenSize = height - 100;
	initgraph(width, height);
	settextcolor(0xb3001d);
	setbkmode(TRANSPARENT);
	state stateSystem;
	//游戏循环
	while(1)
	{
		stateSystem.selectMenu();
		stateSystem.startToPlay(width, screenSize);
		EndBatchDraw();
	}
}

