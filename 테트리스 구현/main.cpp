#include <iostream>
#include <cstring>
#include <Windows.h>
#include "block.h"

using namespace std;

int block[4][4];
int map[10][10] =
{
	1,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,1,
	1,1,1,1,1,1,1,1,1,1,
};

int dy = 0;
int dx = 3;

void print()
{
	int temp[10][10] = { 0 };
	memcpy(temp, map, 10 * 10 * 4);
	//1. block 을 temp에 copy 
	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 4; x++) {
			if (block[y][x] == 0) continue;
			temp[dy + y][dx + x] = block[y][x];
		}
	}

	//2. temp를 출력
	system("cls");
	for (int y = 0; y < 10; y++) {
		for (int x = 0; x < 10; x++) {
			if (temp[y][x] == 0) cout << " ";
			else cout << "#";
		}
		cout << "\n";
	}
	Sleep(100);
}

int isStack(int ny, int nx) {

	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 4; x++) {
			if (block[y][x] == 0) continue;
			if (map[ny + y][nx + x] == 1) return 1;
		}
	}
	return 0;
}

void down()
{
	if (isStack(dy + 1, dx) == 0) dy++;
	else {
		
		//바닥에 닿으면 copy
		for (int y = 0; y < 4; y++) {
			for (int x = 0; x < 4; x++) {
				if (block[y][x] == 0) continue;
				map[dy + y][dx + x] = 1;
			}
		}

		//초기화
		dy = 0;
		dx = 3;
		setBlock(block);
	}
}

int main()
{
	setBlock(block);
	spin(block);

	int cnt = 1;
	while (1)
	{
		cnt++;
		if (cnt % 10 == 0) down();

		print();

		if (GetAsyncKeyState(VK_UP) & 0x8001) {
			spin(block);
			if (isStack(dy, dx) == 1) {
				spin(block);
				spin(block);
				spin(block);
			}
		}
		if (GetAsyncKeyState(VK_DOWN) & 0x8001) {
			down();
		}
		if (GetAsyncKeyState(VK_LEFT) & 0x8001) {
			if (isStack(dy, dx - 1) == 0) dx--;
		}
		if (GetAsyncKeyState(VK_RIGHT) & 0x8001) {
			if (isStack(dy, dx + 1) == 0) dx++;
		}
	}
	

	return 0;
}