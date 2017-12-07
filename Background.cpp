#include "Background.h"
#include<iostream>
#include<unordered_map>
#include<thread>
Background::Background(const int & width, const int & heigth, SnakeNode * head)
{
	this->bg = std::vector<std::vector<int>>(heigth, std::vector<int>(width, 0));
	SnakeNode * tmp = head;
	while (tmp != nullptr) {
		int x = tmp->getX();
		int y = tmp->getY();
		if (x > 0 && y > 0) {
            this->bg[tmp->getY()][tmp->getX()] = 1;
		}	
		tmp = tmp->getNextNode();
	}
}

Background::~Background()
{
}

void Background::updateBg(SnakeNode * head)
{
	SnakeNode * tmp = head;
	while (tmp != nullptr) {
		int x = tmp->getX();
		int y = tmp->getY();
		if (x >= 0 && y >= 0 && x<getBgWidth() && y<getBgHeight()) {
			this->bg[y][x] = 1;
		}
		tmp = tmp->getNextNode();
	}
}

void Background::drawBg()
{
	for (int i = 0; i < (this->bg.size()); i++) {
		for (int j = 0; j< (this->bg[0].size()); j++) {
			std::cout << this->bg[i][j] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << "ÇëÊäÈë·½Ïò ";
}

int Background::getBgWidth()
{
	return this->bg[0].size();
}

int Background::getBgHeight()
{
	return this->bg.size();
}

void Background::createApple(SnakeNode * head)
{
	std::unordered_map<int,int> snakeNodes;
	std::vector<int> results;
	SnakeNode * tmp = head;
	while (tmp != nullptr) {
		int num = tmp->getY() * bg[0].size() + tmp->getX()+1;
		snakeNodes[num]++;
		tmp = tmp->getNextNode();
	}

	for (int i = 0; i < bg.size(); i++) {
		for (int j = 0; j < bg[0].size(); j++) {
			if (snakeNodes[i * bg[0].size() + j + 1] == 0) {
				results.push_back(i * bg[0].size() + j + 1);
			}
		}
	}
	srand(time(NULL));
	int point = results[rand() % results.size()];
	int px = 0, py = 0;
	if (point % bg[0].size() == 0) {
		px = point / bg[0].size() - 1;
	}
	else {
		px = point / bg[0].size();
	}
	py = point - px * bg[0].size() - 1;
	bg[px][py] = 2;
}

void Background::clearLastSnakeNode(const int & x, const int & y)
{
	if(y>=0&&x>=0)
	    bg[y][x] = 0;
}

void Background::clearBg()
{
	for (int i = 0; i < bg.size(); i++) {
		for (int j = 0; j < bg[0].size(); j++) {
			bg[i][j] = 0;
		}
	}
}

bool Background::isAppleEaten(const int & x, const int & y)
{
	if (x >= 0 && y >= 0 && x<getBgWidth() && y<getBgHeight())
	    return bg[x][y] == 2;
	else 
		return false;
}

 
