#pragma once
#include <graphics.h>
#include <vector>
using namespace std;
struct  Point
{
	int row;
	int col;
};

class Block
{
public:
	Block();
	/// <summary>
	/// 下降
	/// </summary>
	void Drop();
	/// <summary>
	/// 偏移
	/// </summary>
	/// <param name="offset"></param>
	void moveLeftRight(int offset);
	/// <summary>
	/// 旋转
	/// </summary>
	void Rotation();
	/// <summary>
	/// 绘制
	/// </summary>
	void Draw(int leftMargin, int topMargin);
	Block& operator=(const Block& other);
	static IMAGE** getImage();
	Point* getSmallBlocks();
	bool blockInMap(const vector<vector<int>> &map);
	void Rotate();
	void solidify( vector<vector<int>> & map);
	int GetBlockType();
	
private :

	/// <summary>
	/// 方块类型
	/// </summary>
	int blockType;
	/// <summary>
	/// 组成每种类型的方块的子方块在屏幕中的坐标
	/// </summary>
	Point smallBlocks[4];

	IMAGE* img;

	static IMAGE* imgs[7];
	static int size;
};

