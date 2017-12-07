#pragma once
#include<vector>
#include"SnakeNode.h"
class Background
{
public:
	Background(const int &width, const int &heigth, SnakeNode * head);
	~Background();
	void updateBg(SnakeNode * head);
	void drawBg();
	int getBgWidth();
	int getBgHeight();
	void createApple(SnakeNode * head);
	void clearLastSnakeNode(const int & x, const int & y);
	void clearBg();
	bool isAppleEaten(const int & x, const int & y);
private:
	std::vector<std::vector<int>> bg;
};

