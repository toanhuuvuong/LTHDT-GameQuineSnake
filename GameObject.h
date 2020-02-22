#ifndef __GAME_OBJECT_H__
#define __GAME_OBJECT_H__

#include "GameBaseFunction.h"
#include "GameState.h"
#include "Coord.h"

class GameObject : public GameBaseFunction
{
protected:
	char** body; // hình dáng nhân vật
	int width; // chiều rộng nhân vật
	int height; // chiều cao nhân vật
	int color; // màu nhân vật
	Coord coord; // tọa độ nhân vật
	Direction direction; // hướng chuyển động
	bool isVisible; // Có thể nhìn thấy
public:
	GameObject() : body(NULL), width(0), height(0), color(7), coord(Coord{-1, -1}), direction(NO), isVisible(false) {}
	GameObject(char** body, int width, int height, int color, Coord coord, Direction direction, bool isVisible = false) : GameObject()
	{
		setSize(width, height);
		setBody(body);
		this->color = color;
		this->coord = coord;
		this->direction = direction;
		this->isVisible = isVisible;
	}
	GameObject(std::initializer_list<char> body, int width, int height, int color, Coord coord, Direction direction, bool isVisible = false) : GameObject()
	{
		setSize(width, height);
		setBody(body);
		this->color = color;
		this->coord = coord;
		this->direction = direction;
		this->isVisible = isVisible;
	}
	GameObject(const GameObject &other) : GameObject(other.body, other.width, other.height, other.color, other.coord, other.direction, other.isVisible) {}
	~GameObject()
	{
		if (body)
		{
			for (int i = 0; i < height; i++)
				delete[] body[i];
			delete[] body;
		}
	}

	GameObject& operator=(const GameObject &other)
	{
		setSize(other.width, other.height);
		setBody(other.body);
		color = other.color;
		coord = other.coord;
		direction = other.direction;
		isVisible = other.isVisible;
		return *this;
	}
	
	void setBody(char** body)
	{
		if (body && width != 0 && height != 0)
		{
			for (int i = 0; i < height; i++)
			{
				for (int j = 0; j < width; j++)
					this->body[i][j] = body[i][j];
			}
		}
	}
	void setBody(std::initializer_list<char> body)
	{
		if (body.size() != 0 && width != 0 && height != 0)
		{
			for (int i = 0; i < height * width; i++)
				this->body[i / width][i % width] = *(body.begin() + i);
		}
	}
	void setSize(int width, int height)
	{
		if (body)
		{
			for (int i = 0; i < this->height; i++)
				delete[] body[i];
			delete[] body;
		}
		body = new char*[height];
		for (int i = 0; i < height; i++)
			body[i] = new char[width];

		this->width = width;
		this->height = height;
	}
	void setColor(int color)
	{
		this->color = color;
	}
	void setCoord(Coord coord)
	{
		this->coord = coord;
	}
	void setDirection(Direction direction)
	{
		this->direction = direction;
	}
	void setVisible(bool isVisible)
	{
		this->isVisible = isVisible;
	}
	char** getBody()
	{
		return body;
	}
	int getWidth()
	{
		return width;
	}
	int getHeight()
	{
		return height;
	}
	int getColor()
	{
		return color;
	}
	Coord getCoord()
	{
		return coord;
	}
	Direction getDirection()
	{
		return direction;
	}
	bool getVisible()
	{
		return isVisible;
	}

	void erase()
	{
		if (isVisible)
		{
			for (int i = 0; i < height; i++)
			{
				for (int j = 0; j < width; j++)
						drawChar(coord.x + j, coord.y + i, body[i][j], 7);
			}
		}
	}
	void draw()
	{
		if (isVisible)
		{
			for (int i = 0; i < height; i++)
			{
				for (int j = 0; j < width; j++)
						drawChar(coord.x + j, coord.y + i, body[i][j], color);
			}
		}
	}

	void moveLeft(int distance)
	{
		direction = Direction::LEFT;
		erase();
		coord.x -= distance;
		draw();
	}
	void moveRight(int distance)
	{
		direction = Direction::RIGHT;
		erase();
		coord.x += distance;
		draw();
	}
	void moveUp(int distance)
	{

		direction = Direction::UP;
		erase();
		coord.y -= distance;
		draw();
	}
	void moveDown(int distance)
	{
		direction = Direction::DOWN;
		erase();
		coord.y += distance;
		draw();
	}

	void rotateLeft()
	{
		erase();
		char** temp = new char*[width];
		for (int i = 0; i < width; i++)
			temp[i] = new char[height];
		for (int i = 0; i < width; i++)
		{
			for (int j = 0; j < height; j++)
				temp[i][j] = body[j][width - i - 1];
		}
		setCoord(Coord{ coord.x + width / 2 - height / 2, coord.y + height / 2 - width / 2 });
		setSize(height, width);
		setBody(temp);
		for (int i = 0; i < height; i++)
			delete[] temp[i];
		delete[] temp;
		draw();
	}
	void rotateRight()
	{
		erase();
		char** temp = new char*[width];
		for (int i = 0; i < width; i++)
			temp[i] = new char[height];
		for (int i = 0; i < width; i++)
		{
			for (int j = 0; j < height; j++)
				temp[i][j] = body[height - j - 1][i];
		}
		setCoord(Coord{ coord.x + width / 2 - height / 2, coord.y + height / 2 - width / 2 });
		setSize(height, width);
		setBody(temp);
		for (int i = 0; i < height; i++)
			delete[] temp[i];
		delete[] temp;
		draw();
	}
};

#endif