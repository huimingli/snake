#include "Snake.h"

#include<iostream>
#include<thread>

Snake::Snake(const int & snakeBgWidth, const int & snakeBgHeight)
{
	int intitX = 0;
	int intitY = 0;
	head = new SnakeNode(intitX, intitY);
	SnakeNode * tmp = head;
	for (int i = 0; i < 2; i++) {//��ʼ�����������ڵ�
		SnakeNode * node = new SnakeNode(--intitX, intitY);
		tmp->setNextNode(node);
		tmp = tmp->getNextNode();
	}
	direction = 4;//��ʼ������
 
	this->snakeBacground = new Background(snakeBgWidth, snakeBgHeight, head);//���ñ���
	snakeBacground->createApple(head);//����ƻ��
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
			resetSnake();//ҧ���Լ����߳����ϱ߽�������Ϸ
			return false;
		}
		else {//�����µĽڵ�����ͷ��ɾ��β�ڵ㣬�Ӷ�ʹ�����ƶ�
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
		snakeBacground->updateBg(head);//�������нڵ�
	}
	
	
	snakeBacground->drawBg();//������������
	return true;
}

/*
*�߿�ʼ�ƶ�
*/
void Snake::begin()
{
	while (true) {
		system("cls");
		bool isplaying = updateSnack();//ÿ0.5���ƶ�һ����
		if (!isplaying) {
			std::cout << "�˳�������0:";
			break;
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}
}
 
/*
*�����ߵ�ǰ����
*/
void Snake::setDirection()
{	 
	while (true) {
		int d;
		std::cin >> d;
		if ((1 == d || 2 == d) && (1 == direction || 2 == direction))//������ʱֻ�����һ�����
			continue;
		else if ((3 == d || 4 == d) && (3 == direction || 4 == direction))//������ʱֻ�ܻ����·���
			continue;
		else if (d == 0)
			break;
		else
		    this->direction = d;				 
	}
}

/*
*����Ƿ�ҧ���Լ�
*/
bool Snake::hasEatenSelf()
{
	SnakeNode * tmp = head->getNextNode()->getNextNode();
	//��ͷ���ܻ�Ҫ�����ĸ����ߵ��ĸ��Ժ�Ľڵ㣬���Դӵ��ĸ���ʼ�ж��Ƿ�ҧ���Լ�
	while (tmp->getNextNode() != nullptr) {
		if (tmp->getNextNode()->getX() == head->getX() && tmp->getNextNode()->getY() == head->getY()) {
			return true;
		}
		tmp = tmp->getNextNode();
	}
	return false;
}

/*
*��Ϸ�����������ߵ�״̬
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
	direction = 4;//��ʼ������
	snakeBacground->clearBg();
	snakeBacground->createApple(head);
}

/*
*ɾ�����һ���ڵ�
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
