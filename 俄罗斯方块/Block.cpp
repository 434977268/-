#include "Block.h"
#include <stdlib.h>
using namespace std;

IMAGE* Block::imgs[7] = { NULL, };
int Block::size = 36;


Block::Block()
{
	if (imgs[0] == NULL) {
		IMAGE imgTmp;
		loadimage(&imgTmp, "res/tiles.png");
		SetWorkingImage(&imgTmp);
		for (int i = 0; i < 7; i++)
		{
			imgs[i] = new IMAGE;
			getimage(imgs[i], i * size, 0, size, size);
		}
		SetWorkingImage();
	}

	int blocks[7][4] = {
		1,3,5,7,//I
		2,4,5,7,//Z 1��
		3,5,4,6,//Z 2��
		3,5,4,7,//T
		2,3,5,7,//L
		3,5,7,6,//J
		2,3,4,5,//��
	};

	//������ɷ���
	blockType = 1 + rand() % 7;//(1~7)
	//��ʼ����������
	for (int i = 0; i < 4; i++)
	{
		int value = blocks[blockType - 1][i];
		this->smallBlocks[i].row = value / 2;
		this->smallBlocks[i].col = value % 2;
	}

	img = imgs[blockType - 1];
}

void Block::Drop()
{
	for (int i = 0; i < 4; i++)
	{
		smallBlocks[i].row++;
	}

	/*for (auto& block : smallBlocks) {
		block.row++;
	}*/
}



void Block::Rotation()
{
}

void Block::Draw(int leftMargin, int topMargin)
{
	for (size_t i = 0; i < 4; i++)
	{
		int x = leftMargin + this->smallBlocks[i].col * size;
		int y = topMargin + this->smallBlocks[i].row * size;
		putimage(x, y, img);
	}
}

Block& Block::operator=(const Block& other)
{
	if (this == &other)
		return *this;

	this->blockType = other.blockType;
	for (int i = 0; i < 4; i++)
	{
		this->smallBlocks[i] = other.smallBlocks[i];
	}
	return *this;
}

IMAGE** Block::getImage()
{

	return imgs;
}

Point* Block::getSmallBlocks()
{
	return nullptr;
}

bool Block::blockInMap(const vector<vector<int>>& map)
{
	int rows = map.size();
	int cols = map[0].size();
	for (int i = 0; i < 4; i++)
	{
		if (smallBlocks[i].col < 0 || smallBlocks[i].col >= cols ||
			smallBlocks[i].row < 0 || smallBlocks[i].row >= rows ||
			map[smallBlocks[i].row][smallBlocks[i].col]) {
			return false;
		}
	}
	return true;
}

void Block::Rotate()
{
	Point p = smallBlocks[1];
	for (int i = 0; i < 4; i++)
	{
		Point tmp = smallBlocks[i];
		smallBlocks[i].col = p.col - tmp.row + p.row;
		smallBlocks[i].row = p.row + tmp.col - p.col;
	}
}

void Block::solidify(vector<vector<int>>& map)
{
	for (int i = 0; i < 4; i++)
	{
		map[smallBlocks[i].row][smallBlocks[i].col] = blockType;
	}
}

int Block::GetBlockType()
{
	return this->blockType;
}

void Block::moveLeftRight(int offset)
{
	for (int i = 0; i < 4; i++)
	{
		smallBlocks[i].col += offset;
	}
}
