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
	/// �½�
	/// </summary>
	void Drop();
	/// <summary>
	/// ƫ��
	/// </summary>
	/// <param name="offset"></param>
	void moveLeftRight(int offset);
	/// <summary>
	/// ��ת
	/// </summary>
	void Rotation();
	/// <summary>
	/// ����
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
	/// ��������
	/// </summary>
	int blockType;
	/// <summary>
	/// ���ÿ�����͵ķ�����ӷ�������Ļ�е�����
	/// </summary>
	Point smallBlocks[4];

	IMAGE* img;

	static IMAGE* imgs[7];
	static int size;
};

