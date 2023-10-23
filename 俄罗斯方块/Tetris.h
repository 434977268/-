#pragma once
#include <time.h>
#include <stdlib.h>
#include <vector>
#include <graphics.h>
#include <map>
#include "Block.h"
#include <Windows.h>
#include <mmsystem.h>
#pragma comment (lib, "winmm.lib")

using namespace std;
class Tetris
{
public:
	Tetris(int rows, int cols, int left, int top, int blockSize);
	void Init();
	void Play();
private:
	vector<vector<int>> map;
	int rows;
	int cols;
	int leftMargin;
	int topMargin;
	int blockSize;
	IMAGE imgBg;
	void moveLeftRight(int offset);
	Block* curBlock;//��ǰ����
	Block* nextBlock;//��һ������
	Block bakBlock;//��ǰ����ı��÷���
	/// <summary>
	/// �û�����ʱִ��
	/// </summary>
	void KeyEvent();
	/// <summary>
	/// ���½���
	/// </summary>
	void UpdataWindow();
	/// <summary>
	/// ������ʱ
	/// </summary>
	/// <returns>���ؾ�����һ����ʱ�����ʱ��</returns>
	int GetDelay();
	/// <summary>
	/// ���÷����½�
	/// </summary>
	void Drop();
	/// <summary>
	/// �����������
	/// </summary>
	void ClearLine();
	/// <summary>
	/// ��ʱ����
	/// </summary>
	int delay;
	/// <summary>
	/// �Ƿ����
	/// </summary>
	bool update;
	void Rotate();
	int score;
	void DrawScore();
	int level;
	int lineCount;
};


