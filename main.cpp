#include<iostream>
#include"Snake.h"
#include<vector>
#include<thread>
#include<windows.h> 

#define KEY_DOWN(VK_NONAME) ((GetAsyncKeyState(VK_NONAME) & 0x8000) ? 1:0) //��Ҫ�ģ����Ǳ�������  
using namespace std;


int main() {
	  Snake s(20,20);
	
	thread t(&Snake::begin,&s);
	

	thread t2(&Snake::setDirection, &s);
	
	t.join();
	t2.join();

	
	
	system("pause");
}