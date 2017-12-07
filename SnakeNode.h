#pragma once
class SnakeNode
{
public:

	SnakeNode(const int &x, const int &y) :x(x), y(y),nextNode(nullptr) {}
	int getX();
	int getY();
	void setX(const int &x);
	void setY(const int &Y);
	SnakeNode * getNextNode();
	void setNextNode(SnakeNode * next);
	~SnakeNode();
private:
	int x;
	int y;
	SnakeNode * nextNode;
};

