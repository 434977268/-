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
	Block* curBlock;//当前方块
	Block* nextBlock;//下一个方块
	Block bakBlock;//当前方块的备用方块
	/// <summary>
	/// 用户输入时执行
	/// </summary>
	void KeyEvent();
	/// <summary>
	/// 更新界面
	/// </summary>
	void UpdataWindow();
	/// <summary>
	/// 设置延时
	/// </summary>
	/// <returns>返回距离上一次延时相隔的时间</returns>
	int GetDelay();
	/// <summary>
	/// 设置方块下降
	/// </summary>
	void Drop();
	/// <summary>
	/// 清楚填满的行
	/// </summary>
	void ClearLine();
	/// <summary>
	/// 延时长度
	/// </summary>
	int delay;
	/// <summary>
	/// 是否更新
	/// </summary>
	bool update;
	void Rotate();
	int score;
	void DrawScore();
	int level;
	int lineCount;
};


