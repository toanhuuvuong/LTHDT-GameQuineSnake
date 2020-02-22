#ifndef __QUINE_SNAKE_H__
#define __QUINE_SNAKE_H__

#include "GameProgram.h"
#include <fstream>
#include <vector>
#include <time.h>

class GameQuineSnakeOOP : public GameProgram
{
private:
	std::vector<GameObject*> blocks; // Thân con rắn
	GameObject* fruit; // Thức ăn
	int keyPressed; // Khóa nhận từ bàn phím
	int score; // Điểm
	
	GameObject* createCodeTable(char* fileName)
	{
		std::ifstream inFile(fileName);

		if (!inFile)
		{
			std::cerr << "Error read file " << fileName << " :(" << std::endl;
			return NULL;
		}
		int width, height;
		char** body = NULL; 
		char buff[500];

		inFile.getline(buff, 500);
		width = strlen(buff);
		height = 1;
		while (!inFile.eof())
		{
			inFile.getline(buff, 500);
			height++;
		}
		body = new char*[height];
		for (int i = 0; i < height; i++)
			body[i] = new char[width];

		inFile.seekg(0);

		for (int i = 0; i < height; i++)
		{
			inFile.getline(buff, 500);
			memcpy(body[i], buff, width);
		}
		GameObject* result = new GameObject(body, width, height, 7, Coord{ 0, 0 }, Direction::NO, true);

		for (int i = 0; i < height; i++)
			delete[] body[i];
		delete[] body;
		inFile.close();

		return result;
	}
	GameObject* createBlock(Coord coord)
	{
		return new GameObject({ frame->getBody()[coord.y][coord.x] }, 1, 1, 172, coord, Direction::NO);
	}
	bool checkCollide()
	{
		return (blocks[0]->getCoord().x == fruit->getCoord().x && blocks[0]->getCoord().y == fruit->getCoord().y);
	}
	bool checkGameOver()
	{
		int size = blocks.size();
		for (int i = 1; i < size; i++)
		{
			if (blocks[0]->getCoord().x == blocks[i]->getCoord().x && blocks[0]->getCoord().y == blocks[i]->getCoord().y)
				return true;
		}
		if (blocks[0]->getCoord().x > frame->getWidth() - 1 || 
			blocks[0]->getCoord().x < 0 || 
			blocks[0]->getCoord().y > frame->getHeight() - 1 || 
			blocks[0]->getCoord().y < 0)
			return true;
		return false;
	}
	void addBlock()
	{ 
		int size = blocks.size();
		Coord coord;
		if (blocks[size - 1]->getDirection() == Direction::LEFT)
			coord = Coord{ blocks[size - 1]->getCoord().x + 1, blocks[size - 1]->getCoord().y };
		else if (blocks[size - 1]->getDirection() == Direction::RIGHT)
			coord = Coord{ blocks[size - 1]->getCoord().x - 1, blocks[size - 1]->getCoord().y };
		else if (blocks[size - 1]->getDirection() == Direction::UP)
			coord = Coord{ blocks[size - 1]->getCoord().x, blocks[size - 1]->getCoord().y + 1 };
		else if (blocks[size - 1]->getDirection() == Direction::DOWN)
			coord = Coord{ blocks[size - 1]->getCoord().x, blocks[size - 1]->getCoord().y - 1 };
		else
			std::cerr << "Error blocks haven't moved :(" << std::endl;
		GameObject* newBlock = createBlock(coord);
		newBlock->setDirection(blocks[size - 1]->getDirection());
		blocks.push_back(newBlock);
	}
	void eraseBlocks()
	{
		int size = blocks.size();
		for (int i = 0; i < size; i++)
			blocks[i]->erase();
	}
	void setVisbleBlocks(bool isVisible)
	{
		int size = blocks.size();
		for (int i = 0; i < size; i++)
			blocks[i]->setVisible(isVisible);
	}
	void updateBlocks()
	{
		int size = blocks.size();
		for (int i = size - 1; i > 0; i--)
			*blocks[i] = *blocks[i - 1];
	}
	void drawBlocks()
	{
		int size = blocks.size();
		for (int i = 0; i < size; i++)
			blocks[i]->draw();
	}
	void randomFruit()
	{
		int x = rand() % frame->getWidth(), y = rand() % frame->getHeight();
		fruit->setCoord(Coord{ x, y });
		fruit->setBody({ frame->getBody()[y][x] });
		fruit->draw();
	}
public:
	GameQuineSnakeOOP() : GameProgram()
	{
		fruit = NULL;
		keyPressed = ' ';
		score = 0;
	}
	~GameQuineSnakeOOP()
	{
		if (fruit)
			delete fruit;
	}

	void init()
	{
		GameBaseFunction::resizeCMD(650, 620);
		// GameProgram Settings
		frame = createCodeTable("CodeTable.txt");
		frame->draw();
		miliSecondForSleep = 100;
		// GameQuineSnakeOOP Settings
		blocks.push_back(createBlock(Coord{ 0, 0 }));
		blocks[0]->draw();

		srand(time(NULL));
		fruit = new GameObject({ ' ' }, 1, 1, 206, Coord{ 0, 0 }, Direction::NO, true);
		randomFruit();
	}
	DWORD WINAPI keyboardEvent()
	{
		if (_kbhit())
		{
			keyPressed = _getch();
			switch (keyPressed)
			{
			case 'A': case 'a':
				blocks[0]->setDirection(LEFT);
				break;
			case 'D': case 'd':
				blocks[0]->setDirection(RIGHT);
				break;
			case 'W': case 'w':
				blocks[0]->setDirection(UP);
				break;
			case 'S': case 's':
				blocks[0]->setDirection(DOWN);
				break;
			}
		}
		switch (blocks[0]->getDirection())
		{
		case LEFT:
			blocks[0]->moveLeft(1);
			break;
		case RIGHT:
			blocks[0]->moveRight(1);
			break;
		case UP:
			blocks[0]->moveUp(1);
			break;
		case DOWN:
			blocks[0]->moveDown(1);
			break;
		}
		if (checkGameOver())
		{
			system("cls");
			GameBaseFunction::gotoXY(frame->getWidth() / 2 - 6, frame->getHeight() / 2 - 1);
			std::cout << "GAME OVER :(" << std::endl;
			return 1;
		}
		blocks[0]->setBody({ frame->getBody()[blocks[0]->getCoord().y][blocks[0]->getCoord().x] });

		return 0;
	}
	void run()
	{
		init();
		while (true)
		{
			eraseBlocks();

			setVisbleBlocks(false);

			updateBlocks();

			if (keyboardEvent())
				return;

			if (checkCollide())
			{
				addBlock();
				randomFruit();
			}
			
			setVisbleBlocks(true);

			drawBlocks();

			Sleep(miliSecondForSleep);
		}
	}
};

#endif