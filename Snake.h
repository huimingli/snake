#pragma once
#include"Background.h"
#include"SnakeNode.h"
class Snake
{
public:
	Snake(const int & snakeBgWidth,const int & snakeBgHeight);
	~Snake();
	bool updateSnack();
	void begin();
	void setDirection();
	bool hasEatenSelf();
private:
	SnakeNode *head;
	void resetSnake();
	void deleteLastNode();
	int direction;//1向上，2向下，3向左，4向右
	Background *snakeBacground;
};

