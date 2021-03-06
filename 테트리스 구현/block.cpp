#include <iostream>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include "block.h"
using namespace std;

void pull(int block[4][4]);

const int bn = 3;
int model[bn][4][4] =
{
	{
		1,1,1,0,
		0,0,1,0,
		0,0,0,0,
		0,0,0,0,
	},
	{
		1,1,1,1,
		0,0,0,0,
		0,0,0,0,
		0,0,0,0,
	},
	{
		1,1,0,0,
		0,1,1,0,
		0,0,0,0,
		0,0,0,0,
	},
};

void setBlock(int block[4][4]) {	

	srand(time(0));
	int n = rand() % bn; // 0 ~ 6 값까지 랜덤한 숫자 저장

	//bn block copy
	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 4; x++) {
			block[y][x] = model[n][y][x];
		}
	}
}

void spin(int block[4][4])
{
	int temp[4][4];
	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 4; x++) {
			temp[x][3 - y] = block[y][x];
		}
	}

	memcpy(block, temp, 4 * 4 * 4); //16 * 4 Byte

	pull(block);
}

void pull(int block[4][4])
{
	//좌표구하기
	int minY = 9;
	int minX = 9;
	int maxY = 0;
	int maxX = 0;

	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 4; x++) {
			if (block[y][x] == 0) continue;
			if (minY > y) minY = y;
			if (minX > x) minX = x;
			if (maxY < y) maxY = y;
			if (maxX < x) maxX = x;
		}
	}

	//2. 당기기
	int temp[4][4] = { 0 };
	for (int y = minY; y <= maxY; y++) {
		for (int x = minX; x <= maxX; x++) {
			temp[y - minY][x - minX] = block[y][x];
		}
	}

	//3. temp --> block
	memcpy(block, temp, 4 * 4 * 4);
}
