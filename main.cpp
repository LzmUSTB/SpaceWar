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
	SetProcessDpiAwareness(PROCESS_PER_MONITOR_DPI_AWARE);
	
	// init
	int score = 0;
	int width = 550;
	int height = 950;
	int screenSize = height - 100;
	initgraph(width, height);
	settextcolor(0xb3001d);
	setbkmode(TRANSPARENT);
	state stateSystem;

	// main loop
	while(1)
	{
		stateSystem.selectMenu();
		stateSystem.startToPlay(width, screenSize);
		EndBatchDraw();
	}
}

