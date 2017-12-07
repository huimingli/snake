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
	int direction;//1���ϣ�2���£�3����4����
	Background *snakeBacground;
};

