#include "SnakeNode.h"

int SnakeNode::getX()
{
	return this->x;
}

int SnakeNode::getY()
{
	return this->y;
}

void SnakeNode::setX(const int & px)
{
	this->x = px;
}

void SnakeNode::setY(const int & py)
{
	this->y = py;
}

SnakeNode * SnakeNode::getNextNode()
{
	return this->nextNode;
}

void SnakeNode::setNextNode(SnakeNode * next)
{
	this->nextNode = next;
}

SnakeNode::~SnakeNode()
{
}
