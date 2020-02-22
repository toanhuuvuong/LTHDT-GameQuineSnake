#ifndef __GAME_BASE_FUNCTION_H__
#define __GAME_BASE_FUNCTION_H__

#include <iostream>
#include <Windows.h>

class GameBaseFunction
{
public:
	static void gotoXY(int x, int y)
	{
		HANDLE handle;
		handle = GetStdHandle(STD_OUTPUT_HANDLE);
		COORD nextPostion = { x, y };
		SetConsoleCursorPosition(handle, nextPostion);
	}
	static void textColor(int color)
	{
		HANDLE handle;
		handle = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(handle, color);
	}
	static void drawChar(int x, int y, char c, int color)
	{
		gotoXY(x, y);
		textColor(color);
		std::cout << c;
		textColor(7);
	}
	static void resizeCMD(int width, int height)
	{
		HWND consoleWindow = GetConsoleWindow();
		RECT rect;
		GetWindowRect(consoleWindow, &rect);
		MoveWindow(consoleWindow, rect.left, rect.top, width, height, TRUE);
	}

	virtual void moveLeft(int distance) = 0;
	virtual void moveRight(int distance) = 0;
	virtual void moveUp(int distance) = 0;
	virtual void moveDown(int distance) = 0;
	virtual void rotateLeft() = 0;
	virtual void rotateRight() = 0;
};

#endif