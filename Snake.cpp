#include "Snake.h"

#include<iostream>
#include<thread>

Snake::Snake(const int & snakeBgWidth, const int & snakeBgHeight)
{
	int intitX = 0;
	int intitY = 0;
	head = new SnakeNode(intitX, intitY);
	SnakeNode * tmp = head;
	for (int i = 0; i < 2; i++) {//初始化蛇有三个节点
		SnakeNode * node = new SnakeNode(--intitX, intitY);
		tmp->setNextNode(node);
		tmp = tmp->getNextNode();
	}
	direction = 4;//初始化向右
 
	this->snakeBacground = new Background(snakeBgWidth, snakeBgHeight, head);//设置背景
	snakeBacground->createApple(head);//创建苹果
}

Snake::~Snake()
{

	if (snakeBacground != nullptr) {
		delete snakeBacground;
		snakeBacground = nullptr;
	}
		
	while (head != nullptr) {
		SnakeNode * tmp = head;
		head = head->getNextNode();
		delete tmp;
		tmp = nullptr;
	}
}


bool Snake::updateSnack()
{
	SnakeNode * moveHead = nullptr;
	switch (this->direction)
	{
	case 1:
		if (head->getY() < 0|| hasEatenSelf()) {
			resetSnake();//咬到自己或者超出上边界重启游戏
			return false;
		}
		else {//创建新的节点在蛇头，删除尾节点，从而使得蛇移动
			moveHead = new SnakeNode(head->getX(), head->getY() - 1);
			if (snakeBacground->isAppleEaten(head->getY() - 1, head->getX())) {
				snakeBacground->createApple(head);
			}
			else {
				deleteLastNode();
			}		
		}		    
		break;
	case 2:
		if (head->getY() + 1 > snakeBacground->getBgHeight() || hasEatenSelf()) {
			resetSnake(); return false;
		}
		else{
			moveHead = new SnakeNode(head->getX(), head->getY() + 1);
			if (snakeBacground->isAppleEaten(head->getY() + 1, head->getX())) {
				snakeBacground->createApple(head);
			}
			else {
				deleteLastNode();
			}
		}
		break;
	case 3:
		if (head->getX() < 0 || hasEatenSelf()) {
			resetSnake(); return false;
		}
		else {
			moveHead = new SnakeNode(head->getX() - 1, head->getY());
			if (snakeBacground->isAppleEaten(head->getY(), head->getX() - 1)) {
				snakeBacground->createApple(head);
			}
			else {
				deleteLastNode();
			}
		}
		break;
	case 4:
		if (head->getX() + 1 > snakeBacground->getBgWidth() || hasEatenSelf()) {
			resetSnake(); return false;
		}
		else {
			moveHead = new SnakeNode(head->getX() + 1, head->getY());
			if (snakeBacground->isAppleEaten(head->getY(), head->getX() + 1)) {
				snakeBacground->createApple(head);
			}
			else {
				deleteLastNode();
			}
		}
		break;
	default:
		if (head->getX() + 1 > snakeBacground->getBgWidth() || hasEatenSelf()) {
			resetSnake(); return false;
		}
		else {
			moveHead = new SnakeNode(head->getX() + 1, head->getY());
			if (snakeBacground->isAppleEaten(head->getY(), head->getX() + 1)) {
				snakeBacground->createApple(head);
			}
			else {
				deleteLastNode();
			}
		}
		break;
	}
	if (moveHead != nullptr) {
		moveHead->setNextNode(head);
		head = moveHead;
		snakeBacground->updateBg(head);//更新所有节点
	}
	
	
	snakeBacground->drawBg();//画出背景和蛇
	return true;
}

/*
*蛇开始移动
*/
void Snake::begin()
{
	while (true) {
		system("cls");
		bool isplaying = updateSnack();//每0.5秒移动一下蛇
		if (!isplaying) {
			std::cout << "退出请输入0:";
			break;
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}
}
 
/*
*设置蛇当前方向
*/
void Snake::setDirection()
{	 
	while (true) {
		int d;
		std::cin >> d;
		if ((1 == d || 2 == d) && (1 == direction || 2 == direction))//上下走时只能左右换方向
			continue;
		else if ((3 == d || 4 == d) && (3 == direction || 4 == direction))//左右走时只能换上下方向
			continue;
		else if (d == 0)
			break;
		else
		    this->direction = d;				 
	}
}

/*
*检查是否咬到自己
*/
bool Snake::hasEatenSelf()
{
	SnakeNode * tmp = head->getNextNode()->getNextNode();
	//蛇头可能会要到第四个或者第四个以后的节点，所以从第四个开始判断是否咬到自己
	while (tmp->getNextNode() != nullptr) {
		if (tmp->getNextNode()->getX() == head->getX() && tmp->getNextNode()->getY() == head->getY()) {
			return true;
		}
		tmp = tmp->getNextNode();
	}
	return false;
}

/*
*游戏重启，重置蛇的状态
*/
void Snake::resetSnake()
{
	SnakeNode *tmp = head;
	while (tmp->getNextNode()->getNextNode()->getNextNode()) {
		deleteLastNode();
	}
	int intitX = 0;
	tmp = head;
	for (int i = 0; i < 2; i++) {
		tmp->setX(intitX--);
		tmp->setY(0);
		tmp = tmp->getNextNode();
	}
	direction = 4;//初始化向右
	snakeBacground->clearBg();
	snakeBacground->createApple(head);
}

/*
*删除最后一个节点
*/
void Snake::deleteLastNode()
{
	SnakeNode * tmp = head;
	while (tmp->getNextNode()->getNextNode() != nullptr) {
		tmp = tmp->getNextNode();
	}
	SnakeNode * delNode = tmp->getNextNode();
	snakeBacground->clearLastSnakeNode(delNode->getX(),delNode->getY());
	tmp->setNextNode(nullptr);
	delete delNode;
	delNode = nullptr;
}
