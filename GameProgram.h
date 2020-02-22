#ifndef __GAME_PROGRAM_H__
#define __GAME_PROGRAM_H__

#include "GameObject.h"
#include <conio.h>

class GameProgram
{
protected:
	GameObject* frame; // Khung game
	int miliSecondForSleep; // Số mili giây chờ
public:
	GameProgram() : frame(NULL), miliSecondForSleep(0) {}
	GameProgram(int frameWidth, int frameHeight, int frameColor, int miliSecondForSleep) : GameProgram()
	{
		setFrameSize(frameWidth, frameHeight);
		setFrameColor(frameColor);
		this->miliSecondForSleep = miliSecondForSleep;
	}
	virtual ~GameProgram()
	{
		if (frame)
			delete frame;
	}

	void setFrameSize(int frameWidth, int frameHeight)
	{
		char** bodyFrame = new char*[frameHeight];
		for (int i = 0; i < frameHeight; i++)
			bodyFrame[i] = new char[frameWidth];
		for (int i = 0; i < frameHeight; i++)
		{
			for (int j = 0; j < frameWidth; j++)
			{
				if (i == 0 || i == frameHeight - 1 || j == 0 || j == frameWidth - 1)
					bodyFrame[i][j] = '.';
				else
					bodyFrame[i][j] = ' ';
			}
		}
		if (frame)
			delete frame;
		frame = new GameObject(bodyFrame, frameWidth, frameHeight, 7, Coord{ 0, 0 }, Direction::NO);
	}
	void setFrameColor(int frameColor)
	{
		frame->setColor(frameColor);
	}
	void setMiliSecondForSleep(int miliSecondForSleep)
	{
		this->miliSecondForSleep = miliSecondForSleep;
	}
	GameObject* getFrame()
	{
		return frame;
	}
	int getMiliSecondForSleep()
	{
		return miliSecondForSleep;
	}

	virtual void init() = 0;
	virtual DWORD WINAPI keyboardEvent() = 0;
	virtual void run() = 0;
};

#endif